#ifndef PIECES_CONSTRAINTS_H
#define PIECES_CONSTRAINTS_H

// File headers
#include "constants.h"

int checkPosition(int rowI, int rowF, int colI, int colF, char piece);
int rook(int rowI, int rowF, int colI, int colF);
int pawn(int rowI, int rowF, int colI, int colF);
int bishop(int rowI, int rowF, int colI, int colF);
int knight(int rowI, int rowF, int colI, int colF);
int queen(int rowI, int rowF, int colI, int colF);
int king(int rowI, int rowF, int colI, int colF);

void suggestedMovements(int rowI, int colI, char piece, char board[SIZE][SIZE][LTR_SIZE]);
void rookMovements(int rowI, int colI, char board[SIZE][SIZE][LTR_SIZE]);
void pawnMovements(int rowI, int colI, char board[SIZE][SIZE][LTR_SIZE]);
void bishopMovements(int rowI, int colI, char board[SIZE][SIZE][LTR_SIZE]);
void knightMovements(int rowI, int colI, char board[SIZE][SIZE][LTR_SIZE]);
void queenMovements(int rowI, int colI, char board[SIZE][SIZE][LTR_SIZE]);
void kingMovements(int rowI, int colI, char board[SIZE][SIZE][LTR_SIZE]);

#endif  // CHESS_CONSTRAINTS_H