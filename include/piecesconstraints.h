#ifndef PIECES_CONSTRAINTS_H
#define PIECES_CONSTRAINTS_H

// File headers
#include "constants.h"

int tower(int row1, int row2, int col1, int col2);
void towerMovements(int rowI, int colI, char board[SIZE][SIZE][LTR_SIZE]);

void suggestedPositions(int rowI, int colI, char piece, char board[SIZE][SIZE][LTR_SIZE]);
int checkPosition(int row1, int row2, int col1, int col2, char piece);

#endif  // CHESS_CONSTRAINTS_H