

#include "structs.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "movegen.h"
#include "board.h"
#include "playmove.h"

bool isFree(char board[8][8], int targetRank, int targetFile ) {
    /*
     Checks if a square is free or occupied
     */
    if(board[targetRank-1][targetFile-1] != '.') {
        return false;
    }
    else {
        return true;
    }
}
bool pawnmove(bool* ctp, int* totMov, struct move legalMoves[256], int pInd, int pcolour, char type, int rank, int file, char board[8][8], int length,  int rdir, int fdir, int step) {
    /*
     Checks if a pawn move is legal,
     including captures. Any found move
     is added to legal moves.
     */

    int targetRank = rank + rdir*step;
    int targetFile = file + fdir*step;
    
    if(targetRank > 8 || targetRank < 1) {
         return false;
    }
     if(targetFile > 8 || targetFile < 1) {
         return false;
    }

    if (step > length) {
        return false;

    }

    if (isFree(board, targetRank, targetFile) && fdir == 0) {
        
        moveupdates(legalMoves, totMov, rank, file, pInd, pcolour, rank + step * rdir, file + step * fdir, 0);
        return pawnmove(ctp, totMov, legalMoves, pInd, pcolour, type, rank, file, board, length, rdir, fdir, step+1);
    }

    else if (!isFree(board, targetRank, targetFile)) {
        if (pcolour) {
            if (fdir != 0 && isupper(board[targetRank-1][targetFile-1])) {

                        moveupdates(legalMoves, totMov, rank, file, pInd, pcolour, targetRank, targetFile, 1);
                        return false;
            }
        }
        else {
            if (fdir != 0 && islower(board[targetRank-1][targetFile-1])) {

                        moveupdates(legalMoves, totMov, rank, file, pInd, pcolour, targetRank, targetFile, 1);
                        return false;
            }
        }   
    }
    return false; 
}




bool knightmove(int* totMov, struct move legalMoves[256], int pInd, int pcolour, int rank, int file, char board[8][8], int rdir, int fdir) {
    /*
     Check if a knight move is possible,
     including captures. If so, it adds to 
     legal moves.
     */
    
    int targetRank = rank + rdir;
    int targetFile = file + fdir;
    if (targetRank > 8 || targetRank < 1) {
        return false;
    }
    if (targetFile > 8 || targetFile < 1) {
        return false;
    }

    if (isFree(board, targetRank, targetFile)) {
        moveupdates(legalMoves, totMov, rank, file, pInd, pcolour, targetRank, targetFile, 0);
        return true;
    }
    
    else if (pcolour) {
        if (isupper(board[targetRank-1][targetFile-1])) {
            moveupdates(legalMoves, totMov, rank, file, pInd, pcolour, targetRank, targetFile, 1);
        }
    }
    else {
        if (islower(board[targetRank-1][targetFile-1])) {

            moveupdates(legalMoves, totMov, rank, file, pInd, pcolour, targetRank, targetFile, 1);
            return false;
        }
    }
    return false;
}

bool legalMove(bool* ctp, int* totMov, struct move legalMoves[256], int pInd, int pcolour, char type, int rank, int file, char board[8][8], int length,  int rdir, int fdir, int step) {

    /*
     Checks legal moves in one direction from a piece,
     including captures. Ending when hitting a wall
     or a friendly piece. Any found move is 
     added to legal moves.
     */

    int targetRank = rank + rdir*step;
    int targetFile = file + fdir*step;
    
    if(targetRank > 8 || targetRank < 1) {
         return false;
    }
     if(targetFile > 8 || targetFile < 1) {
         return false;
    }

    if (step > length) {
        return false;

    }

    if (isFree(board, targetRank, targetFile)) {
        
        moveupdates(legalMoves, totMov, rank, file, pInd, pcolour, rank + step * rdir, file + step * fdir, 0);
        return legalMove(ctp, totMov, legalMoves, pInd, pcolour, type, rank, file, board, length, rdir, fdir, step+1);
    }

    else if (pcolour) {
        if (isupper(board[targetRank-1][targetFile-1])) {

                    moveupdates(legalMoves, totMov, rank, file, pInd, pcolour, targetRank, targetFile, 1);
                    return false;
        }
    }
    else {
        if (islower(board[targetRank-1][targetFile-1])) {

                    moveupdates(legalMoves, totMov, rank, file, pInd, pcolour, targetRank, targetFile, 1);
                    return false;
        }
    }
    return false; 
}


