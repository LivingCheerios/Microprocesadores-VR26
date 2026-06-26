#include <xc.h>

//=============================================================================
// CONFIGURACIÓN DE BITS DE CONFIGURACIÓN (FUSES)
//=============================================================================
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

//=============================================================================
// DEFINICIONES
//=============================================================================
#define _XTAL_FREQ 8000000

#define PULSO_MIN   500     // 1 ms  -> 0 grados
#define PULSO_MAX   1000    // 2 ms  -> 180 grados

#define PASOS       100
#define TIEMPO_PASO_MS  50

//=============================================================================
// FUNCIONES
//=============================================================================

void Set_Pulso(unsigned int valor) {
    CCP1CON &= 0xCF;
    CCP1CON |= (unsigned char)((valor & 0x03) << 4);
    CCPR1L = (unsigned char)(valor >> 2);
}

void PWM_Init(void) {

    TRISC2 = 1;

    PR2 = 249;            // Periodo de 20ms con prescaler 1:16

    CCPR1L = (PULSO_MIN >> 2);
    CCP1CON = 0b00001100;
    CCP1CON |= (PULSO_MIN & 0x03) << 4;

    PIR1bits.TMR2IF = 0;
    T2CON = 0b00000111;

    while(!PIR1bits.TMR2IF);
    PIR1bits.TMR2IF = 0;

    TRISC2 = 0;
}

void main(void) {

    ANSEL  = 0x00;
    ANSELH = 0x00;
    TRISC  = 0x00;

    PWM_Init();

    int paso;
    long rango = PULSO_MAX - PULSO_MIN;

    while(1) {

        for (paso = 0; paso <= PASOS; paso++) {
            unsigned int pulso = PULSO_MIN + (rango * paso) / PASOS;
            Set_Pulso(pulso);
            __delay_ms(TIEMPO_PASO_MS);
        }

        for (paso = PASOS; paso >= 0; paso--) {
            unsigned int pulso = PULSO_MIN + (rango * paso) / PASOS;
            Set_Pulso(pulso);
            __delay_ms(TIEMPO_PASO_MS);
        }
    }
}