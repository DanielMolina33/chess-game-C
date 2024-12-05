// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// File headers
#include "board.h"
#include "utils.h"
#include "pieces.h"
#include "piecesconstraints.h"

// Function to initialize the board
void initBoard(char board[SIZE][SIZE][LTR_SIZE]){
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            // Fill the matrix using a blank character
            strcpy(board[row][col], pieces[0][7]);
        }
    }
}

// Function to create and show the board
void showBoard(char board[SIZE][SIZE][LTR_SIZE]) {
    printf("\n");
    int row = 0, col = 0;

    for (row = 0; row < SIZE; row++) {
        if (row == 0) {
            // Place the numbers, from 1-8 in the first row
            drawColNumbers();
            continue;
        } else if (row == 1) {
            // Draw the first line separator
            drawTop();
        } else {
            // Draw all the board cells
            drawIntermediate();
        }

        // Place the number of the current row, from 1-8
        drawRowNumbers(row, board);

        // Draw the last line separator
        if (row == SIZE - 1) {
            drawBottom();
        }
    }

    // Separate the board from any other text
    printf("\n\n");
}

// Function to place a piece in a specific cell in the board
void setBoardPosition(int rowF, char colFLtr, char piece[LTR_SIZE], int* failedCounter, int* successCounter, char board[SIZE][SIZE][LTR_SIZE]){
    int rowColIsValid = 0;
    char* rowCol = getBoardPosition(board); // Get the position where the piece is
    int rowI = rowCol[0]-'0'; // Get the first character which is the row, from 1-8
    int colI = rowCol[1]-'0'; // Get the second character which is the column, from A-H

    int colF = convert((int) colFLtr); // Convert from letter A-H to number 1-8

    // Check if a piece was found in the board
    if(rowCol != NULL){
        // Try to move the piece to another position, given by the player
        rowColIsValid = checkPosition(rowI, rowF, colI, colF, piece[0]);
    }

    // If the movement is allowed (based on piece type) redraw the board using the new piece position
    if(rowColIsValid){
        clearBoard(board);
        strcpy(board[rowF][colF], piece);
        (*successCounter)++; // Save a success movement for stats

        showBoard(board);
    } else {
        // If the movement was wrong, notify the player and redraw the board showing the possible movements by hints
        printf("\n %c%d no es un movimiento valido\n", colFLtr, rowF);
        suggestedMovements(rowI, colI, piece[0], board);
        (*failedCounter)++; // Save a failed movement for stats

        showBoard(board);
    }
}

// Function to get the position where a piece is
char *getBoardPosition(char board[SIZE][SIZE][LTR_SIZE]){
    static char rowCol[3];

    // Loop all the cells in the board, looking for a piece
    for(int row = 1; row < SIZE; row++){
        for(int col = 1; col < SIZE; col++){
            // If is not the hint character (+) of the empty space, the piece is found
            if((strcmp(board[row][col], pieces[0][6]) != 0) && (strcmp(board[row][col], pieces[0][7]) != 0)) {
                sprintf(rowCol, "%d%d", row, col);
                return rowCol;
            }
        }
    }

    // Otherwise is null
    return NULL;
}

// Function to draw the first line separator when the board is being created
void drawTop() {
    printf("   ╔════");
    printLine(SIZE - 1, "╦════");
    printf("╗\n");
}

// Function to draw the column letters, from A-H
void drawColNumbers() {
    // Column 0 contains the markers 1-8
    for (int col = 1; col < SIZE; col++) {
        char colLtr = convert(col); // Convert from number 1-8 to letter A-H
        printf(col == 1 ? "     %c" : "    %c", colLtr);
    }
    printf("\n");
}

// Function to draw the cells separator lines
void drawIntermediate() {
    printf("   ╠════╬");
    printLine(SIZE - 2, "════╬");
    printf("════╣\n");
}

// Function to draw the row numbers and place the piece in a cell
void drawRowNumbers(int row, char board[SIZE][SIZE][LTR_SIZE]) {
    printf("%d", row); // Row 0 contains the markers A-H

    for (int col = 1; col < SIZE; col++) {
        char *piece = board[row][col];
        
        // If a piece is found in the board, then place it in the cell
        if(strcmp(piece, pieces[0][7]) != 0) {
            piece = letterToPiece(board[row][col]); // Convert the piece in its correponding icon
        }

        printf("  ║ %s", piece);
    }

    printf("  ║\n");
}

// Function to draw the last line separator when the board is being created
void drawBottom() {
    printf("   ╚═");
    printLine(SIZE - 1, "═══╩═");
    printf("═══╝");
}

// Function to place a piece in a random position
void randomPosition(char piece[LTR_SIZE], char board[SIZE][SIZE][LTR_SIZE]) {
    int min = 1, max = SIZE-1;

    // Calculate the random row and column from 1-8
    int row = min + rand() % (max - min + 1);
    int col = min + rand() % (max - min + 1);

    // place the piece into the board
    strcpy(board[row][col], piece);
    showBoard(board); // Redraw the board
}

// Function to clear the board
void clearBoard(char board[SIZE][SIZE][LTR_SIZE]){ 
    initBoard(board); // Just initialize the board once again
}