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

void ADC_Init(void)
{
    ANSEL = 0x01;
    ANSELH = 0x00;

    ADCON0 = 0x01;
    ADCON1 = 0x80;
}

unsigned int ADC_Read(unsigned char channel)
{
    ADCON0 &= 0x83;
    ADCON0 |= (channel << 2);

    __delay_ms(2);

    GO_nDONE = 1;

    while(GO_nDONE);

    return ((ADRESH << 8) + ADRESL);
}

void PWM_Init(void)
{
    TRISC2 = 0;

    PR2 = 124;

    CCP1CON = 0b00001100;

    T2CON = 0b00000101;

    CCPR1L = 0;
}

void PWM_SetDuty(unsigned int duty)
{
    CCPR1L = duty >> 2;

    CCP1CONbits.DC1B1 = (duty & 0x02) >> 1;
    CCP1CONbits.DC1B0 = duty & 0x01;
}

void main(void)
{
    unsigned int valorADC;

    ADC_Init();

    PWM_Init();

    while(1)
    {
        valorADC = ADC_Read(0);

        PWM_SetDuty(valorADC);
    }
}