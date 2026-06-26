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

Para poder realizar el ejercicio 1 se utilizó la siguiente lógica:

* Configuración de pines a modo Digital: Se utilizan las instrucciones ANSEL = 0x00; y ANSELH = 0x00;. Por defecto, muchos pines del microcontrolador inician configurados para leer señales analógicas (como sensores de temperatura). Al igualarlas a cero, le decimos al microcontrolador que trate a todos los pines estrictamente como entradas y salidas digitales (es decir, que solo entiendan el lenguaje de ceros y unos).

* Activación de resistencias Pull-up: Se ejecuta la operación OPTION_REG = OPTION_REG & 0x7F;. Esta operación limpia (pone en 0) el bit 7 de ese registro especial. En los microcontroladores PIC, hacer esto activa unas resistencias internas (Pull-ups) en el Puerto B. Gracias a esto, cuando el botón no está presionado, el pin lee un 1 (HIGH), y cuando se presiona y cierra el circuito a tierra, lee un 0 (LOW).

* Definición de Entradas y Salidas: Se configura el puerto B completo como entrada declarando TRISB = 0xFF; (donde estarán conectados los botones) y el puerto D completo como salida declarando TRISD = 0x00; (donde estarán los LEDs).

* Se entra en el bucle infinito while(1) para estar "escuchando" los botones constantemente.

* Dentro del bucle, se utiliza una sintaxis nueva: PORTDbits.RD0 y PORTBbits.RB0. Esto permite leer y escribir el estado de un pin específico individualmente, sin afectar al resto del puerto.

* Lógica de Inversión (NOT): Se utiliza la instrucción PORTDbits.RD0 = !PORTBbits.RB0; (y lo mismo para los pines 1 y 2). El operador ! representa una compuerta lógica NOT (Negación).Como activamos las resistencias Pull-up, si el botón no está presionado, el puerto B lee un 1. El operador ! lo invierte a 0, apagando el LED en el puerto D. Si el botón se presiona, el puerto B lee un 0. El operador ! lo invierte a 1, encendiendo el LED instantáneamente. Al no haber retardos (__delay_ms), el sistema responde de manera inmediata a la acción física del usuario, repitiendo esta evaluación de los 3 botones de forma ininterrumpida.

</div>

### Ejercicio 2: Contador del 0-99 con botones de suma, resta y reset

<div align="justify">
Para poder realizar el ejercicio 2 se utilizó la siguiente lógica:

* Se define un arreglo display[10] que contiene los códigos hexadecimales necesarios para formar los números del 0 al 9 en los displays de 7 segmentos. Asimismo, se inicializa la variable global contador = 0; que almacenará el valor actual de nuestra cuenta (del 0 al 99).

* Se configuran los pines del microcontrolador en modo estrictamente digital igualando ANSEL y ANSELH a 0, como se hizo en el ejercicio pasado.

* Se activan las resistencias Pull-up internas del microcontrolador aplicando una máscara al registro de opciones (OPTION_REG &= 0b01111111;). 

* Se configuran los puertos: El Puerto B se declara como entrada (TRISB = 0xFF;) para conectar los botones. Los Puertos C y D se declaran como salidas (TRISC = 0x00; y TRISD = 0x00;) para conectar el display de las unidades y el de las decenas, respectivamente.

* Se entra en el bucle infinito while(1).

* Separación de dígitos: Dentro del bucle, se divide el número del contador usando operaciones matemáticas básicas para enviarlo a los displays.

* PORTC = display[contador % 10];: La operación módulo (%) obtiene el residuo de la división entre 10, lo que nos da el dígito de las unidades.

* PORTD = display[contador / 10];: La división entera (/) entre 10 nos da el dígito de las decenas.

* Filtro Anti-rebote (Debounce): Para leer cada botón (ej. if(!RB0)), se utiliza una técnica de confirmación. Al detectar un 0 (botón presionado), el microcontrolador espera 50 milisegundos (__delay_ms(50);) y vuelve a preguntar si el botón sigue presionado (if(!RB0)). Esto elimina las lecturas falsas causadas por la vibración mecánica de los contactos del botón físico.

* Lógica del Botón Incrementar (RB0): Si se confirma su pulsación, se evalúa si la variable contador ya llegó al límite de 99. De ser así, se reinicia a 0. En caso contrario, se le suma uno (contador++).

* Lógica del Botón Decrementar (RB1): Si se confirma su pulsación, se evalúa el límite inferior. Si la variable está en 0, pasa directamente al límite superior (99). En caso contrario, se le resta uno (contador--).

* Lógica del Botón Reset (RB2): Si se confirma su pulsación, simplemente se iguala la variable a cero (contador = 0;), reiniciando la cuenta sin importar en qué número iba.

* Bloqueo de repetición: Al final de la lógica de cada botón, se incluye un bucle vacío condicionado (ej. while(!RB0);). Esto obliga al microcontrolador a quedarse "atrapado" sin hacer nada mientras el usuario mantenga el dedo en el botón, asegurando que la cuenta avance (o retroceda) exactamente un solo número por cada pulsación individual, en lugar de avanzar cientos de números por segundo.


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
