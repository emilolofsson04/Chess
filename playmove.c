

#include "structs.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "playmove.h"

struct move translate(char move[5], bool* ctp) {
    /*
     Converts the input move string into a move struct
     */
    struct move inputMove;
    inputMove.colour = -1;
    if(strlen(move) >= 4) {
        
        inputMove.startFile = move[0]-'a'+1;
        inputMove.targetFile = move[2]-'a'+1;
        inputMove.startRank = move[1]-'0';
        inputMove.targetRank = move[3]-'0';
        inputMove.colour = *ctp;
    }   
    return inputMove;
}
void moveupdates(struct move legalMoves[256], int* totMov, int rank, int file, int pInd, int pcolour, int targetRank, int targetFile, int capture) {
    /*
     Updates the list of legal moves
     */

    legalMoves[*totMov].startRank = rank;
    legalMoves[*totMov].startFile = file;
    legalMoves[*totMov].targetRank = targetRank;
    legalMoves[*totMov].targetFile = targetFile; 
    legalMoves[*totMov].colour = pcolour;
    legalMoves[*totMov].pieceIndex = pInd;

    if (capture == 1) {
        legalMoves[*totMov].capture = -capture;
    }
    (*totMov)++;
}


void playmove(bool* ctp, struct move playedMove, struct piece wPieces[16], struct piece bPieces[16]){

    /*
     Executes the move, by changing postion of the moved piece,
     and setting a captured piece to dead

     *  *ctp: colour to play
     *  move playedMove: struct containing move information
     *  piece wPieces: set of white pieces
     *  piece bPieces: set of black pieces
     */
    
    // Kills captured piece
    if (playedMove.capture == -1) {
        if (*ctp) {
            for (int i = 0; i < 16; i++) {
                if (bPieces[i].alive && bPieces[i].rank == playedMove.targetRank && bPieces[i].file == playedMove.targetFile) {
                    bPieces[i].alive = 0;
                    bPieces[i].rank = -1;
                    bPieces[i].file = -1;
                    break;
                }
            }
        }
        else {
            for (int i = 0; i < 16; i++) {
                if (wPieces[i].alive && wPieces[i].rank == playedMove.targetRank && wPieces[i].file == playedMove.targetFile) {
                    wPieces[i].alive = 0;
                    wPieces[i].rank = -1;
                    wPieces[i].file = -1;
                }
            }
        }
    }

    // Changing position of moved piece
    if (*ctp) {
        wPieces[playedMove.pieceIndex].rank = playedMove.targetRank;
        wPieces[playedMove.pieceIndex].file = playedMove.targetFile;
    }
    else {
        bPieces[playedMove.pieceIndex].rank = playedMove.targetRank;
        bPieces[playedMove.pieceIndex].file = playedMove.targetFile;
    }
}

