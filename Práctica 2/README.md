# Práctica 2

Esta práctica consistió en 2 ejercicios:
* Ejercicio 1: Dibujar una X en una matriz de LEDs 8x8
* Ejercicio 2: Dibujar 2 Letras de los nombres de cada integrante del equipo
Por simplicidad, se hicieron los 2 ejercicios en 1 mismo código, dibujando primero la X, y luego las demás letras. Como extra, el equipo decidió agregar la animación de "barrido" a las letras. 

## Materiales utilizados
* PIC16f887
* Push button
* Matriz de LEDs 8x8
* Cristal oscilador de 8Mhz

## Descripción

### Ejercicio 1 y 2: Dibujar letras en Matriz de LEDs

<div align="justify">
Para poder realizar los ejercicios, se utilizó la siguiente lógica:

* Creación de los caracteres (Patrones): Se definen arreglos (arrays) de 8 elementos. Cada valor hexadecimal dentro del arreglo representa una de las 8 filas (o columnas) necesarias para formar el "dibujo" de la letra pixel por pixel.
  
* Dentro de la función principal main, se configuran los Puertos B y D completamente como salidas (TRISB = 0x00; y TRISD = 0x00;). Se inicializan en estado bajo (0x00) para garantizar que la matriz empiece apagada.
*  Se entra en un bucle infinito while(1) donde se manda a llamar a la función personalizada mostrarBarrido(), pasándole como parámetro el arreglo de cada letra en el orden deseado (X, E, U, J, I, C, A).
*  El núcleo de la función aquí es la Multiplexación: Dentro de mostrarBarrido(), existe un ciclo interno for(char i=0; i<8; i++) encargado de la ilusión óptica. Utiliza PORTB = 1 << i; para encender solamente una línea de la matriz a la vez mediante un corrimiento de bits. Además, utiliza PORTD para mandar la parte del dibujo que corresponde a esa línea. Nota: Aquí se utiliza el operador ~ (NOT a nivel de bits) para invertir los 1s a 0s y los 0s a 1s, lo cual ajusta la lógica a la conexión física de la matriz.
*  Luego, se genera un retardo imperceptible de __delay_ms(2); para que el LED brille, antes de pasar a la siguiente línea.

Lógica del efecto Barrido

* Fase 1 del Efecto (Entrada desde la derecha): Se utiliza un ciclo for principal donde la variable desplazamiento decrementa de 7 a 0. En la línea PORTD = ~(patron[i] >> desplazamiento);, se aplica un corrimiento hacia la derecha a los datos de la letra. Esto provoca que el dibujo entre progresivamente a la zona visible de la matriz. El ciclo t intermedio funciona como un "congelador de fotogramas" para que la animación tenga una velocidad visible para el humano.

* Fase 2 del Efecto (Letra fija): Se ejecuta un ciclo donde no existe ningún corrimiento (PORTD = ~patron[i];). La letra se dibuja de forma normal durante 5 fotogramas (t<5), permitiendo que se mantenga estática y legible en el centro de la matriz por una fracción de segundo.

* Fase 3 del Efecto (Salida hacia la izquierda): Se utiliza un último ciclo for donde desplazamiento incrementa de 1 a 7. Ahora se aplica un corrimiento de los datos hacia la izquierda con patron[i] << desplazamiento. Esto va "empujando" el dibujo fuera de la matriz pixel por pixel, logrando que la letra salga del marco y dando paso a la siguiente.

</div>



## Simulación e Implementación

![Simulación en Proteus](./assets/Captura%20de%20pantalla%202026-06-07%20195642.png) 

![Implementación física en Protoboard](./assets/Proto%20Practica2.jpeg)

![Implementación física en Protoboard](./assets/Practica2.gif)

## Archivos
Para esta práctica se cuentan con los siguentes archivos para todos los ejercicios:
* [Archivo del código en C](./Archivos%20C)
* [Archivo .hex generado por MPLAB](./Archivos%20.hex)
* [Archivo de la simulación de Proteus](./Archivos%20C) 
