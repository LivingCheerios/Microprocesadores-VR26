# Práctica 4

Esta práctica consistió en 2 ejercicios:
* Ejercicio 1: Prender 3 Leds mediante entradas digitales (
* Ejercicio 2: Hacer un contador del 0-99, que mediante 3 botones pueda, sumar, restar, y resetear el conteo
  
## Materiales utilizados
* PIC16f887
* Push button
* Display de 7 segmentos cátodo común (x2)
* Resistencias de 220Ω (x16)
* Cristal oscilador de 8Mhz


## Descripción

### Ejercicio 1: Prender 3 Leds con botones

<div align="justify">

Para poder realizar el ejercicio 6 se utilizó la siguiente lógica:

* Configuración de pines a modo Digital: Se utilizan las instrucciones ANSEL = 0x00; y ANSELH = 0x00;. Por defecto, muchos pines del microcontrolador inician configurados para leer señales analógicas (como sensores de temperatura). Al igualarlas a cero, le decimos al microcontrolador que trate a todos los pines estrictamente como entradas y salidas digitales (es decir, que solo entiendan el lenguaje de ceros y unos).

* Activación de resistencias Pull-up: Se ejecuta la operación OPTION_REG = OPTION_REG & 0x7F;. Esta operación limpia (pone en 0) el bit 7 de ese registro especial. En los microcontroladores PIC, hacer esto activa unas resistencias internas (Pull-ups) en el Puerto B. Gracias a esto, cuando el botón no está presionado, el pin lee un 1 (HIGH), y cuando se presiona y cierra el circuito a tierra, lee un 0 (LOW).

* Definición de Entradas y Salidas: Se configura el puerto B completo como entrada declarando TRISB = 0xFF; (donde estarán conectados los botones) y el puerto D completo como salida declarando TRISD = 0x00; (donde estarán los LEDs).

* Se entra en el bucle infinito while(1) para estar "escuchando" los botones constantemente.

* Dentro del bucle, se utiliza una sintaxis nueva: PORTDbits.RD0 y PORTBbits.RB0. Esto permite leer y escribir el estado de un pin específico individualmente, sin afectar al resto del puerto.

* Lógica de Inversión (NOT): Se utiliza la instrucción PORTDbits.RD0 = !PORTBbits.RB0; (y lo mismo para los pines 1 y 2). El operador ! representa una compuerta lógica NOT (Negación).Como activamos las resistencias Pull-up, si el botón no está presionado, el puerto B lee un 1. El operador ! lo invierte a 0, apagando el LED en el puerto D. Si el botón se presiona, el puerto B lee un 0. El operador ! lo invierte a 1, encendiendo el LED instantáneamente. Al no haber retardos (__delay_ms), el sistema responde de manera inmediata a la acción física del usuario, repitiendo esta evaluación de los 3 botones de forma ininterrumpida.

</div>

### Ejercicio 2: Contador del 0-99 con botones de suma, resta y reset

<div align="justify">



</div>

## Simulación e Implementación

![Simulación en Proteus](./assets/Captura%20de%20pantalla%202026-06-07%20202907.png) 

![Implementación física en Protoboard](./assets/Proto%20Practica3.jpeg)

## Archivos
Para esta práctica se cuentan con los siguentes archivos para todos los ejercicios:
* [Archivo del código en C](./Archivos%20C)
* [Archivo .hex generado por MPLAB](./Archivos%20.hex)
* [Archivo de la simulación de Proteus](./Practica4_1.pdsprj) 
