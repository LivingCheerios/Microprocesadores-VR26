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
#define LED PORTCbits.RC0

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

void blink_led()
{
    for(int i = 0; i < 4; i++)
    {
        LED = 1;
        __delay_ms(500);
        LED = 0;
        __delay_ms(500);
    }
}

void main(void)
{
    ANSEL = 0;
    ANSELH = 0;
    OPTION_REG &= 0b01111111;

    TRISC = 0;
    TRISD = 0;
    TRISB = 0xFF;

    PORTC = 0;
    PORTD = 0;

    unsigned char count = 0;

    INTF = 0;
    INTEDG = 0;
    INTE = 1;
    GIE = 1;

    while(1)
    {
        PORTD = patron[count];
        count = (count + 1) % 10;
        __delay_ms(500);
    }
}

void __interrupt() ISR(void)
{
    if(INTF && !RB0)
    {
        GIE = 0;
        blink_led();
        GIE = 1;
        INTF = 0;
    }
}