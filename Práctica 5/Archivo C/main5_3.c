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

unsigned int num = 0;
unsigned char direccion = 1;

void mostrar(void)
{
    unsigned char unidades = num % 10;
    unsigned char decenas = (num / 10) % 10;
    unsigned char centenas = (num / 100) % 10;
    unsigned char millares = num / 1000;

    PORTC = 0b11110111;
    PORTD = patron[millares];
    __delay_us(500);

    PORTC = 0b11111011;
    PORTD = patron[centenas];
    __delay_us(500);

    PORTC = 0b11111101;
    PORTD = patron[decenas];
    __delay_us(500);

    PORTC = 0b11111110;
    PORTD = patron[unidades];
    __delay_us(500);
}

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

    INTF = 0;
    INTEDG = 0;
    INTE = 1;
    GIE = 1;

    while(1)
    {
        for(int i = 0; i < 10; i++)
        {
            mostrar();
        }

        if(direccion)
        {
            num++;

            if(num == 10000)
            {
                num = 0;
            }
        }
        else
        {
            if(num == 0)
            {
                num = 9999;
            }
            else
            {
                num--;
            }
        }
    }
}

void __interrupt() ISR(void)
{
    if(INTF)
    {
        INTF = 0;

        __delay_ms(50);

        direccion = !direccion;
    }
}