void moveChecker(bool* ctp, int* totMov, struct move legalMoves[256], int pInd, int pcolour, char type, int rank, int file, char board[8][8]) {

    
    /*
    Checks all available moves for the piece.
    And returns them to legalMoves,
    with the total amount of moves.
    */
    
    if(type == 'p' || type == 'P') {
        if(pcolour) {
            if(rank == 2 ) { // 2 steps from first rank
                pawnmove(ctp, totMov, legalMoves, pInd, pcolour, type, rank, file, board, 2, +1, 0, 1); 
            }
            else {    
                pawnmove(ctp, totMov, legalMoves, pInd, pcolour, type, rank, file, board, 1, +1, 0, 1); 
            }
            // pawn captures
            pawnmove(ctp, totMov, legalMoves, pInd, pcolour, type, rank, file, board, 1, 1, 1, 1);
            pawnmove(ctp, totMov, legalMoves, pInd, pcolour, type, rank, file, board, 1, 1, -1, 1);

        }
        else {
             if(rank == 7 ) { // 2 steps from first rank
                pawnmove(ctp, totMov, legalMoves, pInd, pcolour, type, rank, file, board, 2, -1, 0, 1); 
            }
            else {    
                pawnmove(ctp, totMov, legalMoves, pInd, pcolour, type, rank, file, board, 1, -1, 0, 1); 
            }
            // pawn captures
            pawnmove(ctp, totMov, legalMoves, pInd, pcolour, type, rank, file, board, 1, -1, 1, 1);
            pawnmove(ctp, totMov, legalMoves, pInd, pcolour, type, rank, file, board, 1, -1, -1, 1);

        } 
    }
    if (type == 'r' || type == 'R') {
        int rdirs[4] = { 1, -1, 0, 0};
        int fdirs[4] = { 0, 0, 1, -1};

        for (int k = 0; k < 4; k++) {
            legalMove(ctp, totMov, legalMoves, pInd, pcolour, type, rank, file, board, 8, rdirs[k], fdirs[k], 1); 
        }
    }
    if (type == 'b' || type == 'B') {
        int rdirs[4] = { 1, 1, -1, -1};
        int fdirs[4] = { 1, -1, -1, 1};
        for (int k = 0; k < 4; k++) {
            
            legalMove(ctp, totMov, legalMoves, pInd, pcolour, type, rank, file, board, 8, rdirs[k], fdirs[k], 1);

        }
    }
    if (type == 'q' || type == 'Q') {
        int rdirs[8] = { 1, -1, 0, 0, 1, 1, -1, -1};
        int fdirs[8] = { 0, 0, 1, -1, 1, -1, -1, 1};

        for (int k = 0; k < 8; k++) {
            legalMove(ctp, totMov, legalMoves, pInd, pcolour, type, rank, file, board, 8, rdirs[k], fdirs[k], 1);
        }
    }
    if (type == 'n' || type == 'N') {
        int rdirs[8] = { 2, 2, -2, -2, 1, -1, 1, -1};
        int fdirs[8] = { 1, -1, 1, -1, 2, 2, -2, -2};

        for (int k = 0; k < 8; k++) {
            knightmove(totMov, legalMoves, pInd, pcolour, rank, file, board, rdirs[k], fdirs[k]);
        }
    }
    if (type == 'k' || type == 'K') {
        int rdirs[8] = { 1, -1, 0, 0, 1, 1, -1, -1};
        int fdirs[8] = { 0, 0, 1, -1, 1, -1, -1, 1};

        for (int k = 0; k < 8; k++) {
            legalMove(ctp, totMov, legalMoves, pInd, pcolour, type, rank, file, board, 1, rdirs[k], fdirs[k], 1);
        }
    }
}
void AllLegalMoves(bool* ctp, int* totMov, struct move legalMoves[256], struct piece wPieces[16], struct piece bPieces[16], char board[8][8]) {
    /* 
     Iterates over each piece,
     and calls moveChecker for each piece,
     which finds and totals legal moves.
     */
    char type;
    int rank;
    int file;
    int pieceInd;
    int pcolour;
    if(*ctp) {
        for(int i = 0; i < 16; i++) {
            if (wPieces[i].alive) {
                type = wPieces[i].type;
                rank = wPieces[i].rank;
                file = wPieces[i].file;
                pieceInd = i;
                pcolour = 1;
                moveChecker(ctp, totMov, legalMoves, pieceInd, pcolour, type, rank, file, board); 
            }
        }
    }
    else {
        for(int i = 0; i < 16; i++) {
            if (bPieces[i].alive) {
                type = bPieces[i].type;
                rank = bPieces[i].rank;
                file = bPieces[i].file;
                pieceInd = i;
                pcolour = 0;
                moveChecker(ctp, totMov, legalMoves, pieceInd, pcolour, type, rank, file, board); 
            }
        }
    }
}
struct move isMoveLegal(int* totMov, struct move inputMove, struct move legalMoves[256]) {
    /* 
     Checks if the input move is among the legal moves, 
     and if so, returns the struct of the legal move.

     *  *totMov: total amount of legal moves
     *  move inputMove: the input move
     *  move legalMoves: all legal moves
     */

    struct move dummymove;
    dummymove.pieceIndex = -1;
    int rank = inputMove.startRank;
    int file = inputMove.startFile;
    int targetRank = inputMove.targetRank;
    int targetFile = inputMove.targetFile;

   
    for (int i = 0; i < *totMov; i++) {
            
        if (legalMoves[i].startRank == rank && legalMoves[i].targetRank == targetRank && legalMoves[i].startFile == file && legalMoves[i].targetFile == targetFile) {
                return legalMoves[i];
        }
     }
    return dummymove;
}

