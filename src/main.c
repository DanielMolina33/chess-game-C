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
#include "pieces.h"
#include "menu.h"
#include "utils.h"

// Counter variable to track how many times a piece is moved
int counter = 0;

int main() {
    initWindowsUTF8();
    srand(time(NULL));
    
    // Board declaration
    char board[SIZE][SIZE][LTR_SIZE];
    char usedPieces[ALLOWED_MOVES_SIZE];

    int row;
    char col;
    char piece[LTR_SIZE];
    int start = 1;
    char opt;
    int idx = 0;

    do {      
        if (start) {
            initBoard(board);
            strncpy(piece, mainMenu(), sizeof(piece));
            randomPosition(piece, board);
            
            // Set a single piece only once
            storeNewPiece(piece[0], usedPieces);
        }
        
        askPiecePosition("\n\n¿A que celda quieres mover la ficha? ", &row, &col);
        col = toUpper(col);
        
        setBoardPosition(row, col, piece, board);
        
        // Ask for a new piece, continue with the current one or go out
        getChar("\n¿Quieres probar otra ficha? (S/N)", &opt);
        start = toUpper(opt) == 'S';
        printf("%s", start ? "\n\n": "");

    } while (1);

    return 0;
}