// Libraries
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
    // Initializes the window settings in UTF-8 format for special characters.
    initWindowsUTF8();
    // Initializes the random number generator seed based on the current time.
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
        // If start is 1 (indicates the start of the game)
        if (start) {
            // Store all used pieces and their stats
            if (strcmp(piece, "") != 0){
                int stats[3] = {successMoves, failedMoves};
                storeNewPiece(piece[0], usedPieces, stats, &idx);
            }
            
            // Resets counters and board for a new game attempt
            successMoves = 0;
            failedMoves = 0;
            initBoard(board);

            // Gets the initial piece from the main menu.
            strncpy(piece, mainMenu(), sizeof(piece));

            // When the piece is S, it means exit
            if (strcmp(piece, "S") != 0) randomPosition(piece, board);
        }

        if (strcmp(piece, "S") != 0) {
            askPiecePosition("\n\n¿A que celda quieres mover la ficha? ", &row, &col);
            col = toUpper(col);
            
            // Updates the board with the new position of the piece and count its stats
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
        // Gets the icon of the current piece.
        int pieceIdx = pieceType(usedPieces[i].name);

        // // Calculates the success percentage of the piece.
        int successPercentaje = (usedPieces[i].successCounter * 100) / usedPieces[i].timesUsed;

        printf("Ficha: %s\n", pieces[0][pieceIdx]);
        printf("Veces usada: %d\n", usedPieces[i].timesUsed);
        printf("Porcentaje de aciertos: %d%%\n", successPercentaje);
        printf("Movimientos fallidos: %d\n\n", usedPieces[i].failedCounter);
    }

    return 0;
}