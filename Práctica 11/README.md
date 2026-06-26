# Práctica 11

Esta práctica consistió en 2 ejercicios:
* Controlar la intensidad de un LED mediante un potenciómetro utilizando PWM por Hardware.
* Controlar la intensidad de dos LEDs mediante dos potenciómetros utilizando dos módulos PWM.

## Materiales utilizados
* PIC16F887
* 2 LEDs
* 2 Resistencias de 220Ω
* 2 Potenciómetros de 10kΩ
* Cristal oscilador de 8MHz

## Descripción

### Ejercicio 1: Control de intensidad de un LED con PWM por Hardware

<div align="justify">

Para poder realizar el ejercicio 1 se utilizó la siguiente lógica:

* Definiciones y Variables: Se define la constante `_XTAL_FREQ` con un valor de 8 MHz para utilizar correctamente las funciones de retardo. Se utiliza la variable `valorADC` para almacenar el resultado obtenido por el convertidor analógico-digital.

* Funciones auxiliares: Se crean las funciones `ADC_Init()`, `ADC_Read()`, `PWM_Init()` y `PWM_SetDuty()`. La primera configura el convertidor analógico-digital, la segunda realiza la lectura del canal seleccionado, la tercera inicializa el módulo PWM y la última actualiza el ciclo de trabajo del PWM.

* Configuración inicial: En la función `main()` se inicializan el convertidor analógico-digital y el módulo PWM mediante las funciones `ADC_Init()` y `PWM_Init()`. El pin AN0 queda configurado como entrada analógica y el pin RC2 como salida del módulo CCP1.

* Configuración del ADC: Esta es la parte clave antes de entrar al bucle. En la función `ADC_Init()` se configura el canal AN0 como entrada analógica mediante `ANSEL = 0x01`, mientras que el resto de los pines permanecen como digitales utilizando `ANSELH = 0x00`. También se configuran los registros `ADCON0` y `ADCON1` para habilitar el convertidor analógico-digital y establecer el formato del resultado.

* Configuración del PWM: En la función `PWM_Init()` se configura el pin RC2 como salida del módulo CCP1. Se establece el período del PWM mediante el registro `PR2`, se configura el módulo CCP1 en modo PWM utilizando `CCP1CON = 0b00001100` y se habilita el Timer2 para comenzar la generación de la señal PWM.

* Bucle Principal: Se entra en el `while(1)`. Aquí el programa realiza continuamente la lectura del potenciómetro mediante la función `ADC_Read(0);` y posteriormente envía ese valor a la función `PWM_SetDuty();`. Esta función actualiza el ciclo de trabajo del PWM, por lo que conforme cambia la posición del potenciómetro también cambia la intensidad del LED.

</div>

### Ejercicio 2: Control de intensidad de dos LEDs con dos potenciómetros

<div align="justify">

Para poder realizar el ejercicio 2 se utilizó la siguiente lógica:

* Definiciones y Variables: Se define la constante `_XTAL_FREQ` con un valor de 8 MHz para utilizar correctamente las funciones de retardo. Se utilizan las variables `pot1` y `pot2` para almacenar los valores obtenidos de cada uno de los potenciómetros.

* Funciones auxiliares: Se crean las funciones `ADC_Init()`, `ADC_Read()`, `PWM_Init()`, `PWM1_SetDuty()` y `PWM2_SetDuty()`. Las primeras permiten configurar y leer el convertidor analógico-digital, mientras que las dos últimas actualizan el ciclo de trabajo de cada módulo PWM.

* Configuración inicial: En la función `main()` se inicializan el convertidor analógico-digital y los módulos PWM mediante las funciones `ADC_Init()` y `PWM_Init()`. Los canales AN0 y AN1 quedan configurados como entradas analógicas, mientras que los pines RC2 y RC1 se configuran como salidas de los módulos CCP1 y CCP2, respectivamente.

* Configuración del ADC: Esta es la parte clave antes de entrar al bucle. En la función `ADC_Init()` se habilitan los canales AN0 y AN1 mediante `ANSEL = 0x03`, mientras que el resto de los pines permanecen configurados como digitales utilizando `ANSELH = 0x00`. También se configuran los registros `ADCON0` y `ADCON1` para habilitar el convertidor analógico-digital.

* Configuración del PWM: En la función `PWM_Init()` se configuran los módulos CCP1 y CCP2 en modo PWM mediante los registros `CCP1CON` y `CCP2CON`. Se establece el período utilizando el registro `PR2` y finalmente se habilita el Timer2 para generar ambas señales PWM.

* Bucle Principal: Se entra en el `while(1)`. Aquí el programa realiza continuamente la lectura de ambos potenciómetros utilizando las funciones `ADC_Read(0)` y `ADC_Read(1)`. Posteriormente cada lectura es enviada a las funciones `PWM1_SetDuty()` y `PWM2_SetDuty()`, actualizando el ciclo de trabajo de cada módulo PWM. Como resultado, cada LED modifica su intensidad de forma independiente según la posición de su respectivo potenciómetro.

</div>

## Simulación e Implementación

### Ejercicio 1

![Simulación en Proteus](./assets/11_1)

![Implementación física en Protoboard](./assets/Practica11.1.jpeg)

### Ejercicio 2

![Simulación en Proteus](./assets/11_2)



## Archivos

Para esta práctica se cuentan con los siguentes archivos para todos los ejercicios:
* [Archivo del código en C](./Archivos%20C)
* [Archivo .hex generado por MPLAB](./Archivos%20.hex)
* [Archivo de la simulación de Proteus](./assets/Practica11.pdsprj)
