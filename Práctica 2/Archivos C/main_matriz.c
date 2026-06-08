#include <xc.h>

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define _XTAL_FREQ 8000000

//==================== PATRONES ====================

unsigned char X[8] = {
    0x81,
    0x42,
    0x24,
    0x18,
    0x18,
    0x24,
    0x42,
    0x81
};

unsigned char E[8] = {
    0xFF,
    0x80,
    0x80,
    0xFE,
    0x80,
    0x80,
    0x80,
    0xFF
};

unsigned char U[8] = {
    0x81,
    0x81,
    0x81,
    0x81,
    0x81,
    0x81,
    0x81,
    0x7E
};

unsigned char J[8] = {
    0xFF,
    0x04,
    0x04,
    0x04,
    0x04,
    0x84,
    0x84,
    0x78
};

unsigned char I[8] = {
    0xFF,
    0x18,
    0x18,
    0x18,
    0x18,
    0x18,
    0x18,
    0xFF
};

unsigned char C[8] = {
    0x7E,
    0x81,
    0x80,
    0x80,
    0x80,
    0x80,
    0x81,
    0x7E
};

unsigned char A[8] = {
    0x3C,
    0x42,
    0x81,
    0x81,
    0xFF,
    0x81,
    0x81,
    0x81
};

//==================== FUNCION ====================

void mostrarBarrido(unsigned char patron[])
{
    signed char desplazamiento;

    // Entra desde la derecha
    for(desplazamiento = 7; desplazamiento >= 0; desplazamiento--)
    {
        for(unsigned int t=0; t<8; t++)
        {
            for(char i=0; i<8; i++)
            {
                PORTB = 1 << i;
                PORTD = ~(patron[i] >> desplazamiento);
                __delay_ms(2);
            }
        }
    }

    // Se queda fija
    for(unsigned int t=0; t<5; t++)
    {
        for(char i=0; i<8; i++)
        {
            PORTB = 1 << i;
            PORTD = ~patron[i];
            __delay_ms(2);
        }
    }

    // Sale hacia la izquierda
    for(desplazamiento = 1; desplazamiento <= 7; desplazamiento++)
    {
        for(unsigned int t=0; t<8; t++)
        {
            for(char i=0; i<8; i++)
            {
                PORTB = 1 << i;
                PORTD = ~(patron[i] << desplazamiento);
                __delay_ms(2);
            }
        }
    }
}

//==================== MAIN ====================

void main(void)
{
    TRISB = 0x00;
    TRISD = 0x00;

    PORTB = 0x00;
    PORTD = 0x00;

    while(1)
    {
      mostrarBarrido(X);
      mostrarBarrido(E);
      mostrarBarrido(U);
      mostrarBarrido(J);
      mostrarBarrido(I);
      mostrarBarrido(C);
      mostrarBarrido(A);
    }
}