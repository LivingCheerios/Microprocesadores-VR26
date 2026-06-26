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

unsigned int pot;
unsigned char prev_RB0 = 1;
unsigned char prev_RB1 = 1;

// ---------------- ADC ----------------
void ADC_Init()
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

    __delay_us(50);

    GO_nDONE = 1;
    while(GO_nDONE);

    return ((ADRESH << 8) + ADRESL);
}

// ---------------- PWM ----------------
void PWM_Init()
{
    TRISC2 = 0;

    PR2 = 255;

    CCP1CON = 0b00001100;

    T2CON = 0b00000100;
}

void PWM_SetDuty(unsigned int duty)
{
    CCPR1L = duty >> 2;

    CCP1CONbits.DC1B1 = (duty & 0x02) >> 1;
    CCP1CONbits.DC1B0 = duty & 0x01;
}

// ---------------- MAIN ----------------
void main()
{
    ADC_Init();
    PWM_Init();

    TRISB0 = 1;
    TRISB1 = 1;

    TRISB2 = 0;
    TRISB3 = 0;

    OPTION_REGbits.nRBPU = 0;

    RB2 = 0;
    RB3 = 0;

    while(1)
    {
        // -------- VELOCIDAD --------
        pot = ADC_Read(0);
        PWM_SetDuty(pot);

        // -------- DIRECCIÓN (FLANCO SIN RETARDO) --------

        if(prev_RB0 == 1 && RB0 == 0)
        {
            RB2 = 1;
            RB3 = 0;
        }

        if(prev_RB1 == 1 && RB1 == 0)
        {
            RB2 = 0;
            RB3 = 1;
        }

        prev_RB0 = RB0;
        prev_RB1 = RB1;
    }
}