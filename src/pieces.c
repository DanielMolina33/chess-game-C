#include <string.h>
#include "constants.h"

const char* pieces[2][8] = { 
    // White pieces
    {"\u265A", "\u265B", "\u265C", "\u265D", "\u265E", "\u265F", "+", " "},
    // Black pieces
    {"\u2654", "\u2655", "\u2656", "\u2657", "\u2658", "\u2659", "+", " "}
};


void storeNewPiece(char piece, char* usedPieces) {
    int n = strlen(usedPieces);
    int pieceFound = 0;
    
    for (int i = 0; i < n; i++) {
        int currentPiece = usedPieces[i];
        if (piece == currentPiece) pieceFound = 1;
    }
    
    
}