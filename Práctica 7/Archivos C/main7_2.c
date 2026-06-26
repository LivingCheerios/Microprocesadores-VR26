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
    unsigned char modo = 0;
    unsigned char boton_anterior = 1;

    while(1)
    {
        //==========================================
        // DETECCIÓN DE FLANCO DEL BOTÓN
        //==========================================
        if(!PORTBbits.RB0 && boton_anterior)
        {
            __delay_ms(20);           // debounce al presionar
            if(!PORTBbits.RB0)
            {
                modo++;
                if(modo > 2)
                    modo = 0;

                // Esperar a que se suelte el botón
                while(!PORTBbits.RB0);
                __delay_ms(20);       // debounce al soltar
            }
        }
        boton_anterior = PORTBbits.RB0;

        //==========================================
        // LECTURA ADC
        //==========================================
        unsigned int adc_value = ADC_Read();
        LCD_Clear();

        switch(modo)
        {
            //==================================
            // MODO VOLTAJE
            //==================================
            case 0:
            {
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
                break;
            }
            //==================================
            // MODO ADC
            //==================================
            case 1:
            {
                LCD_Set_Cursor(0, 0);
                LCD_putrs("ADC:");
                sprintf(buffer, "%u", adc_value);
                LCD_Set_Cursor(1, 0);
                LCD_putrs(buffer);
                break;
            }
            //==================================
            // MODO PORCENTAJE
            //==================================
            case 2:
            {
                unsigned int porcentaje;
                porcentaje =
                    ((unsigned long)adc_value * 100UL) / 1023UL;
                LCD_Set_Cursor(0, 0);
                LCD_putrs("Porcentaje:");
                sprintf(buffer, "%u %%", porcentaje);
                LCD_Set_Cursor(1, 0);
                LCD_putrs(buffer);
                break;
            }
        }
        __delay_ms(80);
    }
}