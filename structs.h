#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdbool.h>

struct piece {
    char type;
    bool colour;
    int rank;
    int file;
    int alive;
};

struct move {
    int startRank;
    int startFile;
    int targetRank;
    int targetFile;
    int pieceIndex;
    int pieceType;
    int colour;
    int capture;
    int capturedIndex;
    int captureType;
};     
 
#endif
