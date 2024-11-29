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
    return rowDiff < 1 || colDiff < 1;
}

// Determine if a pawn can move from one position to another. Based on chess rules (vertical only and attacks diagonally)
int pawn(int rowI, int rowF, int colI, int colF) {
    int rowDiff = rowF - rowI;
    int colDiff = abs(colF - colI);

    int rowDiffAbs = abs(rowDiff);

    // Piece was not moved
    if(rowDiff == 0 && colDiff == 0) return 1;

    // No movement is required when the piece is in the first or last row in the board. That's a promotion
    if(rowI == 1 || rowI == 8) return 0;

    if (rowI == 2 || rowI == 7) {
        // The movement can be more than 2 positions in row 2 or 7 (Initial pawn position)
        if(rowDiffAbs > 2) return 0;

        if(rowI == 2) {
            // Move in second row, two positions down or one position up and one diagonally
            return (rowDiff > 0 && colDiff == 0) || (rowDiff < 0 && colDiff <= 1);
        }

        // Move in seventh row, two positions up or one position down and one diagonally
        return (rowDiff < 0 && colDiff == 0) || (rowDiff > 0 && colDiff <= 1);
    }

    // Move in any other place, one position up or down or one position diagonally
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

    // Ensure the movement is within the board's limits
    if (!((rowF >= 1 && rowF < SIZE) && (colF >= 1 && colF < SIZE))) return 0;

    // Check L direction
    if ((rowDiff == 2 && colDiff == 1) || (colDiff == 2 && rowDiff == 1)) return 1; 

    return 0;
}

// Determine if the queen can move from one position to another. Based on chess rules (Any direction, except L)
int queen(int rowI, int rowF, int colI, int colF) {
    int rowDiff = abs(rowF - rowI);
    int colDiff = abs(colF - colI);

    // Check if the movement is either horizontal, vertical, or diagonal
    if (rowI == rowF || colI == colF || rowDiff == colDiff) {
        // Ensure the movement is within the board's limits
        if (rowF >= 1 && rowF <= SIZE && colF >= 1 && colF <= SIZE) {
            return 1;
        }
    }
    
    return 0;
}

// Determine if the king can move from one position to another. Based on chess rules (Any direction, only one position)
int king(int rowI, int rowF, int colI, int colF) {
    int rowDiff = abs(rowF - rowI);
    int colDiff = abs(colF - colI);


    if (rowDiff <= 1 && colDiff <= 1) {
        // Ensure the movement is within the board's limits
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

    // If the pawn is in the first or the last row, it can be promoted for another piece. (Based on chess rules)
    if (rowI == 1 || rowI == 8) {
        printf("\nPuedes promocionar por otra ficha\n");
    } else {
        // Mark movements in the initial pawn position
        if (rowI == 2 || rowI == 7) {
            if(rowI == 2) rowF = 1; // When the piece is in the second row, rowF is in the first row
            else rowF = SIZE-1; // When the piece is in the seventh row, rowF is in the last row

            for (int i = 1; i <= 2; i++) {
                if (rowI == 2) strcpy(board[rowI+i][colI], pieces[0][6]);
                else strcpy(board[rowI-i][colI], pieces[0][6]);
            }
        }

        for (int i = colF; i <= colF+2; i++) {
            // Ensure the hint to be placed is within the board's limits
            if (i > 0 || i < SIZE-1) {
                // Place the diagonal hints in the initial pawn position
                if(rowI == 2 || rowI == 7) {
                    // Place the 3 hints in the selected row 1,8. Taking into account the pawn position
                    if (i < (colF+3)){
                        strcpy(board[rowF][i], pieces[0][6]);
                        continue;
                    }

                    break;
                } else {
                    // Place the vertical and horizontal (attack) hints in any other place where the pawn is
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
        // Upward direction by subtraction operation
        rowF = rowI - i;
        colF = colI - i;

        // Ensure the hint to be placed in the row is within the top board's limits
        if (rowF >= 1) {
            // Ensure the hint to be placed in the column is within the left board's limits

            // Place the hint up left direction
            if (colF >= 1) strcpy(board[rowF][colF], pieces[0][6]);

            // Place the hint up right direction by increasing the last column position
            if (colF+2*(i) <= (SIZE-1)) strcpy(board[rowF][colF+2*(i)], pieces[0][6]);
        }

        // Downward direction by addition operation
        rowF = rowI + i;
        colF = colI + i;

        // Ensure the hint to be placed is within the bottom board's limits
        if (rowF < SIZE) {
            // Ensure the hint to be placed in the column is within the left board's limits

            // Place the hint down right direction
            if (colF < SIZE) strcpy(board[rowF][colF], pieces[0][6]);

            // Place the hint down left direction by decreasing the last column position
            if (colF-2*(i) >= 1) strcpy(board[rowF][colF-2*(i)], pieces[0][6]);
        }
    }
}

// Mark allowable movements for the knight on the board.
void knightMovements(int rowI, int colI, char board[SIZE][SIZE][LTR_SIZE]) {
    int rowF, colF;
    
    // Knight movements collection
    int knightMoves[8][2] = {
        {-2, -1}, {-1, -2}, {1, -2}, {2, -1}, // Up/down and left/right movements
        {2, 1}, {1, 2}, {-1, 2}, {-2, 1} // Up/down and right/left movements
    };
    
    // Loop each movement in the collection
    for (int i = 0; i < 8; i++) {
        // Calculate new row and column positions
        rowF = rowI + knightMoves[i][0];
        colF = colI + knightMoves[i][1];
        
        // Ensure the hint to be placed is within the top board's limits
        if (rowF >= 0 && rowF < SIZE && colF >= 0 && colF < SIZE) {
            strcpy(board[rowF][colF], pieces[0][6]);
        }
    }
}

// Mark allowable movements for the queen on the board.
void queenMovements(int rowI, int colI, char board[SIZE][SIZE][LTR_SIZE]) {
    // The queen uses the bishop and the rook hints
    bishopMovements(rowI, colI, board);
    rookMovements(rowI, colI, board);
}

// Mark allowable movements for the king on the board.
void kingMovements(int rowI, int colI, char board[SIZE][SIZE][LTR_SIZE]) {
    int rowF, colF = 1;

    // Change direction from up to down, left to right
    for (int i = -1; i < 2; i++) {    
        rowF = rowI + i; // Calculate the final row position using the current direction
        colF = colI - 1;

        for (int j = 0; j < 3; j++) {
            // Ensure the hint to be placed is within the top board's limits
            if (rowF >= 0 && rowF < SIZE && colF >= 0 && colF < SIZE) {
                // Place the hint using the current direction, horizontally and vertically, skiping the piece cell
                if (rowI != rowF || colI != colF) strcpy(board[rowF][colF], pieces[0][6]);
                colF++;
            }
        }
    }
}