#ifndef BOARD_H
#define BOARD_H

// File headers
#include "constants.h"

void initBoard(char board[SIZE][SIZE][LTR_SIZE]);
void showBoard(char board[SIZE][SIZE][LTR_SIZE]);
void setBoardPosition(int rowF, char colFLtr, char piece[LTR_SIZE], char board[SIZE][SIZE][LTR_SIZE]);
char *getBoardPosition(char board[SIZE][SIZE][LTR_SIZE]);
void drawTop(void);
void drawColNumbers(void);
void drawRowNumbers(int row, char board[SIZE][SIZE][LTR_SIZE]);
void drawIntermediate(void);
void drawBottom(void);
void randomPosition(char piece[LTR_SIZE], char board[SIZE][SIZE][LTR_SIZE]);
void clearBoard(char board[SIZE][SIZE][LTR_SIZE]);

#endif // BOARD_H