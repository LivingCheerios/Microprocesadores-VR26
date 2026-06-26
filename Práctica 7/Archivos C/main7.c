#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lcd.h"
//==================================================
// FUSES
//==================================================
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF
#define _XTAL_FREQ 8000000
//==================================================
// ADC
//==================================================
void ADC_Init()
{
    ANSEL  = 0x01;
    ANSELH = 0x00;
    OPTION_REG = OPTION_REG & 0x7F;
    ADCON0 = 0x81;
    ADCON1 = 0x80;
}
unsigned int ADC_Read()
{
    __delay_us(5);
    GO_nDONE = 1;
    while(GO_nDONE);
    return ((ADRESH << 8) + ADRESL);
}
//==================================================
// MAIN
//==================================================
void main(void)
{
    ADC_Init();

    TRISBbits.TRISB0 = 1;
    LCD lcd = {&PORTC, 2, 3, 4, 5, 6, 7};
    LCD_Init(lcd);

    char buffer[16];
    

    while(1)
    {
     
        unsigned int adc_value = ADC_Read();
        LCD_Clear();

        
        unsigned long milivoltios;
        milivoltios =
            ((unsigned long)adc_value * 5000UL) / 1023UL;
        unsigned int entera  = milivoltios / 1000;
        unsigned int decimal = milivoltios % 1000;
        LCD_Set_Cursor(0, 0);
        LCD_putrs("Voltaje:");
        sprintf(buffer, "%u.%03u V", entera, decimal);
        LCD_Set_Cursor(1, 0);
        LCD_putrs(buffer);
            
          
        __delay_ms(80);
    }
}