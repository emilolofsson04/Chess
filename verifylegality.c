#include "structs.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "turn.h"
#include "printAllMoves.h"
#include "movegen.h"
#include "kingsafety.h"
#include "board.h"
#include "playmove.h"
#include "unplaymove.h"

void verifylegality(struct move strictlylegalMoves[256], int* stotMov, bool* ctp, struct move playedMove, struct piece wPieces[16], struct piece bPieces[16], char board[8][8]){

    int rank = playedMove.startRank;
    int file = playedMove.startFile;
    int pInd = playedMove.pieceIndex;
    int pcolour = playedMove.colour;
    int targetRank = playedMove.targetRank;
    int targetFile = playedMove.targetFile;
    int capture = playedMove.capture;
    int type = playedMove.pieceType; 
    playmove(ctp, &playedMove, wPieces, bPieces);
    updateboard(board, wPieces, bPieces);
    switch (playedMove.captureType) {
        case 0:
    if (*ctp) {
        if (isKingSafe(board, wPieces[12].rank, wPieces[12].file, 1)) {
            moveupdates(strictlylegalMoves, stotMov, rank, file, pInd, pcolour, targetRank, targetFile, -capture, type);
        }
    }
    else {
        if (isKingSafe(board, bPieces[12].rank, bPieces[12].file, 0)) {
            moveupdates(strictlylegalMoves, stotMov, rank, file, pInd, pcolour, targetRank, targetFile, -capture, type);
        }
    }
    break;

        case 1: 
    if (*ctp) {
        if (isKingSafe(board, wPieces[12].rank, wPieces[12].file, 1)) {
            specialmoveupdates(strictlylegalMoves, stotMov, rank, file, pInd, pcolour, targetRank, targetFile, -capture, type,1);
        }
    }
    else {
        if (isKingSafe(board, bPieces[12].rank, bPieces[12].file, 0)) {
            specialmoveupdates(strictlylegalMoves, stotMov, rank, file, pInd, pcolour, targetRank, targetFile, -capture, type,1);
        }
    }
    
    }
    unplaymove(ctp, playedMove, wPieces, bPieces);
    updateboard(board, wPieces, bPieces); 

}
