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

* Para poder realizar el ejercicio 2 se utilizó la siguiente lógica:

* Configuración Inicial: Se configuran los puertos C y D como salidas (TRISC = 0; TRISD = 0;). El Puerto D se encargará de mandar el "dibujo" del número (los segmentos), y el Puerto C se encargará de seleccionar qué dígito físico se va a encender.

* Variable del Contador: Se declara la variable int num = 0;. Al ser un tipo de dato int (entero de 16 bits), ahora tiene la capacidad matemática de almacenar números mucho más grandes, perfectos para llegar hasta el 9999.

* Se entra en el bucle principal while(1).

* Descomposición del Número: Dentro del bucle, se toma el valor completo de num (por ejemplo, el 4567) y se despedaza en cuatro variables separadas usando matemáticas:

  * millares = num / 1000; (Ej: 4567 / 1000 = 4).

  * centenas = (num % 1000) / 100; (Ej: El residuo de dividir entre 1000 es 567. Luego 567 / 100 = 5).

  * decenas = (num % 100) / 10; (Ej: El residuo entre 100 es 67. Luego 67 / 10 = 6).

  * unidades = num % 10; (Ej: El residuo de dividir entre 10 directamente es 7).

* El Bucle de Multiplexación: Se utiliza un ciclo for que se repite 10 veces. Este ciclo tiene dos objetivos: dibujar los números rapidísimo para engañar al ojo humano (Persistencia de la Visión), y actuar como un retardo general para que la cuenta no avance tan rápido que sea imposible de leer.

Proceso de Barrido (dentro del for):

* Se activa solo el primer display mandando un 0 lógico en el bit correspondiente del Puerto C (PORTC = 0b11110111;). Inmediatamente, se manda el dibujo al Puerto D (PORTD = patron[millares];) y se espera 1 milisegundo.

* Se apaga el primero y se enciende solo el segundo display (PORTC = 0b11111011;), se manda el dibujo de las centenas, y se espera 1 ms.

* Se repite el proceso para el tercer display (0b11111101;) con las decenas, y para el cuarto display (0b11111110;) con las unidades, cada uno encendido solo por 1 ms.

* Nota técnica: Toda esta secuencia de 4 encendidos tarda apenas 4 milisegundos en completarse. El ojo humano es demasiado lento para notar este parpadeo, por lo que el cerebro fusiona las imágenes y parece que los 4 dígitos están encendidos al mismo tiempo.

* Incremento de la Cuenta: Una vez que el ciclo for termina de mostrar el número actual por unas fracciones de segundo, se incrementa el contador general sumándole uno (num++;).

* Límite y Reseteo: Se evalúa la condición if(num == 10000). Como el display físico solo tiene 4 dígitos (y el máximo es 9999), si la cuenta intenta llegar al diez mil, la condición fuerza a la variable de regreso a cero (num = 0;), repitiendo la secuencia desde el principio infinitamente.


</div>

### Ejercicio 3: Contador del 0-9999 con interrupciones

<div align="justify">

Para poder realizar el tercer ejercicio se utilizó la siguiente lógica:

* Variables Globales: Se declaran num (que guardará la cuenta actual del 0 al 9999) y direccion (que funciona como una bandera: 1 significa cuenta ascendente y 0 cuenta descendente) fuera del main para que tanto el programa principal como la interrupción puedan acceder a ellas.

* Modularidad con la función mostrar(): Para mantener el código limpio, se agrupó toda la lógica del display multiplexado en esta función.

  * Primero, separa el valor de num en millares, centenas, decenas y unidades usando operaciones de división y módulo (/ y %).

  * Luego, realiza el barrido encendiendo un dígito a la vez (modificando PORTC) y mandando el patrón correspondiente (a PORTD).

  * Se utilizan retardos de microsegundos (__delay_us(500)). Esto hace que el barrido sea mucho más rápido (imperceptible al ojo humano) dando la ilusión de que los cuatro números están encendidos fijos al mismo tiempo.

* Configuración Inicial: En el main, se configuran los puertos como digitales, se activan las resistencias Pull-up (en el Puerto B) y se definen entradas y salidas.

* Configuración de la Interrupción: Al igual que en la práctica anterior, se prepara el microcontrolador para reaccionar a una señal externa en el pin RB0 (INTF = 0, INTEDG = 0 para flanco de bajada, INTE = 1, y GIE = 1).

* Dentro del bucle principal (while(1)):

* Retardo visual activo: Se utiliza un ciclo for que repite la función mostrar() 10 veces. A diferencia de un __delay_ms() normal que "congela" al microcontrolador y apagaría el display, este ciclo mantiene la multiplexación viva mientras hace tiempo para que la cuenta no avance demasiado rápido.

* Lógica Bidireccional: Después de mostrar los números un rato, se evalúa la bandera direccion.

  * Si direccion vale 1, el contador incrementa (num++). Si llega a 10000, se reinicia a 0.

  * Si direccion vale 0, el contador decrementa (num--). Si está en 0, da la vuelta regresando a 9999.

* Rutina de Interrupción (ISR): Cuando el usuario presiona el botón, el programa pausa el conteo y salta a la ISR.

  * Se verifica que la interrupción provenga del botón comprobando la bandera INTF.

  * Inmediatamente se limpia la bandera (INTF = 0;) para indicarle al sistema que la alarma ya está siendo atendida.

  * Se incluye un __delay_ms(50); directamente dentro de la interrupción como filtro anti-rebote (debounce) para evitar que el ruido mecánico del botón provoque múltiples cambios accidentales.

  * Finalmente, se invierte el estado de la bandera usando una negación lógica (direccion = !direccion;). Si era 1 pasa a 0, y si era 0 pasa a 1.

  * Al salir de la interrupción, el bucle principal retoma su trabajo, pero ahora contando en el sentido contrario.

</div>

## Simulación e Implementación

### Ejercicio 1


![Simulación en Proteus](./assets/Captura%20de%20pantalla%202026-06-25%20195250.png) 

![Implementación física en Protoboard](./assets/Proto%20Practica4_1.jpeg)

### Ejercicio 2


![Simulación en Proteus](./assets/Captura%20de%20pantalla%202026-06-25%20004600.png) 

![Implementación física en Protoboard](./assets/Proto%20Practica4_2.jpeg)

## Archivos
Para esta práctica se cuentan con los siguentes archivos para todos los ejercicios:
* [Archivo del código en C](./Archivos%20C)
* [Archivo .hex generado por MPLAB](./Archivos%20.hex)
* [Archivo de la simulación de Proteus](./Simulaciones) 
