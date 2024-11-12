#include <string.h>
#include <stdio.h>

#include "constants.h"
#include "pieces.h"

const char* pieces[2][8] = { 
    // White pieces
    {"\u265A", "\u265B", "\u265C", "\u265D", "\u265E", "\u265F", "+", " "},
    // Black pieces
    {"\u2654", "\u2655", "\u2656", "\u2657", "\u2658", "\u2659", "+", " "}
};

void storeNewPiece(char piece, Piece* usedPieces, int* stats, int* idx) {
    int i = 0;
    
    while (i < *idx && usedPieces[i].name != piece) i++;
    
    if (usedPieces[i].name == piece){
        updatePieceStats(stats, i, usedPieces);
    } else {
        usedPieces[i] = createPieceStats(piece, stats);
        (*idx)++;
    }
}

void updatePieceStats(int* stats, int i, Piece* usedPieces) {
    usedPieces[i].successCounter += stats[0];
    usedPieces[i].failedCounter += stats[1];
    usedPieces[i].timesUsed = usedPieces[i].successCounter + usedPieces[i].failedCounter;
}

Piece createPieceStats(char piece, int* stats) {
    Piece p;
    p.name = piece;
    p.timesUsed = stats[0] + stats[1];
    p.successCounter = stats[0];
    p.failedCounter = stats[1];

    return p;
}