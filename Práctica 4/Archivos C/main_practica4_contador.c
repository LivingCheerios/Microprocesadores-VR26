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

const unsigned char display[10] = {
    0x3F,
    0x06,
    0x5B,
    0x4F,
    0x66,
    0x6D,
    0x7D,
    0x07,
    0x7F,
    0x6F
};

unsigned char contador = 0;

void main(void)
{
    ANSEL = 0;
    ANSELH = 0;

    OPTION_REG &= 0b01111111;

    TRISB = 0xFF;
    TRISC = 0x00;
    TRISD = 0x00;

    PORTB = 0xFF;
    PORTC = 0x00;
    PORTD = 0x00;

    while(1)
    {
        PORTC = display[contador % 10];
        PORTD = display[contador / 10];

        if(!RB0)
        {
            __delay_ms(50);

            if(!RB0)
            {
                if(contador == 99)
                    contador = 0;
                else
                    contador++;

                while(!RB0);
            }
        }

        if(!RB1)
        {
            __delay_ms(50);

            if(!RB1)
            {
                if(contador == 0)
                    contador = 99;
                else
                    contador--;

                while(!RB1);
            }
        }

        if(!RB2)
        {
            __delay_ms(50);

            if(!RB2)
            {
                contador = 0;

                while(!RB2);
            }
        }
    }
}