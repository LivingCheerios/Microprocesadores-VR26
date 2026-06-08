# Práctica 3

Esta práctica consistió en 2 ejercicios:
* Ejercicio 1: Contar del 0-9 en un display de 7 segmentos
* Ejercicio 2: Contar del 0-F (hexadecimal) en un display de 7 segmentos

## Materiales utilizados
* PIC16f887
* Push button
* Display de 7 segmentos cátodo común
* Resistencias de 220Ω (x8)
* Cristal oscilador de 8Mhz


## Descripción

### Ejercicio 1: Contador del 0-9

<div align="justify">

Para poder realizar el ejercicio 1 se utilizó la siguiente lógica:

* Se inicializa el puerto D completo como salida declarando TRISD = 0x00;. A estos pines estarán conectados los segmentos (a, b, c, d, e, f, g) del display.

* Se declara un arreglo (array) llamado hex que contiene los valores hexadecimales precalculados para formar los números. Por ejemplo, el primer valor 0x3F (que en binario es 0b00111111) encenderá los segmentos necesarios para dibujar un "0", el valor 0x06 dibujará un "1", y así sucesivamente hasta el "9".

* Se declara una variable unsigned char i = 0;. Esta variable tiene un doble propósito: llevará el control numérico de nuestra cuenta y, al mismo tiempo, funcionará como el "índice" para saber qué posición del arreglo hex debemos leer.

* Se entra en el bucle infinito while(1).

* Dentro del bucle, se manda la información a los pines físicos mediante la instrucción PORTD = hex[i];. Si i vale 0, el microcontrolador va a la lista, toma el valor 0x3F y lo manda al puerto, encendiendo el número 0 en el display físico.

* Se genera un retardo con __delay_ms(500); para que el dígito se mantenga encendido y visible durante medio segundo.

* Se incrementa el valor de la variable en uno mediante la instrucción i++; para preparar el siguiente dígito (pasando del 0 al 1, luego al 2, etc.).

* Se evalúa una condición de límite utilizando if(i > 9). Como nuestro objetivo es hacer un contador decimal de un solo dígito (del 0 al 9), no necesitamos leer posiciones del arreglo más allá de la 9.

* Si la variable i llega al número 10, la condición se cumple y se ejecuta i = 0; para reiniciar el índice al principio de la lista.

* El ciclo vuelve a iniciar, lo que resulta en una cuenta ascendente continua que se muestra visualmente en el display y se repite infinitamente.

</div>

### Ejercicio 2: Contador del 0-F

<div align="justify">

Para poder realizar el ejercicio 2 se utilizó la siguiente lógica:


</div>



## Simulación e Implementación

![Simulación en Proteus](./assets/Captura%20de%20pantalla%202026-06-07%20202907.png) 

![Implementación física en Protoboard](./assets/Proto%20Practica3.jpeg)

## Archivos
Para esta práctica se cuentan con los siguentes archivos para todos los ejercicios:
* [Archivo del código en C](./Archivos%20C)
* [Archivo .hex generado por MPLAB](./Archivos%20.hex)
* [Archivo de la simulación de Proteus](./Practica3_1.pdsprj) 
