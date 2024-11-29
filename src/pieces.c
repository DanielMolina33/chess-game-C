#include <string.h>
#include <stdio.h>

#include "constants.h"
#include "pieces.h"

// Chess pieces collection. Adding the hint and the initial empty cell characters
const char* pieces[2][8] = { 
    // Black pieces
    {"\u265A", "\u265B", "\u265C", "\u265D", "\u265E", "\u265F", "+", " "},
    // White pieces
    {"\u2654", "\u2655", "\u2656", "\u2657", "\u2658", "\u2659", "+", " "}
};

// Store a new piece into the stats
void storeNewPiece(char piece, Piece* usedPieces, int* stats, int* idx) {
    int i = 0;
    
    // Look if the given piece is already used
    while (i < *idx && usedPieces[i].name != piece) i++;
    
    // If the given piece is already used, just update its stats
    if (usedPieces[i].name == piece){
        updatePieceStats(stats, i, usedPieces);
    } else {
        // Otherwise, create that specific piece stats
        usedPieces[i] = createPieceStats(piece, stats);
        (*idx)++;
    }
}

// Update a specific piece stats
void updatePieceStats(int* stats, int i, Piece* usedPieces) {
    usedPieces[i].successCounter += stats[0];
    usedPieces[i].failedCounter += stats[1];
    usedPieces[i].timesUsed = usedPieces[i].successCounter + usedPieces[i].failedCounter;
}

// Create a specific piece stats
Piece createPieceStats(char piece, int* stats) {
    Piece p;
    p.name = piece;
    p.timesUsed = stats[0] + stats[1];
    p.successCounter = stats[0];
    p.failedCounter = stats[1];

    return p;
}