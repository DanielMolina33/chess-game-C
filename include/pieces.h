#ifndef PIECES_H
#define PIECES_H

typedef struct Piece {
    char name;
    int timesUsed;
    int successCounter;
    int failedCounter;
} Piece;

void storeNewPiece(char, Piece*, int*, int*);
void updatePieceStats(int*, int, Piece*);
Piece createPieceStats(char, int*);

#endif // PIECES_H