# Práctica 6

Esta práctica consistió en 2 ejercicios:
* Ejercicio 1: Escribir "HELLO WORLD!" en una pantalla LCD 16x2
* Ejercicio 2: Crear caracteres personalizados y mostrarlos en la LCD 16x2

## Materiales utilizados
* PIC16f887
* Push button
* Pantalla LCD 16x2
* Cristal oscilador de 8Mhz


## Descripción
Para todos los ejercicios que consistan con la pantalla LCD, se utilizarán de ahora en adelante ciertas librerías (lcd.c y lcd.h). Se explicarán su funcionamiento en esta práctica, y permanecerá igual para las demás prácticas. 

### Ejercicio 1: "HELLO WORLD!"

Parte 1: Las Librerías (lcd.h y lcd.c)

Estas librerías ahorran el trabajo de hacer toda la comunicación binaria a mano. Están diseñadas para usar el LCD en modo de 4 bits, lo cual es excelente porque ahorra pines del microcontrolador (usas 6 pines en lugar de 10).

* La estructura LCD (lcd.h): Se define un tipo de dato personalizado que guarda a qué puerto físico te vas a conectar (ej. PORTC) y qué número de pin exacto usarás para las señales de control RS, EN y los datos D4 al D7.

* Macros de Comandos (lcd.h): Contiene atajos definidos con #define (como `LCD_Clear()` o `LCD_Set_Cursor()`) para que no tengas que memorizar los códigos hexadecimales nativos de la pantalla.

* Inicialización (lcd.c): La función `LCD_Init()` hace el trabajo pesado. Detecta qué puerto le pasaste (ej. PORTC) y automáticamente configura ese registro TRIS como salida (0x00). Luego, manda la secuencia de pulsos eléctricos exacta que requiere el chip del LCD para encender en modo de 4 bits, con líneas múltiples y encender la pantalla.

* Envío de Datos (lcd.c): Funciones como LCD_Out() y LCD_Write() se encargan de enmascarar los datos y mover los bits (bit-shifting) para mandar la información en dos bloques de 4 bits, haciendo el pulso necesario en el pin Enable (EN).

* Escritura amigable (lcd.c): Tienes funciones listas para usar como LCD_putc (para enviar una sola letra) y LCD_putrs o LCD_puts (para enviar palabras completas usando bucles internos).

Parte 2: El Programa Principal (main)


Configuración inicial: Se desactivan las entradas analógicas igualando `ANSEL` y `ANSELH` a 0x00.

* Instanciación del LCD: Se declara el objeto de la pantalla con LCD lcd = {&PORTC,2,3,4,5,6,7};. Esto le dice a la librería: "Conéctate al Puerto C. Usa el pin RC2 para RS, el RC3 para EN, y del RC4 al RC7 para los datos D4-D7". Acto seguido, se inicializa con LCD_Init(lcd);.

* Configuración de la Interrupción: Se prepara el pin RB0 como entrada y se configuran los registros de interrupción externa (INTEDG, INTF, INTE, GIE). Aunque en este código en particular la interrupción (la función ISR arriba) solo hace una pausa de 30 ms y limpia la bandera, se deja lista para el siguiente ejercicio que utilizará un push button.

* El Mensaje Estático: Se utiliza la instrucción LCD_Set_Cursor(0,2); para ubicar el texto en la fila 0 (la línea de arriba), empezando en la columna 2. Luego se imprime el texto estático con LCD_putrs("HELLO WORLD!");.

* El Efecto de "Máquina de Escribir": Se prepara un arreglo con el abecedario (texto[]) y una variable indice = 0;. Se posiciona el cursor al inicio de la línea de abajo (LCD_Set_Cursor(1,0);) y se entra al bucle infinito while(1).

* Lógica del Bucle (Animación):

  * Se evalúa if(texto[indice] != '\0') para saber si aún hay letras por imprimir (el \0 es un carácter invisible que marca el final de un texto en C).

  * Si hay letras, usa `LCD_putc(texto[indice]);` para imprimir una sola letra, incrementa el índice, y hace una pausa de 300 ms (__delay_ms(300);). Esto genera el efecto visual de que las letras van apareciendo una por una.

  * Si el índice llega al final de la palabra (entra al else), se reposiciona el cursor a la izquierda de la segunda línea (LCD_Set_Cursor(1,0);) y se imprimen 16 espacios en blanco para simular un "borrado" de esa fila.

  * Finalmente, se vuelve a poner el cursor al inicio, se reinicia el indice = 0;, y el abecedario vuelve a escribirse infinitamente.

</div>

### Ejercicio 2: Contador del 0-F

<div align="justify">




</div>

## Simulación e Implementación

![Simulación en Proteus](./assets/Captura%20de%20pantalla%202026-06-07%20202907.png) 

![Implementación física en Protoboard](./assets/Proto%20Practica3.jpeg)

## Archivos
Para esta práctica se cuentan con los siguentes archivos para todos los ejercicios:
* [Archivo del código en C](./Archivos%20C)
* [Archivo .hex generado por MPLAB](./Archivos%20.hex)
* [Archivo de la simulación de Proteus](./Practica3_1.pdsprj) 
