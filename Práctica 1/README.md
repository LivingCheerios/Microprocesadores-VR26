# Práctica 1

Esta práctica consistió en 3 ejercicios:
* Ejercicio 1: Prender y apagar 4 leds al mismo tiempo
* Ejercicio 2: Realizar un contador de 6 bits
* Ejercicio 3: Realizar una secuencia tipo "caminata" con 8 leds

## Materiales utilizados
* PIC16f887
* Push button
* Leds azules (x8)
* Resistencias de 220Ω (x8)
* Cristal oscilador de 8Mhz


## Descripción
### Configuración básica del sistema (FUSES y oscilador)

<div align="justify">

Como Header en todas las prácticas, se tiene las configuraciones de los FUSEs. Solo se explicará en esta sección, pues en las demás prácticas permanecerá idéntico. En esta sección de código, se incluye la librería del compilador XC8, con el que se podrá accesar a todos los registros del controlador. Aquí, se configura el tipo de oscilador "FOSC" como "HS", pues estarémos utilizando un cristal oscilador externo de 8Mhz. Y al tratarse de un oscilador superior a 4Mhz, es recomendable configurarlo en "HS". Otras configuraciones notables es  "#pragma config WDTE = OFF". Debido a que nuestros programas por naturaleza serán cíclicos, no queremos que el temporizador de perro guardián reinicie el controlador al detectar que éste se encuentra en bucle. Por lo mismo, se configura en OFF. Por último, se utiliza "#pragma config BOREN = ON" para configurar RE3 como un RESET del controlador. Después de haber configurado los fuses, se configura la frecuencia del oscilador que se utilizará:  #define _XTAL_FREQ 8000000

</div>

### Ejercicio 1: Blinker

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

### Ejercicio 2: Contador Binario de 6 bits

<div align="justify">

Para poder realizar el ejercicio 2 se utilizó la siguiente lógica:

* Se declara la variable contador de tipo unsigned char y se inicializa en cero (unsigned char contador = 0;). Esta variable es la que llevará el registro numérico de nuestra cuenta.

* Se inicializa el puerto D completo como salida declarando TRISD = 0x00; (que es el equivalente hexadecimal de 0b00000000).

* Se entra en el bucle infinito while(1).

* Dentro del bucle, se manda el valor de la cuenta a los pines físicos usando PORTD = contador & 0x3F;. El valor hexadecimal 0x3F convertido a binario es 0b00111111. Al utilizar el operador lógico AND (&), se crea una "máscara" que deja pasar el valor del contador hacia los primeros 6 pines (RD0 al RD5), pero obliga a los pines sobrantes (RD6 y RD7) a mantenerse siempre en LOW.

* Se genera un retardo con __delay_ms(500);. El microcontrolador espera 500 milisegundos para que podamos percibir visualmente la combinación de LEDs encendidos.

* Se incrementa el valor actual de la variable en uno mediante la instrucción contador++;.

* Se evalúa una condición límite usando if(contador > 63). Como estamos haciendo un contador de 6 bits, el valor máximo que podemos representar es el 63 en decimal (es decir, todos los 6 LEDs en HIGH: 0b00111111).

* Si la variable supera el número 63 (al llegar a 64), se ejecuta la instrucción interna contador = 0; para reiniciar la cuenta.

* Con esto, el ciclo vuelve a iniciar, logrando así un sistema que realiza una secuencia de conteo binario ascendente del 0 al 63 de forma ininterrumpida.
  
</div>

## Simulación e Implementación

![Simulación en Proteus](./assets/Captura%20de%20pantalla%202026-06-07%20142442.png) 

![Implementación física en Protoboard](./assets/Proto%20Practica1.jpeg)

## Archivos
Para esta práctica se cuentan con los siguentes archivos para todos los ejercicios:
* [Archivo del código en C](./Archivos%20C)
* [Archivo .hex generado por MPLAB](./Archivos%20.hex)
* [Archivo de la simulación de Proteus](./Archivos%20C) 
