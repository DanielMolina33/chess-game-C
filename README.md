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


## Algoritmo empleado

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
    60. Hasta que piezaSeleccionada == "S"
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





