#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// File headers
#include "constants.h"

int tower(int row1, int row2, int col1, int col2) {
    int rowDiff = abs(row2 - row1);
    int colDiff = abs(col2 - col1);
    return rowDiff < 1 || colDiff < 1;
}

// Check tower movements based on current position
void towerMovements(int rowI, int colI, char board[SIZE][SIZE][LTR_SIZE]){
    for(int rowF = 1; rowF < SIZE; rowF++){
        if(rowF != rowI){
            strcpy(board[rowF][colI], pieces[0][6]);
        }
    }

    for(int colF = 1; colF < SIZE; colF++){
        if(colF != colI){
            strcpy(board[rowI][colF], pieces[0][6]);
        }
    }
}

void suggestedPositions(int rowI, int colI, char piece, char board[SIZE][SIZE][LTR_SIZE]){
    switch (piece) {
        case 'T': {
            towerMovements(rowI, colI, board);
            break;
        }
    }
}

int checkPosition(int row1, int row2, int col1, int col2, char piece) {
    switch (piece) {
        case 'T': return tower(row1, row2, col1, col2);
    }

    return 0;
}