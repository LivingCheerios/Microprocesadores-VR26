#include <xc.h>

//=============================================================================
// CONFIGURACIÓN DE BITS DE CONFIGURACIÓN (FUSES)
//=============================================================================

#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

//=============================================================================
// DEFINICIONES
//=============================================================================

#define _XTAL_FREQ 8000000

//=============================================================================
// PROGRAMA PRINCIPAL
//=============================================================================

void main(void)
{
    unsigned char led = 0x01;
    char direccion = 1;

    TRISD = 0x00;

    while(1)
    {
        PORTD = led;
        __delay_ms(60);

        if(direccion)
        {
            led <<= 1;

            if(led == 0x80)
                direccion = 0;
        }
        else
        {
            led >>= 1;

            if(led == 0x01)
                direccion = 1;
        }
    }
}