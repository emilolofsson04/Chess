

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
void moveupdates(struct move legalMoves[256], int* totMov, int rank, int file, int pInd, int pcolour, int targetRank, int targetFile, int capture, char type) {
    /*
     Updates the list of legal moves
     */

    legalMoves[*totMov].startRank = rank;
    legalMoves[*totMov].startFile = file;
    legalMoves[*totMov].targetRank = targetRank;
    legalMoves[*totMov].targetFile = targetFile; 
    legalMoves[*totMov].colour = pcolour;
    legalMoves[*totMov].pieceType = type;
    legalMoves[*totMov].pieceIndex = pInd;
    legalMoves[*totMov].capturedIndex = -1; // Changed later if a piece was captured
    legalMoves[*totMov].capture = 0;
    if (capture == 1) {
        legalMoves[*totMov].capture = -capture;
    }
    legalMoves[*totMov].captureType = 0; // standard capture
    (*totMov)++;
}

void specialmoveupdates(struct move legalMoves[256], int* totMov, int rank, int file, int pInd, int pcolour, int targetRank, int targetFile, int capture, char type, int capturetype) {
    /*
     Updates the list of legal moves
     */

    legalMoves[*totMov].startRank = rank;
    legalMoves[*totMov].startFile = file;
    legalMoves[*totMov].targetRank = targetRank;
    legalMoves[*totMov].targetFile = targetFile; 
    legalMoves[*totMov].colour = pcolour;
    legalMoves[*totMov].pieceType = type;
    legalMoves[*totMov].pieceIndex = pInd;
    legalMoves[*totMov].capturedIndex = -1; // Changed later if a piece was captured
    legalMoves[*totMov].capture = 0;
    if (capture == 1) {
        legalMoves[*totMov].capture = -capture;
    }
    legalMoves[*totMov].captureType = capturetype; // special capture
    (*totMov)++;
}



void playmove(bool* ctp, struct move playedMove[1], struct piece wPieces[16], struct piece bPieces[16]){

    /*
     Executes the move, by changing postion of the moved piece,
     and setting a captured piece to dead

     *  *ctp: colour to play
     *  move playedMove: struct containing move information
     *  piece wPieces: set of white pieces
     *  piece bPieces: set of black pieces
     */

    // Switch case for handling normal captures and special moves (en passant) 
    int captureRank = 0;
    switch (playedMove[0].captureType) {
    case 0:
        captureRank = playedMove[0].targetRank; // In a standard capture, the piece is on the target square
        break;
    case 1:
        captureRank = playedMove[0].startRank; // In en passant, the piece is on the starting Rank
        break;
    }

    // Kills captured piece
    if (playedMove[0].capture == -1) {
            if (*ctp) {
                for (int i = 0; i < 16; i++) {
                    if (bPieces[i].alive && bPieces[i].rank == captureRank && bPieces[i].file == playedMove[0].targetFile) {
                        bPieces[i].alive = 0;
                        bPieces[i].rank = -1;
                        bPieces[i].file = -1;
                        playedMove[0].capturedIndex = i;
                        break;
                    }
                }
            }
            else {
                for (int i = 0; i < 16; i++) {
                    if (wPieces[i].alive && wPieces[i].rank == captureRank && wPieces[i].file == playedMove[0].targetFile) {
                        wPieces[i].alive = 0;
                        wPieces[i].rank = -1;
                        wPieces[i].file = -1;   
                        playedMove[0].capturedIndex = i;
                    break;
                    }
                }
            }
        }

    // Changing position of moved piece
    if (*ctp) {
        wPieces[playedMove[0].pieceIndex].rank = playedMove[0].targetRank;
        wPieces[playedMove[0].pieceIndex].file = playedMove[0].targetFile;
    }
    else {
        bPieces[playedMove[0].pieceIndex].rank = playedMove[0].targetRank;
        bPieces[playedMove[0].pieceIndex].file = playedMove[0].targetFile;
    }


}

