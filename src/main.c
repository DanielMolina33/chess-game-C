/*
    Tablero de ajedrez 8x8, con puntero dinamico, el cual se pueda actualizar
   constantemente y actualice la vista del tablero.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// File headers
#include "constants.h"
#include "board.h"
#include "menu.h"
#include "utils.h"

// Counter variable to track how many times a piece is moved
int counter = 0;

int main() {
    initWindowsUTF8();
    srand(time(NULL));
    
    // Board declaration
    char board[SIZE][SIZE][LTR_SIZE];

    char row;
    int col;
    char piece[LTR_SIZE];

    initBoard(board);
    strncpy(piece, mainMenu(), sizeof(piece));
    randomPosition(piece, board);

    do {
        printf("\n\n¿A que celda quieres mover la ficha? ");
        scanf(" %c%d", &col, &row);
        col = toUpper(col);

        setBoardPosition(row, col, piece, board);
    } while (1);

    return 0;
}