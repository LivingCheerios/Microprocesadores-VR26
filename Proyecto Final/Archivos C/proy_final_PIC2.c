#include <xc.h>
#include <stdbool.h>
#include "lcd.h"

//=============================================================================
// CONFIGURACION
//=============================================================================
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define _XTAL_FREQ 8000000

// PIC2 es la pantalla derecha. Su bala sale hacia la izquierda.
#define SOY_PIC2        1
#define BOTON           PORTBbits.RB0
#define ZONA_MUERTA     60

#define LCD_FILAS       2
#define LCD_COLS        16

#define SIN_BALA        0
#define BALA_DERECHA    1
#define BALA_IZQUIERDA  2

//=============================================================================
// CARACTERES PERSONALIZADOS
//=============================================================================
unsigned char Mono[8] = {
    0b01110,
    0b01110,
    0b00100,
    0b11111,
    0b00100,
    0b01010,
    0b10001,
    0b00000
};

unsigned char Bala[8] = {
    0b00000,
    0b00000,
    0b01110,
    0b11111,
    0b11111,
    0b01110,
    0b00000,
    0b00000
};

//=============================================================================
// VARIABLES DEL JUEGO
//=============================================================================
unsigned char jugador_fila = 0;
unsigned char jugador_col = 15;

unsigned char bala_activa = 0;
unsigned char bala_fila = 0;
signed char bala_col = 0;
unsigned char bala_dir = SIN_BALA;

unsigned char estado_rx = 0;
unsigned char tocado_timer = 0;

//=============================================================================
// ADC
//=============================================================================
void ADC_Init(void)
{
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;

    ANSEL = 0x03;       // AN0 = X, AN1 = Y
    ANSELH = 0x00;      // Todo lo demas digital

    ADCON0 = 0x81;      // ADC encendido, canal AN0
    ADCON1 = 0x80;      // Justificado a la derecha
}

unsigned int ADC_Read(unsigned char channel)
{
    ADCON0 &= 0x83;
    ADCON0 |= (channel << 2);
    __delay_us(30);
    GO_nDONE = 1;
    while (GO_nDONE);
    return ((ADRESH << 8) + ADRESL);
}

//=============================================================================
// UART
//=============================================================================
void UART_Init(void)
{
    TRISCbits.TRISC6 = 1;   // TX
    TRISCbits.TRISC7 = 1;   // RX

    SPBRG = 51;             // 9600 bps con Fosc = 8 MHz y BRGH = 1
    TXSTAbits.BRGH = 1;
    TXSTAbits.SYNC = 0;
    RCSTAbits.SPEN = 1;
    TXSTAbits.TXEN = 1;
    RCSTAbits.CREN = 1;
}

void UART_Write(char data)
{
    while (TXSTAbits.TRMT == 0);
    TXREG = data;
}

bool UART_Data_Ready(void)
{
    return PIR1bits.RCIF;
}

char UART_Read(void)
{
    if (RCSTAbits.OERR) {
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }
    return RCREG;
}

void Enviar_Bala(unsigned char fila)
{
    UART_Write('B');
    UART_Write('0' + fila);
}

//=============================================================================
// AUXILIARES
//=============================================================================
void delay_ms_var(unsigned int ms)
{
    while (ms--) __delay_ms(1);
}

void Iniciar_Bala_Local(void)
{
    if (bala_activa) return;

    bala_activa = 1;
    bala_fila = jugador_fila;
    bala_col = jugador_col - 1;
    bala_dir = BALA_IZQUIERDA;

    if (bala_col < 0) {
        bala_activa = 0;
        Enviar_Bala(bala_fila);
    }
}

void Iniciar_Bala_Recibida(unsigned char fila)
{
    if (bala_activa) return;

    bala_activa = 1;
    bala_fila = fila;
    bala_col = 0;
    bala_dir = BALA_DERECHA;
}

void Revisar_UART(void)
{
    while (UART_Data_Ready()) {
        char dato = UART_Read();

        if (estado_rx == 0) {
            if (dato == 'B') estado_rx = 1;
        }
        else {
            if (dato == '0' || dato == '1') {
                Iniciar_Bala_Recibida((unsigned char)(dato - '0'));
            }
            estado_rx = 0;
        }
    }
}

void Mover_Jugador(void)
{
    unsigned int vx = ADC_Read(0);
    unsigned int vy = ADC_Read(1);
    int dx = (int)vx - 512;
    int dy = (int)vy - 512;

    if (dx > ZONA_MUERTA) {
        if (jugador_col < LCD_COLS - 1) jugador_col++;
    }
    else if (dx < -ZONA_MUERTA) {
        if (jugador_col > 0) jugador_col--;
    }

    if (dy > ZONA_MUERTA) {
        jugador_fila = 0;
    }
    else if (dy < -ZONA_MUERTA) {
        jugador_fila = 1;
    }
}

void Mover_Bala(void)
{
    if (!bala_activa) return;

    if (bala_fila == jugador_fila && bala_col == jugador_col) {
        bala_activa = 0;
        tocado_timer = 10;
        return;
    }

    if (bala_dir == BALA_DERECHA) {
        bala_col++;
        if (bala_col >= LCD_COLS) {
            bala_activa = 0;
        }
    }
    else if (bala_dir == BALA_IZQUIERDA) {
        bala_col--;
        if (bala_col < 0) {
            bala_activa = 0;
            Enviar_Bala(bala_fila);
        }
    }
}

void Dibujar(void)
{
    LCD_Clear();

    if (tocado_timer > 0) {
        LCD_Set_Cursor(0, 4);
        LCD_putrs("TOCADO!");
        tocado_timer--;
        return;
    }

    LCD_Set_Cursor(jugador_fila, jugador_col);
    LCD_WriteCustomChar(0);

    if (bala_activa && bala_col >= 0 && bala_col < LCD_COLS) {
        LCD_Set_Cursor(bala_fila, (unsigned char)bala_col);
        LCD_WriteCustomChar(1);
    }
}

//=============================================================================
// MAIN
//=============================================================================
void main(void)
{
    ADC_Init();
    UART_Init();

    TRISBbits.TRISB0 = 1;
    OPTION_REGbits.nRBPU = 0;
    WPUBbits.WPUB0 = 1;

    LCD lcd = {&PORTD, 2, 3, 4, 5, 6, 7};
    LCD_Init(lcd);
    LCD_CreateChar(0, Mono);
    LCD_CreateChar(1, Bala);

    while (1) {
        Revisar_UART();
        Mover_Jugador();

        if (BOTON == 0) {
            __delay_ms(20);
            if (BOTON == 0) {
                Iniciar_Bala_Local();
                while (BOTON == 0) {
                    Revisar_UART();
                    __delay_ms(10);
                }
            }
        }

        Mover_Bala();
        Dibujar();
        delay_ms_var(120);
    }
}