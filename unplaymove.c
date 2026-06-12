
#include "structs.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "playmove.h"
#include "unplaymove.h"

void unplaymove(bool* ctp, struct move playedMove, struct piece wPieces[16], struct piece bPieces[16]){

    /*
     unExecutes the move, by changing postion of the moved piece,
     and setting a captured piece to alive

     *  *ctp: colour to play
     *  move playedMove: struct containing move information
     *  piece wPieces: set of white pieces
     *  piece bPieces: set of black pieces
     */
    
    int i = playedMove.capturedIndex;
    int capturedRank = -1;
  
    // Switch case for handling normal and special moves
    switch (playedMove.captureType) {
        case 0:
            capturedRank = playedMove.targetRank; // Normally the captured piece is on the target square
            break;
        case 1:
            capturedRank = playedMove.startRank; // In en passant, the captured piece is on the starting rank
            break;
    }


    // Alives captured piece
    if (playedMove.capture == -1) {
        if (*ctp) {
            bPieces[i].alive = 1;
            bPieces[i].rank = capturedRank;
            bPieces[i].file = playedMove.targetFile;
        }
        else {
            wPieces[i].alive = 1;
            wPieces[i].rank = capturedRank;
            wPieces[i].file = playedMove.targetFile;   
        }
    }

    // Changing position of moved piece
    if (*ctp) {
        wPieces[playedMove.pieceIndex].rank = playedMove.startRank;
        wPieces[playedMove.pieceIndex].file = playedMove.startFile;
    }
    else {
        bPieces[playedMove.pieceIndex].rank = playedMove.startRank;
        bPieces[playedMove.pieceIndex].file = playedMove.startFile;
    }
   
}
