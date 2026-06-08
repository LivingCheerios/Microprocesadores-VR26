# Práctica 1

Esta práctica consistió en 3 ejercicios:
* Ejercicio 1: Dibujar una X en una matriz de LEDs 8x8
* Ejercicio 2: Dibujar 2 Letras de los nombres de cada integrante del equipo
Por simplicidad, se hicieron los 2 ejercicios en 1 mismo código, dibujando primero la X, y luego las demás letras. Como extra, el equipo decidió agregar la animación de "barrido" a las letras. 

## Materiales utilizados
* PIC16f887
* Push button
* Matriz de LEDs 8x8
* Cristal oscilador de 8Mhz


## Descripción

### Ejercicio 1 y 2: Dibujar letras en Matriz de LEDs

<div align="justify">

Para poder realizar el ejercicio 1 se utilizó la siguiente lógica:
* Se inicializa el puerto D como salida (TRISD = 0b00000000;)
* Se inicializan todos los pines del puerto en bajo (PORTD = 0b00000000;)
* Se entra en el bucle while
* Dentro del bucle, se declara "PORTD=0xF;". Aquí se espeficífca a qué pines del puerto D (que recordemos es de 8 bits) queremos accesar, en este caso, para escribir/mandar voltaje. Esta llamada está en hexadecimal, que en decimal sería 15, y convertido a binario, sería 0b00001111. Sabemos entonces que ésta línea activa los pines RD0, RD1, RD2, y RD3 en HIGH, dejando a los demas pines del RD4-RD7 en LOW.
* Después, se genera un pequeño delay con "__delay_ms(500);". Aquí, el microcontrolador espera 500 milisegundos para pasar a la siguiente instrucción.
* Posterior a eso, se tiene "PORTD = 0x0;", esto nuevamente, es para accesar a los pines del puerto D ahora dejando todos los pines en LOW, pues la línea en binario declara 0b00000000. 
*  Con "__delay_ms(500);" el microcontrolador espera 500 milisegundos nuevamente, para volver a iniciae el bucle. Con eso, se tiene un sistema de "Blinker" o parpadeo de Leds.

</div>



## Simulación e Implementación

![Simulación en Proteus](./assets/Captura%20de%20pantalla%202026-06-07%20142442.png) 

![Implementación física en Protoboard](./assets/Proto%20Practica1.jpeg)

## Archivos
Para esta práctica se cuentan con los siguentes archivos para todos los ejercicios:
* [Archivo del código en C](./Archivos%20C)
* [Archivo .hex generado por MPLAB](./Archivos%20.hex)
* [Archivo de la simulación de Proteus](./Archivos%20C) 
