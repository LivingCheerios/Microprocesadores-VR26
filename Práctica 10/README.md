# Práctica 10: Timer 1

Esta práctica consistió en 2 ejercicios:
* Clase: Mostrar el tiempo de ejecución del microcontrolador en el display LCD, utilizando el Timer 1
* Actividad 1: Mostrar el valor del voltaje de un potenciómetro en el display LCD y simultáneamente el tiempo de ejecución con el Timer 1

## Materiales utilizados
* PIC16f887
* Display LCD 16x2
* Potenciómetro
* Resistencias de 220Ω
* Cristal oscilador de 8Mhz

## Descripción

### Clase: Tiempo de ejecución con Timer1

<div align="justify">

Para esta práctica se utilizó la siguiente lógica:

* Configuración del Timer1: Se configura el registro T1CON seleccionando el prescaler deseado y el reloj interno (Fosc/4) como fuente del temporizador, y se habilita el módulo activando el bit TMR1ON. A diferencia del Timer0, el Timer1 es un temporizador de 16 bits, por lo que se utilizan dos registros (TMR1H y TMR1L) para almacenar su valor.

* Precarga del registro: Se calcula y se precarga el valor inicial de TMR1H:TMR1L de forma que, considerando la frecuencia del cristal (8MHz) y el prescaler configurado, el temporizador se desborde exactamente cada cierto intervalo conocido (por ejemplo, cada 50ms o 100ms), facilitando el conteo de segundos transcurridos.

* Habilitación de interrupciones: Se habilita la interrupción por desbordamiento del Timer1 (TMR1IE) junto con las interrupciones periféricas (PEIE) y globales (GIE).

* Manejo de la interrupción: Dentro de la rutina de interrupción se verifica la bandera TMR1IF. Cada vez que el Timer1 se desborda se incrementa un contador de interrupciones; al alcanzar el número de desbordamientos equivalente a un segundo completo, se incrementa la variable global que lleva el conteo de segundos transcurridos. Se vuelve a precargar TMR1H:TMR1L con el valor calculado y se limpia la bandera TMR1IF.

* Cálculo y visualización del tiempo: La variable de segundos totales se convierte a formato MM:SS dividiendo entre 60 (minutos) y obteniendo el residuo (segundos), y se muestra en el LCD utilizando sprintf con el formato "%02u:%02u".

</div>

### Actividad 1: Voltaje del potenciómetro + tiempo de ejecución con Timer1

<div align="justify">

Para esta actividad se añadió la siguiente lógica:

* Configuración del Módulo ADC: Se configura ANSEL para declarar el pin del potenciómetro como entrada analógica, y se configura ADCON0/ADCON1 para seleccionar el reloj de conversión y el voltaje de referencia (Vdd/Vss).

* Lectura y conversión de voltaje: Se inicia la conversión activando el bit GO/DONE y se espera (sondeo) hasta que se limpia automáticamente, indicando que la conversión terminó. El valor de 10 bits resultante (ADRESH:ADRESL) se transforma a milivoltios multiplicando por 5000 y dividiendo entre 1023, separando después la parte entera y decimal para mostrarla en formato "X.XXX V".

* Visualización simultánea en LCD: En el bucle principal se actualiza constantemente el renglón del LCD correspondiente al voltaje leído del potenciómetro, mientras que el tiempo de ejecución en formato MM:SS se sigue actualizando en segundo plano de forma independiente, ya que su conteo ocurre completamente dentro de la rutina de interrupción del Timer1, sin depender de la velocidad de ejecución del resto del programa.

</div>

## Simulación e Implementación

![Simulación en Proteus](./assets/Simulacion10.jpeg)

![Implementación física en Protoboard](./assets/Implementacion10.jpeg)

## Archivos
Para esta práctica se cuentan con los siguientes archivos para todos los ejercicios:
* [Archivo del código en C](./Archivos%20C)
* [Archivo .hex generado por MPLAB](./Archivos%20.hex)
* [Archivo de la simulación de Proteus](./Practica10.pdsprj)
