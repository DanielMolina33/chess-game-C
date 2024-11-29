# Entrenamiento de ajedrez

## Requerimientos

- El programa debe mostrar un tablero de 8x8 cuadritos.
- Al iniciar el programa pregunta que pieza va a colocar.
- Una vez seleccionada, la pieza debe ubicarse de manera aleatoria dentro de tablero.
- Se preguntará al usuario a donde quiere mover la pieza mediante coordenadas en el tablero.
- Si el destino de la pieza es válido efectuará el movimiento si el movimiento es invalido deberá informarse que el movimiento es inválido y se mostrará en el tablero las posibles jugadas o movimientos de la pieza, esto dependerá del tipo de pieza y de los movimientos que esta pueda realizar.
- Tras cada movimiento se le preguntará al usuario si quiere o no continuar con el entrenamiento y con pieza actual o quiere salir o cambiar de pieza.
- Al finalizar se deberá mostrar un conjunto de estadísticas en el que se muestre:
    - Con cuales piezas jugó.
    - Cuantos movimientos en total realizó con cada una.
    - Cuantos movimientos fallidos realizó con cada una.
    - Porcentaje de aciertos con cada pieza.
    - Tiempo total de juego en minutos.

## Objetivo

Un juego interactivo para el entrenamiento de los movimientos básicos de las fichas del ajedrez:

- El peón
- El alfil
- El caballo
- La torre
- La dama
- El rey


## Algoritmos empleados

### Proceso general

    1.  Inicio
    2.  Declarar tablero[8][8] como matriz de cadenas vacías
    3.  Declarar tiempoInicio, tiempoFin, tiempoJuego como variables de tiempo
    4.  Declarar fichasUsadas como matriz
    5.  Declarar movimientoValido como entero
    6.  Declarar movimientosExitosos, movimientosFallidos, vecesUsada = 0
    7.  Declarar indice = 0 como entero
    8.  Declarar fila como entero
    9.  Declarar columna como carácter
    10. Declarar piezaSeleccionada, colorPieza como carácter
    11. Declarar pieza como cadena
    12. Declarar esInicio = 1
    13. Declarar opcion como carácter
    14. tiempoInicio = tiempo actual
    15. Repetir
    16.     Si esInicio = 1 Entonces
    17.         Si piezaSeleccionada no es cadena vacía Entonces
    18.             fichasUsadas[indice] = [movimientosExitosos, movimientosFallidos, vecesUsada]
    19.             indice++
    20.         Fin Si
    21.         movimientosExitosos = 0
    22.         movimientosFallidos = 0
    23.         Inicializar tablero
    24.         Escribir("Seleccione una ficha de ajedrez:")
    25.         Escribir("( R. Rey ) ( Q. Reina ) ( T. Torre ) ( A. Alfil )")
    26.         Escribir("( C. Caballo ) ( P. Peón )")
    27.         Escribir("Ingrese la inicial de la ficha deseada o (S. Salir): ")
    28.         Leer piezaSeleccionada
    29.         Escribir("Seleccione el color de ficha:")
    30.         Escribir("( N. Negro ) ( B. Blanco )")
    31.         Escribir("Ingrese la inicial del color deseado o (S. Salir): ")
    32.         Leer colorPieza
    33.         Si piezaSeleccionada != "S" Entonces
    34.             pieza = piezaSeleccionada + colorPieza
    35.         Fin Si
    36.         Posicionar pieza aleatoriamente en el tablero
    37.     Fin Si
    38.     Si piezaSeleccionada != "S" Entonces
    39.         Escribir("¿A qué celda quieres mover la ficha?")
    40.         Leer fila
    41.         Leer columna
    42.         Mientras fila < 1 o fila > 8 o columna no está entre 'A' y 'H' Hacer
    43.             Escribir("Movimiento fuera del tablero. Intenta de nuevo:")
    44.             Leer fila
    45.             Leer columna
    46.         Fin Mientras
    47.         Validar movimiento
    48.         Realizar movimiento
    49.         Si movimientoValido == 1 Entonces
    50.             movimientosExitosos++
    51.         Sino
    52.             Mostrar posibles movimientos
    53.             movimientosFallidos++
    54.         Fin Si
    55.         vecesUsada++
    56.         Escribir("¿Quieres probar otra ficha? (Y/N)")
    57.         Leer opcion
    58.         esInicio = ConvertirAMayuscula(opcion)
    59.     Fin Si
    60. Hasta que piezaSeleccionada != "S"
    61. tiempoFin = tiempo actual
    62. tiempoJuego = tiempoFin - tiempoInicio
    63. Mostrar tiempo de juego
    64. Para cada ficha en fichasUsadas
    65.     Escribir("Ficha: ", ficha.nombre)
    66.     Escribir("Veces usada: ", ficha.vecesUsada)
    67.     Escribir("Porcentaje de aciertos: ", (ficha.movimientosExitosos * 100) / ficha.vecesUsada, "%")
    68.     Escribir("Movimientos fallidos: ", ficha.movimientosFallidos)
    69. Fin Para
    70. Fin

