// Set UTF-8 when OS is windows
#ifdef _WIN32
#include <Windows.h>
#endif

// Libraries
#include <stdio.h>
#include <string.h>

// File headers
#include "utils.h"

// Set UTF-8 encoding for console output when a windows OS is used
void initWindowsUTF8() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
}

// Request a char from input, using a message
void getChar(char* msg, char* txt) {
    printf("%s ", msg);
    scanf(" %c", txt);
}

// Request a number from input, using a message
void getNumber(char* msg, int* num) {
    printf("%s ", msg);
    scanf(" %d", num);
}

// Request a piece position from input, using a message
void askPiecePosition(char* msg, int* row, char* col) {
    printf("%s ", msg);
    scanf(" %c%d", col, row); // Format rowColumn, like Excel, e.g. A1
}

// Convert number to letter (1 to 8) or letter to number (A to H) using ASCII
int convert(int value) {
    if (value >= 1 && value <= 8) {
        return 'A' + (value - 1);  // Convert number to letter
    } else if (value >= 'A' && value <= 'H') {
        return value - 'A' + 1;  // Convert letter to number
    }
    return 0;  // Return 0 for invalid inputs
}

// Converts a single ascii character into upper case
char toUpper(char ltrIn) {
    int DIFF = 32;
    return (ltrIn >= 97 && ltrIn <= 122) ? ltrIn - DIFF : ltrIn;
}

// Takes a string and place a character to separate the characters. It uses "," comma
char *setStrDelimiter(const char *str) {
    static char strOut[256]; // Static buffer for the result
    size_t len = strlen(str);

    strOut[0] = '\0'; // Initialize the buffer

    for (size_t i = 0; i < len; i++) {
        char buffer[5]; // Temporary buffer for one character and a comma
        snprintf(buffer, sizeof(buffer), "%c, ", str[i]); // Append a comma
        strcat(strOut, buffer); // Append to the result buffer
    }

    // Remove the last comma if necessary
    if (len > 0) {
        strOut[strlen(strOut) - 2] = '\0';  // Replace the last comma with null terminator
    }

    return strOut;
}

// Used to print characters for the board construction
void printLine(int count, char *str) {
    for (int i = 1; i < count; i++) {
        printf("%s", str);
    }
}

// Takes a piece string "TB (Torre Blanca)" and looks for its corresponding icon and color
char* letterToPiece(char piece[LTR_SIZE]) {
    int ltrIdx = pieceType(piece[0]);
    int clrIdx = pieceColor(piece[1]);
    static char outPiece[PIECE_SIZE];

    strncpy(outPiece, pieces[clrIdx][ltrIdx], sizeof(outPiece)-1);
    outPiece[sizeof(outPiece) - 1] = '\0';

    return outPiece;
}

// Takes a piece color and assigns a number (index) to it
int pieceColor(char clr){
    switch(clr){
        case 'B': return 1;
        default: return 0; // Default black
    }
}

// Takes a piece letter and assigns a number (index) to it
int pieceType(char ltr){
    switch (ltr) {
        case 'R': return 0;
        case 'Q': return 1;
        case 'T': return 2;
        case 'A': return 3;
        case 'C': return 4;
        case 'P': return 5;
        case '+': return 6;
        default: return 7; // Default " "
    }
}