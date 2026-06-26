# Práctica 9: Timer 0

Esta práctica consistió en 2 ejercicios:
* Clase: Mostrar el tiempo de ejecución del microcontrolador en el display LCD
* Actividad 1: Mostrar el valor del voltaje de un potenciómetro en el display LCD y simultáneamente el tiempo de ejecución

## Materiales utilizados
* PIC16f887
* Display LCD 16x2
* Potenciómetro
* Resistencias de 220Ω
* Cristal oscilador de 8Mhz

## Descripción

### Actividad 1: Voltaje del potenciómetro + tiempo de ejecución con Timer0

<div align="justify">

Para esta práctica se utilizó la siguiente lógica:

* Configuración del Timer0: Se inicializa el registro OPTION_REG con el valor 0x07, lo que asigna el prescaler 1:256 al Timer0. Se precarga el registro TMR0 con el valor 178, de forma que el temporizador cuente desde ahí hasta desbordarse (255) generando interrupciones periódicas. Se habilita la interrupción del Timer0 (T0IE) y las interrupciones globales (GIE).

* Manejo de la interrupción: Cada vez que el Timer0 se desborda se genera la bandera T0IF, entrando a la rutina de interrupción ISR(). Dentro de esta rutina se incrementa la variable counter, y al llegar a 101 desbordamientos se incrementa en una unidad la variable time (segundos transcurridos) y counter se reinicia a 0. Se vuelve a precargar TMR0 con 178 y se limpia la bandera T0IF para permitir la siguiente interrupción.

* Cálculo del tiempo en minutos y segundos: La variable time, que cuenta los segundos totales transcurridos desde el encendido del microcontrolador, se convierte a formato MM:SS dividiendo entre 60 (minutos) y obteniendo el residuo de esa división (segundos), mostrando el resultado con sprintf en el formato "%02u:%02u".

* Configuración del Módulo ADC: Se configura ANSEL para declarar el pin del potenciómetro (AN0) como entrada analógica, y se configura ADCON0/ADCON1 para seleccionar el reloj de conversión y el voltaje de referencia (Vdd/Vss).

* Lectura y conversión de voltaje: Se inicia la conversión activando GO_nDONE y se espera (sondeo) hasta que el bit se limpia automáticamente. El valor de 10 bits resultante (ADRESH:ADRESL) se transforma a milivoltios multiplicando por 5000 y dividiendo entre 1023, separando después la parte entera y decimal para mostrarla en formato "X.XXX V".

* Visualización simultánea en LCD: En el bucle principal (sin necesidad de detener la lectura del ADC) se actualiza constantemente el renglón superior del LCD con el voltaje del potenciómetro, mientras que el tiempo de ejecución en formato MM:SS se sigue actualizando en segundo plano gracias a que su conteo ocurre completamente dentro de la interrupción del Timer0, independiente del resto del programa.

</div>

## Simulación e Implementación

![Simulación en Proteus](./assets/Simulacion9.jpeg)

![Implementación física en Protoboard](./assets/Implementacion9.jpeg)

## Archivos
Para esta práctica se cuentan con los siguientes archivos para todos los ejercicios:
* [Archivo del código en C](./Archivos%20C)
* [Archivo .hex generado por MPLAB](./Archivos%20.hex)
* [Archivo de la simulación de Proteus](./Practica9.pdsprj)