### Algoritmos de cada pieza

#### Torre

    1. Funcion rook(rowI, rowF, colI, colF)
    2      Declarar rowDiff, colDiff como entero 
    3.     rowDiff = calcular valor absoluto entre la diferencia de rowF rowI
    4.     colDiff = calcular valor absoluto entre la diferencia colF entre colI
    5.     Si rowDiff < 1 O colDiff < 1 Entonces
    6.         Retornar Verdadero porque la torre puede moverse vertical y horizontal
    7.     Fin Si
    8.     Retornar Falso por que la torre no puede moverse en esa direccion
    9. Fin Funcion

#### Peón

    1. Funcion pawn(rowI, rowF, colI, colF)
    2.     Declarar rowDiff, colDiff, rowDiffAbs como enteros
    3.     rowDiff = calcular valor absoluto entre la diferencia de rowF y rowI
    4.     colDiff = calcular valor absoluto entre la diferencia de colF y colI
    5.     rowDiffAbs = calcular valor absoluto de rowDiff  
    6.     Si rowDiff == 0 Y colDiff == 0 Entonces
    7.         Retornar 1 porque la pieza no se movió
    8.     Fin Si
    9.     Si rowI == 1 O rowI == 8 Entonces
    10.         Retornar 0 porque es un movimiento en primera o última fila, es una promoción de ficha
    11.    Fin Si
    12.    Si rowI == 2 O rowI == 7 Entonces
    13.         Si rowDiffAbs > 2 Entonces
    14.             Retornar 0 porque solo se puede mover un máximo de 2 posiciones cuando la ficha está en su posición inicial
    15.         Fin Si
    16.         Si rowI == 2 Entonces
    17.             Mover en segunda fila, dos posiciones hacia adelante o una posición hacia arriba y una diagonal
    18.         Fin Si
    19.         Si rowI == 7 Entonces
    20.             Mover en séptima fila, dos posiciones hacia atrás o una posición hacia abajo y una diagonal
    21.         Fin Si
    22.     Fin Si
    23.     En cualquier otro lugar, mover una posición adelante o atrás o una posición diagonal
    24. Fin Funcion


#### Alfil

    1. Funcion bishop(rowI, rowF, colI, colF)
    2.     Declarar rowDiff, colDiff como enteros
    3.     rowDiff = calcular valor absoluto entre la diferencia de rowF y rowI
    4.     colDiff = calcular valor absoluto entre la diferencia de colF y colI
    5.     Si rowDiff == colDiff Entonces
    6.         Retornar Verdadero porque el alfil puede moverse en diagonal
    7.     Fin Si
    8.     Retornar Falso porque el alfil no puede moverse en esa dirección
    9. Fin Funcion

#### Caballo

    1. Funcion knight(rowI, rowF, colI, colF)
    2.     Declarar rowDiff, colDiff como enteros
    3.     rowDiff = calcular valor absoluto entre la diferencia de rowF y rowI
    4.     colDiff = calcular valor absoluto entre la diferencia de colF y colI
    5.     Si (rowF >= 1 Y rowF < 8) Y (colF >= 1 Y colF < 8) Entonces
    6.         Si (rowDiff == 2 Y colDiff == 1) O (colDiff == 2 Y rowDiff == 1) Entonces
    7.             Retornar 1  porque el caballo puede moverse en forma de "L"
    8.         Fin Si
    9.     Fin Si
    10.     Retornar 0 porque el movimiento no es válido para el caballo
    11. Fin Funcion

#### Reina

    1. Funcion queen(rowI, rowF, colI, colF)
    2.     Declarar rowDiff, colDiff como enteros
    3.     rowDiff = calcular valor absoluto entre la diferencia de rowF y rowI
    4.     colDiff = calcular valor absoluto entre la diferencia de colF y colI
    5.     Si rowI == rowF O colI == colF O rowDiff == colDiff Entonces
    6.         Si rowF >= 1 Y rowF <= 8 Y colF >= 1 Y colF <= 8 Entonces
    7.             Retornar 1 porque la reina puede moverse en diagonal y horizontal y vertical
    8.         Fin Si
    9.     Fin Si
    10.     Retornar 0 porque el movimiento no es valido para la reina
    11. Fin Funcion


#### Rey

    1. Funcion king(rowI, rowF, colI, colF)
    2.     Declarar rowDiff, colDiff como enteros
    3.     rowDiff = calcular valor absoluto entre la diferencia de rowF y rowI
    4.     colDiff = calcular valor absoluto entre la diferencia de colF y colI
    5.     Si rowDiff <= 1 Y colDiff <= 1 Entonces
    6.         Si rowF >= 1 Y rowF <= 8 Y colF >= 1 Y colF <= 8 Entonces
    7.             Retornar 1 porque el rey puede mover una posicion en cualquier direccion
    8.         Fin Si
    9.     Fin Si
    10.     Retornar 0 porque el movimiento no es válido para el rey
    11. Fin Funcion
