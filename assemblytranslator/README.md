Autores: 
- Santiago Quintero
- Edgar M. Amézquita

Translator

## Compilando el programa:
Para compilar este programa se requiere QT version 5.
Generar el Makefile ejecutando:
`qmake`
Compilar haciendo uso del comando:
`make`
El Programa adjunto hace uso del compilador clang++ con
el estandar c++11 (utilizando el parametro -std=c++11).

## Probando el programa
Al ejecutar el programa se introduce el texto a traducir, previamente verificada su validez sintáctica
donde cada palabra clave, variable, etiqueta, etc. esta seperada por un espacio a excepción de la última paralabra.
Opcionalmente se puede copiar el texto que se encuentra en testinput.txt
Se oprime el botón de traducir y se cambia a la pestaña Output para ver el texto en binario.

## Limpiando el espacio de trabajo
Usar el comando:
`make clean`
Esto eliminará el ejecutable, junto con los archivos objeto. 