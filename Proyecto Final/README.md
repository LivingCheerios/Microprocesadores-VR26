# Proyeto Final

## Objetivo General

Como Proyecto Final, se creo un mini-videojuego de 2 jugadores. El jugador intenta impactar con un proyectil a otro jugador. Cada personaje es controlado por 1 PIC individual, y para enviar el proyectíl de una pantalla a otra, se comunican entre sí los PICs.

## Conocimientos Aplicados

* Manejo de librerías para utilizar pantallas LCD
* Conocimiento para generar caracteres especiales en una LCD
* Lectura de voltaje y acondicionamiento de datos a traves del ADC del PIC
* Interrupciones Externas
* Protocolos de comunicación entre micro-controladores

## Materiales utilizados
* PIC16f887
* Push button
* Leds azules (x8)
* Resistencias de 220Ω (x8)
* Cristal oscilador de 8Mhz


## Descripción

### Protocolo de Comunicación (EUSART)

<div align="justify">

El protocolo utilizado en el proyecto final es EUSART. La explicación de este protocolo a detalle se encuentra en el archivo pdf ubicado en la sección de Archivos. 

</div>

### Lógica del proyecto

<div align="justify">



</div>



## Simulación e Implementación

![Simulación en Proteus](./assets/Captura%20de%20pantalla%202026-06-07%20142442.png) 

![Implementación física en Protoboard](./assets/Proto%20Practica1.jpeg)

## Archivos
* [Explicación del protocolo EUSART](./Proyecto%20Final%20Micro%20(EUSART).pdf)
* [Archivo del código en C](./Archivos%20C)
* [Archivo .hex generado por MPLAB](./Archivos%20.hex)
* [Archivo de la simulación de Proteus](./SimuPractica1.pdsprj) 
