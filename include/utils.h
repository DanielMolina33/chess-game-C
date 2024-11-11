#ifndef UTILS_H
#define UTILS_H

#include "constants.h"

void initWindowsUTF8(void);
void getChar(char* msg, char* txt);
void getNumber(char* msg, int* num);
void askPiecePosition(char* msg, int* row, char* col);
char toUpper(char ltrIn);
void printLine(int count, char *str);
char *setStrDelimiter(const char *str);
char *letterToPiece(char piece[LTR_SIZE]);
int convert(int value);
int pieceColor(char clr);
int pieceType(char ltr);

#endif // UTILS_H