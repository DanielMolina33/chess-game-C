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

int main() {
    initWindowsUTF8();
    srand(time(NULL));
    
    // Board declaration
    char board[SIZE][SIZE][LTR_SIZE];

    // Game stats
    clock_t startTime, endTime;
    double timeTaken;
    Piece usedPieces[PIECES_AMOUNT];
    int successMoves = 0;
    int failedMoves = 0;
    int idx = 0;

    // Game interactions
    int row;
    char col;
    char piece[LTR_SIZE] = "";
    int start = 1;
    char opt;

    // Init start time
    startTime = clock();

    do {      
        if (start) {
            // Store all used pieces
            if (strcmp(piece, "") != 0){
                int stats[3] = {successMoves, failedMoves};
                storeNewPiece(piece[0], usedPieces, stats, &idx);
            }
            
            // Start over
            successMoves = 0;
            failedMoves = 0;
            initBoard(board);
            strncpy(piece, mainMenu(), sizeof(piece));
            if (strcmp(piece, "S") != 0) randomPosition(piece, board);
        }

        if (strcmp(piece, "S") != 0) {
            askPiecePosition("\n\n¿A que celda quieres mover la ficha? ", &row, &col);
            col = toUpper(col);
            
            setBoardPosition(row, col, piece, &failedMoves, &successMoves, board);
            
            // Ask for a new piece, continue with the current one or go out
            getChar("\n¿Quieres probar otra ficha? (Y/N)", &opt);
            start = toUpper(opt) == 'Y';
            printf("%s", start ? "\n\n": "");
        }

    } while (strcmp(piece, "S") != 0);

    // Stop time
    endTime = clock();
    timeTaken = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
    int minutes = (int)(timeTaken / 60);
    int seconds = (int)(timeTaken) % 60;

    // Print game stats
    printf("\n\n");
    printf("ESTADISTICAS\n\n");
    printf("Tiempo de juego: %02d:%02d\n", minutes, seconds);

    for (int i = 0; i < idx; i++) {
        int pieceIdx = pieceType(usedPieces[i].name);
        int successPercentaje = (usedPieces[i].successCounter * 100) / usedPieces[i].timesUsed;

        printf("Ficha: %s\n", pieces[1][pieceIdx]);
        printf("Veces usada: %d\n", usedPieces[i].timesUsed);
        printf("Porcentaje de aciertos: %d%%\n", successPercentaje);
        printf("Movimientos fallidos: %d\n\n", usedPieces[i].failedCounter);
    }

    return 0;
}