#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lcd.h"

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define _XTAL_FREQ 8000000

void ADC_Init()
{
    ANSEL = 0x03;
    ANSELH = 0x00;
    TRISAbits.TRISA0 = 1;
    TRISAbits.TRISA1 = 1;
    ADCON0 = 0x01;
    ADCON1 = 0x80;
    OPTION_REG &= 0x7F;
}

unsigned int ADC_Read(unsigned char channel)
{
    ADCON0 &= 0b11000011;
    ADCON0 |= (channel << 2);
    __delay_ms(2);
    GO_nDONE = 1;
    while(GO_nDONE);
    return ((ADRESH << 8) + ADRESL);
}

void main(void)
{
    char buffer[16];
    unsigned char modo = 0;
    unsigned char pot = 0;
    unsigned char boton0_anterior = 1;
    unsigned char boton1_anterior = 1;
    unsigned int adc_value;
    unsigned int porcentaje;
    unsigned long milivoltios;
    unsigned int entera, decimal;

    ADC_Init();
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    LCD lcd = {&PORTC, 2, 3, 4, 5, 6, 7};
    LCD_Init(lcd);

    while(1)
    {
        // RB0 cambia modo
        if(!PORTBbits.RB0 && boton0_anterior)
        {
            __delay_ms(20);
            if(!PORTBbits.RB0)
            {
                modo++;
                if(modo > 2)
                    modo = 0;
                while(!PORTBbits.RB0);
                __delay_ms(20);
            }
        }
        boton0_anterior = PORTBbits.RB0;

        // RB1 cambia potenciómetro
        if(!PORTBbits.RB1 && boton1_anterior)
        {
            __delay_ms(20);
            if(!PORTBbits.RB1)
            {
                pot = !pot;
                while(!PORTBbits.RB1);
                __delay_ms(20);
            }
        }
        boton1_anterior = PORTBbits.RB1;

        adc_value = ADC_Read(pot);
        LCD_Clear();

        switch(modo)
        {
            case 0:
                milivoltios = ((unsigned long)adc_value * 5000UL) / 1023UL;
                entera = milivoltios / 1000;
                decimal = milivoltios % 1000;
                LCD_Set_Cursor(0,0);
                if(pot == 0)
                    LCD_putrs("Voltaje RA0:");
                else
                    LCD_putrs("Voltaje RA1:");
                sprintf(buffer,"%u.%03u V",entera,decimal);
                LCD_Set_Cursor(1,0);
                LCD_putrs(buffer);
                break;

            case 1:
                LCD_Set_Cursor(0,0);
                if(pot == 0)
                    LCD_putrs("ADC RA0:");
                else
                    LCD_putrs("ADC RA1:");
                sprintf(buffer,"%u",adc_value);
                LCD_Set_Cursor(1,0);
                LCD_putrs(buffer);
                break;

            case 2:
                porcentaje = ((unsigned long)adc_value * 100UL) / 1023UL;
                LCD_Set_Cursor(0,0);
                if(pot == 0)
                    LCD_putrs("Porc RA0:");
                else
                    LCD_putrs("Porc RA1:");
                sprintf(buffer,"%u %%",porcentaje);
                LCD_Set_Cursor(1,0);
                LCD_putrs(buffer);
                break;
        }
        __delay_ms(100);
    }
}
