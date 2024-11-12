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
        case 'A':
            return bishop(rowI, rowF, colI, colF);
        case 'C':
            return knight(rowI, rowF, colI, colF);
        case 'Q':
            return queen(rowI, rowF, colI, colF);
        case 'R':
            return king(rowI, rowF, colI, colF);
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

// Determine if a bishop can move from one position to another. Based on chess rules (diagonally only)
int bishop(int rowI, int rowF, int colI, int colF) {
    int rowDiff = abs(rowF - rowI);
    int colDiff = abs(colF - colI);

    return rowDiff == colDiff;
}

// Determine if a knight can move from one position to another. Based on chess rules (L only, any direction)
int knight(int rowI, int rowF, int colI, int colF) {
    int rowDiff = abs(rowF - rowI);
    int colDiff = abs(colF - colI);

    if (!((rowF >= 1 && rowF < SIZE) && (colF >= 1 && colF < SIZE))) return 0;
    if ((rowDiff == 2 && colDiff == 1) || (colDiff == 2 && rowDiff == 1)) return 1; 

    return 0;
}

// Determine if the queen can move from one position to another
int queen(int rowI, int rowF, int colI, int colF) {
    int rowDiff = abs(rowF - rowI);
    int colDiff = abs(colF - colI);

    // Check if the movement is either horizontal, vertical, or diagonal
    if (rowI == rowF || colI == colF || rowDiff == colDiff) {
        // Ensure the destination is within the board's limits
        if (rowF >= 1 && rowF <= SIZE && colF >= 1 && colF <= SIZE) {
            return 1; // Valid queen move
        }
    }
    
    return 0;
}

int king(int rowI, int rowF, int colI, int colF) {
    int rowDiff = abs(rowF - rowI);
    int colDiff = abs(colF - colI);

    if (rowDiff <= 1 && colDiff <= 1) {
        if (rowF >= 1 && rowF <= SIZE && colF >= 1 && colF <= SIZE) {
            return 1; // Valid king move
        }
    }
    
    return 0;
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
        case 'A': {
            bishopMovements(rowI, colI, board);
            break;
        }   
        case 'C': {
            knightMovements(rowI, colI, board);
            break;
        }
        case 'Q': {
            queenMovements(rowI, colI, board);
            break;
        }
        case 'R': {
            kingMovements(rowI, colI, board);
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

// Mark allowable movements for the bishop on the board.
void bishopMovements(int rowI, int colI, char board[SIZE][SIZE][LTR_SIZE]) {
    int rowF, colF;

    for (int i = 1; i < SIZE; i++) {
        rowF = rowI - i;
        colF = colI - i;

        if (rowF >= 1) {
            if (colF >= 1) strcpy(board[rowF][colF], pieces[0][6]);
            if (colF+2*(i) <= (SIZE-1)) strcpy(board[rowF][colF+2*(i)], pieces[0][6]);
        }

        rowF = rowI + i;
        colF = colI + i;

        if (rowF < SIZE) {
            if (colF < SIZE) strcpy(board[rowF][colF], pieces[0][6]);
            if (colF-2*(i) >= 1) strcpy(board[rowF][colF-2*(i)], pieces[0][6]);
        }
    }
}

// Mark allowable movements for the knight on the board.
void knightMovements(int rowI, int colI, char board[SIZE][SIZE][LTR_SIZE]) {
    int rowF, colF;
    
    // Los posibles desplazamientos del caballo en términos de (fila, columna)
    int knightMoves[8][2] = {
        {-2, -1}, {-1, -2}, {1, -2}, {2, -1},   // Movimientos hacia arriba/abajo y a la izquierda/derecha
        {2, 1}, {1, 2}, {-1, 2}, {-2, 1}         // Movimientos hacia abajo/arriba y a la derecha/izquierda
    };
    
    // Iteramos sobre cada uno de los posibles movimientos del caballo
    for (int i = 0; i < 8; i++) {
        // Calcular las nuevas posiciones de fila y columna
        rowF = rowI + knightMoves[i][0];
        colF = colI + knightMoves[i][1];
        
        // Verificar si la posición está dentro de los límites del tablero
        if (rowF >= 0 && rowF < SIZE && colF >= 0 && colF < SIZE) {
            // Si la casilla es válida, marcar el movimiento en el tablero
            strcpy(board[rowF][colF], pieces[0][6]);
        }
    }
}

// Mark allowable movements for the queen on the board.
void queenMovements(int rowI, int colI, char board[SIZE][SIZE][LTR_SIZE]) {
    bishopMovements(rowI, colI, board);
    rookMovements(rowI, colI, board);
}

// Mark allowable movements for the king on the board.
void kingMovements(int rowI, int colI, char board[SIZE][SIZE][LTR_SIZE]) {
    int rowF, colF = 1;

    for (int i = -1; i < 2; i++) {    
        rowF = rowI + i;
        colF = colI - 1;

        for (int j = 0; j < 3; j++) {
            if (rowF >= 0 && rowF < SIZE && colF >= 0 && colF < SIZE) {
                if (rowI != rowF || colI != colF) strcpy(board[rowF][colF], pieces[0][6]);
                colF++;
            }
        }
    }
}