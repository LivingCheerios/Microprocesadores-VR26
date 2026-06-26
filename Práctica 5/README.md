# Práctica 5

Esta práctica consistió en 3 ejercicios:
* Realizar un contador de 0 - 9 con displays de 7 segmentos que al momento de presionar un boton se detenga el contador y haga parpadear un LED momentaneamente utilizando interrupcion externa
* Realizar un contador de 0 - 9999 con el display de 4 digitos de 7 segmentos
* Realizar un contador de 0 - 9999 que utilice interrupciones para sumar digitos.
  
## Materiales utilizados
* PIC16f887
* Push button
* Modulo de display de 7 segmentos cátodo común con 4 dígitos
* Resistencias de 220Ω (x16)
* Cristal oscilador de 8Mhz


## Descripción

### Ejercicio 1: Contador con interrupcion

<div align="justify">

Para poder realizar el ejercicio 1 se utilizó la siguiente lógica:

* Definiciones y Variables: Se declara una macro #define LED PORTCbits.RC0 para referirnos más fácilmente al pin del LED. Se crea el arreglo patron[10] con los valores hexadecimales para el display de 7 segmentos.

* Función auxiliar: Se crea una función blink_led() que contiene un ciclo for para encender y apagar el LED 4 veces, con retardos de 500 ms.

* Configuración inicial: En la función main, se configuran los pines analógicos como digitales (ANSEL = 0; ANSELH = 0;), se activan las resistencias Pull-up del Puerto B (OPTION_REG &= 0b01111111;) y se configuran los puertos de entrada (B) y salida (C y D).

* Configuración de la Interrupción: Esta es la parte clave antes de entrar al bucle. Se configuran los registros especiales para habilitar la interrupción externa en el pin RB0. INTF = 0; "limpia" la bandera de interrupción por si acaso (es como apagar la alarma antes de encender el sistema). INTEDG = 0; configura para que la interrupción se dispare en el "flanco de bajada" (falling edge), es decir, en el instante exacto en que el voltaje cae de 1 a 0 al presionar el botón. INTE = 1; habilita específicamente la interrupción externa (del pin RB0), y GIE = 1; habilita el "Interruptor Maestro" (Global Interrupt Enable). Permite que el microcontrolador escuche todas las interrupciones activadas.

* Bucle Principal: Se entra en el while(1). Aquí el programa actualiza el display con PORTD = patron[count];, calcula el siguiente número de forma elegante usando el módulo (count = (count + 1) % 10; que lo regresa a 0 al llegar a 10) y hace un retardo de 500 ms. El programa se queda dando vueltas aquí felizmente.

* Rutina de Servicio de Interrupción (ISR): Cuando el usuario presiona el botón en RB0, el hardware del microcontrolador detiene bruscamente el bucle while(1) y salta a la función especial void __interrupt() ISR(void).

* Dentro de la ISR: Se verifica que la bandera de interrupción externa se haya activado y el botón esté en bajo (if(INTF && !RB0)). GIE = 0;: Se apaga el interruptor maestro temporalmente para que ninguna otra interrupción interrumpa a esta misma interrupción (medida de seguridad). Se llama a la función blink_led();, bloqueando el contador mientras el LED parpadea 4 veces. GIE = 1;: Se vuelve a encender el interruptor maestro. INTF = 0;: Paso crucial. Se vuelve a limpiar (apagar) la bandera de la alarma. Si no se hace esto, el microcontrolador creería que el botón sigue presionado y se quedaría atrapado en la interrupción para siempre.

* Al terminar la función ISR, el microcontrolador salta de regreso de forma automática al bucle while(1) en el punto exacto donde fue interrumpido, retomando su cuenta normal en el display.

</div>

### Ejercicio 2: Contador del 0-9999 

<div align="justify">



</div>

### Ejercicio 3: Contador del 0-9999 con interrupciones

<div align="justify">



</div>

## Simulación e Implementación

### Ejercicio 1

![Simulación en Proteus](./assets/Captura%20de%20pantalla%202026-06-25%20202907.png) 

![Implementación física en Protoboard](./assets/Proto%20Practica4_1.jpeg)

### Ejercicio 2

![Simulación en Proteus](./assets/Captura%20de%20pantalla%202026-06-25%20202907.png) 

![Implementación física en Protoboard](./assets/Proto%20Practica4_2.jpeg)

## Archivos
Para esta práctica se cuentan con los siguentes archivos para todos los ejercicios:
* [Archivo del código en C](./Archivos%20C)
* [Archivo .hex generado por MPLAB](./Archivos%20.hex)
* [Archivo de la simulación de Proteus](./Practica4_1.pdsprj) 
