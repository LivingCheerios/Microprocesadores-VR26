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
  
Antes de empezar con la lógica del proyecto, unos puntos importantes:
* Se explicará la logica del código de 1 de los 2 PICs, ya que son prácticamente idénticos, sin embargo uno está hecho para ser la pantalla/jugador izquierdo, y otro código ligeramente modificado para ser la pantalla/jugador derecho.
* Se adjuntarán las librerías `lcd.c` y `lcd.h`, ya que se les hizo una pequeña modificación para poder utilizar los pines TX u RX que están en el puerto C, y mover la pantalla LCD al puerto D.

Para poder realizar este videojuego, el código se estructuró en un Bucle de Juego (Game Loop) que procesa las siguientes mecánicas paso a paso:


* Gráficos (Caracteres Personalizados): Se diseñaron "Sprites" (dibujos) para el jugador (`Mono`) y el proyectil (`Bala`) mediante arreglos de 8 bytes, donde los 1 y 0 representan los píxeles encendidos y apagados. Estos dibujos se cargan en la memoria de la pantalla utilizando la función LCD_CreateChar y se invocan en el juego con `LCD_WriteCustomChar`.

* Control de Movimiento (Joystick con ADC): La función `Mover_Jugador()` lee dos canales analógicos correspondientes a los ejes X y Y del joystick.

  * Se le resta 512 a la lectura para convertir el valor de 0 a 1023 en un plano cartesiano que va de -512 a +511.

  * Se implementa una `ZONA_MUERTA` de 60 puntos. Esto es una técnica vital en videojuegos para evitar el Drift; es decir, evita que el personaje se mueva solo si el resorte del joystick no regresa perfectamente al centro.

* Disparo Local: Al presionar el botón (con su respectivo filtro anti-rebote), se manda a llamar a `Iniciar_Bala_Local()`. Esta función revisa que no haya ya una bala activa en tu pantalla, y si es así, crea una nueva bala justo en la columna a la izquierda de tu personaje, indicándole que se mueva hacia la izquierda.

* Transición entre Pantallas: La función `Mover_Bala()` actualiza la posición del proyectil en cada fotograma. Como este código es para el "PIC 2" (pantalla derecha), las balas viajan hacia la izquierda. Si la columna de la bala es menor a 0 (bala_col < 0), significa que se salió de tu pantalla. En ese instante se desactiva de la memoria y se utiliza `Enviar_Bala(fila)` para avisarle al "PIC 1" por EUSART que debe dibujar una bala entrando a su pantalla.

* Recepción de Balas Enemigas: Constantemente se ejecuta `Revisar_UART()` para escuchar si el otro jugador te disparó. Al recibir la letra 'B' y el número de la fila, se ejecuta `Iniciar_Bala_Recibida()`. Esto hace aparecer de la nada una bala enemiga en el extremo izquierdo de tu pantalla (bala_col = 0) moviéndose velozmente hacia la derecha, directo a tu personaje.

* Sistema de Colisiones (Hitboxes): Dentro de la función `Mover_Bala()`, hay una condición matemática rigurosa: `if (bala_fila == jugador_fila && bala_col == jugador_col)`. Si las coordenadas X y Y del jugador y el proyectil son exactamente las mismas en un fotograma, se registra un impacto. La bala desaparece y se activa un contador `(tocado_timer = 10)` que bloquea el juego y muestra "TOCADO!" en pantalla durante varios ciclos.

* El Motor del Juego (`while(1)`): El bucle principal es el corazón del juego. Ejecuta los pasos estrictamente en este orden para cada "fotograma":

  * Escucha mensajes de la red (`Revisar_UART`).

  * Lee el joystick y mueve al jugador (`Mover_Jugador`).

  * Evalúa si se presionó el botón de disparo. (Nota: Mientras se presiona el botón, se sigue revisando el UART para no perder ninguna bala enemiga que llegue justo en ese milisegundo).

  * Actualiza la física y colisión del proyectil (`Mover_Bala`).

  * Borra la LCD y dibuja el nuevo estado visual (`Dibujar`).

  * Aplica un retardo `delay_ms_var(120)`. Esto define la velocidad a la que transcurre el tiempo en tu juego, dándote unos 8 fotogramas por segundo (FPS).

</div>



## Simulación e Implementación

![Simulación en Proteus](./assets/Captura%20de%20pantalla%202026-06-26%20121406.png) 

![Implementación física en Protoboard](./assets/Proy_final.gif)

## Archivos
* [Explicación del protocolo EUSART](./Proyecto%20Final%20Micro%20(EUSART).pdf)
* [Archivo del código en C](./Archivos%20C)
* [Archivo .hex generado por MPLAB](./Archivos%20.hex)
* [Archivo de la simulación de Proteus](./Proyecto_Final.pdsprj) 
