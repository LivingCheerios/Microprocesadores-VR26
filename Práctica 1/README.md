# Práctica 1

Esta práctica consistió en 3 ejercicios:
* Ejercicio 1: Prender y apagar 4 leds al mismo tiempo
* Ejercicio 2: Realizar un contador de 6 bits
* Ejercicio 3: Realizar una secuencia tipo "caminata" con 8 leds

## Materiales utilizados
* PIC16f887
* Push button
* Leds azules
* Resistencias de 220Ω
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
** Dentro

</div>

## Simulación e Implementación

![Simulación en Proteus](./assets/Captura%20de%20pantalla%202026-06-07%20142442.png) 

![Implementación física en Protoboard](./assets/Proto%20Practica1.jpeg)

## Archivos
