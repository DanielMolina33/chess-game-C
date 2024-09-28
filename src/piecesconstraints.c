#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// File headers
#include "piecesconstraints.h"

// Check if a piece can move to a new position based on its type
int checkPosition(int rowI, int rowF, int colI, int colF, char piece) {
    switch (piece) {
        case 'T':
            return rook(rowI, rowF, colI, colF);
        case 'P':
            return pawn(rowI, rowF, colI, colF);
    }

    return 0;
}

// Determine if a rook (tower) can move from one position to another. Based on chess rules (vertical, horizontal)
int rook(int rowI, int rowF, int colI, int colF) {
    int rowDiff = abs(rowF - rowI);
    int colDiff = abs(colF - colI);
    return rowDiff < 1 || colDiff < 1;  // Fix bug when position is outside the limits
}

// Determine if a pawn can move from one position to another. Based on chess rules (vertical only and attacks diagonally)
int pawn(int rowI, int rowF, int colI, int colF) {
    int rowDiff = rowF - rowI;
    int colDiff = abs(colF - colI);

    int rowDiffAbs = abs(rowDiff);

    // Piece was not moved
    if(rowDiff == 0 && colDiff == 0) return 1;

    // No movement is required when the piece is in the first or last row in the board
    if(rowI == 1 || rowI == 8) return 0;

    if (rowI == 2 || rowI == 7) {
        if(rowDiffAbs > 2) return 0;

        if(rowI == 2) {
            return (rowDiff > 0 && colDiff == 0) || (rowDiff < 0 && colDiff <= 1);
        }

        return (rowDiff < 0 && colDiff == 0) || (rowDiff > 0 && colDiff <= 1);
    }

    return (rowDiffAbs == 1 && (colDiff == 1 || colDiff == 0));
}

// Suggest allowable movements for the specified piece type
void suggestedMovements(int rowI, int colI, char piece, char board[SIZE][SIZE][LTR_SIZE]) {
    switch (piece) {
        case 'T': {
            rookMovements(rowI, colI, board);
            break;
        }
        case 'P': {
            pawnMovements(rowI, colI, board);
            break;
        }
    }
}

// Mark allowable movements for the rook (tower) on the board
void rookMovements(int rowI, int colI, char board[SIZE][SIZE][LTR_SIZE]) {
    for (int i = 1; i < SIZE; i++) {
        // Place vertical movements
        if (i != rowI) strcpy(board[i][colI], pieces[0][6]);
        // Place horizontal movements
        if (i != colI) strcpy(board[rowI][i], pieces[0][6]);
    }
}

// Mark allowable movements for the pawn on the board.
void pawnMovements(int rowI, int colI, char board[SIZE][SIZE][LTR_SIZE]) {
    int rowF = rowI - 1;
    int colF = colI - 1;

    if (rowI == 1 || rowI == 8) {
        printf("\nPuedes promocionar por otra ficha\n");
    } else {
        if (rowI == 2 || rowI == 7) {
            if(rowI == 2) rowF = 1;
            rowF = SIZE-1;

            for (int i = 1; i <= 2; i++) {
                if (rowI == 2) strcpy(board[rowI+i][colI], pieces[0][6]);
                else strcpy(board[rowI-i][colI], pieces[0][6]);
            }
        }

        for (int i = colF; i <= colF+2; i++) {
            if (i > 0 || i < SIZE-1) {
                if(rowI == 2 || rowI == 7) {
                    if (i < (colF+3)){
                        strcpy(board[rowF][i], pieces[0][6]);
                        continue;
                    }

                    break;
                } else {
                    strcpy(board[rowF][i], pieces[0][6]);
                    strcpy(board[rowF+2][i], pieces[0][6]);
                }
            }
        }
    }
}