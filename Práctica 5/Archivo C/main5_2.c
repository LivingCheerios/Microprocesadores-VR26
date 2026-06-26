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

const unsigned char patron[10] = {
    0x3F,
    0x06,
    0x5B,
    0x4F,
    0x66,
    0x6D,
    0x7D,
    0x07,
    0x7F,
    0x67
};

void main(void)
{
    TRISD = 0;
    TRISC = 0;

    int num = 0;

    while(1)
    {
        int millares = num / 1000;
        int centenas = (num % 1000) / 100;
        int decenas = (num % 100) / 10;
        int unidades = num % 10;

        for(int i = 0; i < 10; i++)
        {
            PORTC = 0b11110111;
            PORTD = patron[millares];
            __delay_ms(1);

            PORTC = 0b11111011;
            PORTD = patron[centenas];
            __delay_ms(1);

            PORTC = 0b11111101;
            PORTD = patron[decenas];
            __delay_ms(1);

            PORTC = 0b11111110;
            PORTD = patron[unidades];
            __delay_ms(1);
        }

        num++;

        if(num == 10000)
        {
            num = 0;
        }
    }
}