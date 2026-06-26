#include <xc.h>          // Biblioteca principal del compilador XC8
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"

//=============================================================================
// CONFIGURACION DE BITS DE CONFIGURACION (FUSES)
//=============================================================================
#pragma config FOSC = HS        // Oscilador HS (cristal externo)
#pragma config WDTE = OFF       // Watchdog deshabilitado
#pragma config PWRTE = OFF      // Power-up Timer deshabilitado
#pragma config BOREN = ON       // Brown-out Reset habilitado
#pragma config LVP = OFF        // Programacion en bajo voltaje deshabilitada
#pragma config CPD = OFF        // Proteccion EEPROM deshabilitada
#pragma config WRT = OFF        // Escritura de flash deshabilitada
#pragma config CP = OFF         // Proteccion de codigo deshabilitada

//=============================================================================
// DEFINICIONES
//=============================================================================
#define _XTAL_FREQ 8000000      // Frecuencia del oscilador (para __delay_ms/us)
volatile unsigned int time=0;
volatile unsigned int counter=0;
char exec[6];

void Timer0_Init(){
    OPTION_REG=0x07;
    TMR0=178;
    T0IE=1;
    GIE=1;
}

// Aquí van todas las interrupciones
void __interrupt() ISR(void){
    if(T0IF){
        counter++;
        if(counter>100){
            time++;
            counter=0;
        }
        TMR0=178;
        T0IF=0;
    }
}

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

void main(void){
    
    ADC_Init();
    TRISBbits.TRISB0 = 1;
    
    char buffer[16];
    
    Timer0_Init();
    LCD lcd={&PORTC,2,3,4,5,6,7};
    LCD_Init(lcd);
    LCD_Clear();
    LCD_Set_Cursor(0,0);
    
    LCD_putrs("Time: ");
    LCD_Set_Cursor(1,10);
    LCD_putrs("00:00");
    
    while(1){
        
        unsigned int adc_value = ADC_Read();
        
        unsigned long milivoltios;
        milivoltios =((unsigned long)adc_value * 5000UL) / 1023UL;
        unsigned int entera  = milivoltios / 1000;
        unsigned int decimal = milivoltios % 1000;
        LCD_Set_Cursor(0, 0);
        LCD_putrs("Voltaje:");
        sprintf(buffer, "%u.%03u V", entera, decimal);
        LCD_Set_Cursor(1, 0);
        LCD_putrs(buffer);
      
        LCD_Set_Cursor(1,10);
        sprintf(exec,"%02u:%02u",time/60,time%60);
        LCD_putrs(exec);
        
    
    }
    
}