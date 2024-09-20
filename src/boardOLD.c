// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>

// // File headers
// #include "board.h"
// #include "utils.h"
// #include "piecesconstraints.h"

// // SIMPLER VERSION
// /* void showBoard(char board[SIZE][SIZE][SIZE]){
//     int row = 0, col = 0;

//     for(row = 0; row < SIZE; row++) {
//         if(row > 0) printf("%d ", row);
//         for(col = 1; col < SIZE; col++) {
//             if(row > 0) printf("%s ", board[row][col]);
//             else printf("    %d", col);
//         }
//         printf("\n");
//     }
// } */

// void initBoard(char board[SIZE][SIZE][LTR_SIZE]){
//     for (int row = 0; row < SIZE; row++) {
//         for (int col = 0; col < SIZE; col++) {
//             strcpy(board[row][col], " ");
//         }
//     }
// }

// void showBoard(char board[SIZE][SIZE][LTR_SIZE]) {
//     printf("\n");
//     int row = 0, col = 0;

//     for (row = 0; row < SIZE; row++) {
//         if (row == 0) {
//             drawColNumbers();
//             continue;
//         } else if (row == 1) {
//             drawTop();
//         } else {
//             drawIntermediate();
//         }

//         drawRowNumbers(row, col, board);

//         if (row == SIZE - 1) {
//             drawBottom();
//         }
//     }

//     printf("\n\n");
// }

// void setBoardPosition(char rowLtr, int col, char piece[LTR_SIZE], char board[SIZE][SIZE][LTR_SIZE]) {
//     int colRowIsValid = 0;
//     char *colRow = getBoardPosition(board);
//     int row = convert(rowLtr); // Convert from letter A-H to number 1-8

//     // if (x != 0 || y != 0)
//     if(colRow != NULL){
//         if(piece[0] == 'T'){
//             colRowIsValid = tower(row, colRow[0]-'0', col, colRow[1]-'0');
//             // strcpy(board[x][y], " ");
//         }
//     }

//     if(colRowIsValid){
//         clearBoard(colRow[0]-'0', colRow[1]-'0', board);
//         strcpy(board[row][col], piece);
//         showBoard(board);
//     } else {
//         printf("\n %c%d no es un movimiento valido", convert(row), col);
//     }
// }

// char *getBoardPosition(char board[SIZE][SIZE][LTR_SIZE]){
//     static char colRow[3];

//     for(int row = 1; row < SIZE; row++){
//         for(int col = 1; col < SIZE; col++){
//             if(strcmp(board[row][col], " ") != 0){
//                 sprintf(colRow, "%d%d", row, col);
//                 return colRow;
//             }
//         }
//     }

//     return NULL;
// }

// void drawTop() {
//     printf("   ╔════");
//     printLine(SIZE - 1, "╦════");
//     printf("╗\n");
// }

// void drawColNumbers() {
//     for (int col = 1; col < SIZE; col++) {
//         char colLtr = convert(col);
//         printf(col == 1 ? "     %c" : "    %c", colLtr);
//     }
//     printf("\n");
// }

// void drawIntermediate() {
//     printf("   ╠════╬");
//     printLine(SIZE - 2, "════╬");
//     printf("════╣\n");
// }

// void drawRowNumbers(int row, int col, char board[SIZE][SIZE][LTR_SIZE]) {
//     // char rowLtr = convert(row); // Convert from number to letter

//     printf("%d", row); // Col 0 contains the markers A-H

//     for (col = 1; col < SIZE; col++) {
//         char *piece = board[row][col];

//         if(strcmp(piece, " ") != 0) {
//             piece = letterToPiece(board[row][col]);
//         }

//         printf("  ║ %s", piece);
//     }

//     printf("  ║\n");
// }

// void drawBottom() {
//     printf("   ╚═");
//     printLine(SIZE - 1, "═══╩═");
//     printf("═══╝");
// }

// void randomPosition(int min, int max, char piece[LTR_SIZE], char board[SIZE][SIZE][LTR_SIZE]) {
//     int row = min + rand() % (max - min + 1);
//     int col = min + rand() % (max - min + 1);

//     strcpy(board[row][col], piece);
//     showBoard(board);
// }

// void clearBoard(int row, int col, char board[SIZE][SIZE][LTR_SIZE]){
//     strcpy(board[row][col], " ");
// }