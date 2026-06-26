# Práctica 8: Múltiple Lectura Analógica

Esta práctica consistió en 2 ejercicios:
* Clase: Mostrar el valor del voltaje de dos potenciómetros en el display LCD
* Actividad 1: Utilizar un botón para intercalar la vista del valor entre ADC, Voltaje (V) y Porcentaje, y otro botón para intercalar la vista del valor de un potenciómetro u otro

## Materiales utilizados
* PIC16f887
* Display LCD 16x2
* Potenciómetro (x2)
* Push button (x2)
* Resistencias de 220Ω
* Cristal oscilador de 8Mhz

## Descripción

### Clase: Lectura de dos potenciómetros en el LCD

<div align="justify">

Para esta práctica se utilizó la siguiente lógica:

* Configuración del Módulo ADC: Se configura el registro ADCON1 para establecer el voltaje de referencia (Vdd y Vss) y la justificación del resultado (izquierda o derecha). Se configura ADCON0 para seleccionar el reloj de conversión (Fosc) y habilitar el módulo ADC (ADON = 1).

* Configuración de pines analógicos: Se declaran como entradas analógicas los dos canales donde están conectados los potenciómetros (por ejemplo AN0 y AN1), utilizando el registro ANSEL, mientras que el resto de los pines se mantienen en modo digital.

* Selección de canal: Antes de cada conversión se selecciona el canal correspondiente (CHS) según el potenciómetro que se desea leer en ese momento.

* Conversión y lectura: Se inicia la conversión activando el bit GO/DONE del registro ADCON0. El microcontrolador espera (sondeo) hasta que este bit se limpia automáticamente, indicando que la conversión terminó. El resultado de 10 bits se obtiene combinando los registros ADRESH y ADRESL.

* Conversión a Voltaje y Porcentaje: El valor crudo del ADC (0-1023) se transforma matemáticamente a Voltaje multiplicando por la referencia (5V) y dividiendo entre la resolución (1023), y a Porcentaje dividiendo el valor entre 1023 y multiplicando por 100.

* Visualización en LCD: Se utilizan las funciones de la librería LCD (Lcd_Init, Lcd_Set_Cursor, Lcd_Write_String, etc.) para refrescar la pantalla mostrando el valor leído del potenciómetro activo en el formato seleccionado.

</div>

### Actividad 1: Selección de vista (ADC/Voltaje/Porcentaje) y selección de potenciómetro

<div align="justify">

Para esta actividad se añadió la siguiente lógica:

* Variables de estado: Se declaran dos variables globales, una para controlar el formato de visualización actual (vista = 0 para ADC, 1 para Voltaje, 2 para Porcentaje) y otra para controlar qué potenciómetro se está mostrando (canal_activo = 0 o 1).

* Botón de cambio de vista: Al detectar la pulsación confirmada (con filtro anti-rebote de 50 ms) del primer botón, se incrementa la variable vista. Cuando esta sobrepasa el valor 2, se reinicia a 0, generando un ciclo entre los tres formatos disponibles.

* Botón de cambio de potenciómetro: Al detectar la pulsación confirmada del segundo botón, se alterna la variable canal_activo entre 0 y 1, cambiando así el canal que se lee del ADC (CHS) y por lo tanto el potenciómetro que se muestra en pantalla.

* Bloqueo de repetición: Igual que en prácticas anteriores, se incluye un bucle de espera mientras el botón permanece presionado, para que cada pulsación física genere un único cambio de estado.

* Actualización del LCD: En cada ciclo del bucle principal se lee el potenciómetro indicado por canal_activo, se convierte el valor al formato indicado por vista, y se actualiza el LCD mostrando ambos datos (qué potenciómetro y en qué formato se está mostrando).

</div>

## Simulación e Implementación

![Simulación en Proteus](./assets/Simulacion8.jpeg)

![Implementación física en Protoboard](./assets/Practica8.jpeg)

## Archivos
Para esta práctica se cuentan con los siguientes archivos para todos los ejercicios:
* [Archivo del código en C](./Archivos%20C)
* [Archivo .hex generado por MPLAB](./Archivos%20.hex)
* [Archivo de la simulación de Proteus](./Practica8.pdsprj)
