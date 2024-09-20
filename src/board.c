#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// File headers
#include "board.h"
#include "utils.h"
#include "piecesconstraints.h"

// SIMPLER VERSION
/* void showBoard(char board[SIZE][SIZE][SIZE]){
    int row = 0, col = 0;

    for(row = 0; row < SIZE; row++) {
        if(row > 0) printf("%d ", row);
        for(col = 1; col < SIZE; col++) {
            if(row > 0) printf("%s ", board[row][col]);
            else printf("    %d", col);
        }
        printf("\n");
    }
} */

void initBoard(char board[SIZE][SIZE][LTR_SIZE]){
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            strcpy(board[row][col], pieces[0][7]);
        }
    }
}

void showBoard(char board[SIZE][SIZE][LTR_SIZE]) {
    printf("\n");
    int row = 0, col = 0;

    for (row = 0; row < SIZE; row++) {
        if (row == 0) {
            drawColNumbers();
            continue;
        } else if (row == 1) {
            drawTop();
        } else {
            drawIntermediate();
        }

        drawRowNumbers(row, board);

        if (row == SIZE - 1) {
            drawBottom();
        }
    }

    printf("\n\n");
}

void setBoardPosition(char rowF, int colFLtr, char piece[LTR_SIZE], char board[SIZE][SIZE][LTR_SIZE]){
    int rowColIsValid = 0;
    char* rowCol = getBoardPosition(board);
    int rowI = rowCol[0]-'0';
    int colI = rowCol[1]-'0';
    int colF = convert(colFLtr); // Convert from letter A-H to number 1-8

    if(rowCol != NULL){
        // if(piece[0] == 'T'){
            // printf("colI: %d\n", colI);
            // printf("rowI: %d\n", rowI);
            rowColIsValid = checkPosition(rowI, rowF, colI, colF, piece[0]);
            // printf("isValid: %d\n", rowColIsValid);
            // strcpy(board[x][y], " ");
        // }
    }

    if(rowColIsValid){
        clearBoard(board);
        strcpy(board[rowF][colF], piece);
        showBoard(board);
    } else {
        // Show possible movements
        printf("\n %c%d no es un movimiento valido", colFLtr, rowF);
        suggestedPositions(rowI, colI, piece[0], board);
        showBoard(board);
    }
}

char *getBoardPosition(char board[SIZE][SIZE][LTR_SIZE]){
    static char rowCol[3];

    for(int row = 1; row < SIZE; row++){
        for(int col = 1; col < SIZE; col++){
            if((strcmp(board[row][col], pieces[0][6]) != 0) && (strcmp(board[row][col], pieces[0][7]) != 0)) {
                sprintf(rowCol, "%d%d", row, col);
                return rowCol;
            }
        }
    }

    return NULL;
}

void drawTop() {
    printf("   ╔════");
    printLine(SIZE - 1, "╦════");
    printf("╗\n");
}

void drawColNumbers() {
    // Column 0 contains the markers 1-8
    for (int col = 1; col < SIZE; col++) {
        char colLtr = convert(col);
        printf(col == 1 ? "     %c" : "    %c", colLtr);
    }
    printf("\n");
}

void drawIntermediate() {
    printf("   ╠════╬");
    printLine(SIZE - 2, "════╬");
    printf("════╣\n");
}

void drawRowNumbers(int row, char board[SIZE][SIZE][LTR_SIZE]) {
    printf("%d", row); // Row 0 contains the markers A-H

    for (int col = 1; col < SIZE; col++) {
        char *piece = board[row][col];

        if(strcmp(piece, pieces[0][7]) != 0) {
            piece = letterToPiece(board[row][col]);
        }

        printf("  ║ %s", piece);
    }

    printf("  ║\n");
}

void drawBottom() {
    printf("   ╚═");
    printLine(SIZE - 1, "═══╩═");
    printf("═══╝");
}

void randomPosition(char piece[LTR_SIZE], char board[SIZE][SIZE][LTR_SIZE]) {
    int min = 1, max = SIZE-1;
    int row = min + rand() % (max - min + 1);
    int col = min + rand() % (max - min + 1);

    strcpy(board[row][col], piece);
    showBoard(board);
}

void clearBoard(char board[SIZE][SIZE][LTR_SIZE]){ 
    initBoard(board);
}