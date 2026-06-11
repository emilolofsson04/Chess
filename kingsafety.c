
#include "structs.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "turn.h"
#include "kingsafety.h"
#include "movegen.h"

bool walkThreat(char board[8][8], int rank, int file, int pcolour, int step, int rdir, int fdir) {
    /*
     Checks if a piece other other than knights are checking the king 
     */
    int targetFile = file + fdir*step;
    int targetRank = rank + rdir*step;
    
    if (targetFile > 8 || targetFile < 1) {
        return true;
    }
    if (targetRank > 8 || targetRank < 1) {
        return true;
    }
    
    if (isFree(board, targetRank, targetFile)) {
        return walkThreat(board, rank, file, pcolour, step+1, rdir, fdir);
    }
    else {
        if (pcolour && fdir != 0 && rdir != 0) {
            if (board[targetRank-1][targetFile-1] == 'Q' || board[targetRank-1][targetFile-1] == 'B') {
                return false;
            }
        } 
        if (pcolour && (fdir == 0 || rdir == 0)) {
            if (board[targetRank-1][targetFile-1] == 'Q' || board[targetRank-1][targetFile-1] == 'R') {
                return false;
            }
        } 
        if (!pcolour && fdir != 0 && rdir != 0) {
           if (board[targetRank-1][targetFile-1] == 'q' || board[targetRank-1][targetFile-1] == 'b') {
                return false;
            }
        } 
        if (!pcolour && (fdir == 0 || rdir == 0)) {
            if (board[targetRank-1][targetFile-1] == 'q' || board[targetRank-1][targetFile-1] == 'r') {
                return false;
            }
        } 
    }
    return true; 
}
bool knightThreat(char board[8][8], int rank, int file, int pcolour, int rdir, int fdir) {
    /*
     Checks if a knight can currently see the piece (king) 
     */
    int targetRank = rank + rdir;
    int targetFile = file + fdir;

    if (targetFile > 8 || targetFile < 1) {
        return true;
    }
    if (targetRank > 8 || targetRank < 1) {
        return true;
    }
    
    if (pcolour) {
        if (board[targetRank-1][targetFile-1] == 'N') {
            return false;
        }
    }
    else {
        if (board[targetRank-1][targetFile-1] == 'n') {
            return false;
        }
    }
    return true; 
}
bool isKingSafe(char board[8][8], int rank, int file, int pcolour) {
    /*
     Evaluates if the king is unde threat from opposig pieces
     */ 
    int rdirs[8] = { 1, -1, 0, 0, 1, 1, -1, -1};
    int fdirs[8] = { 0, 0, 1, -1, 1, -1, -1, 1};

    for (int k = 0; k < 8; k++) {
        if (!walkThreat(board, rank, file, pcolour, 1, rdirs[k], fdirs[k])) {
            return false; 
        }
    
    }
    int Rdirs[8] = { 2, 2, -2, -2, 1, -1, 1, -1};
    int Fdirs[8] = { 1, -1, 1, -1, 2, 2, -2, -2};

    for (int k = 0; k < 8; k++) {
        if (!knightThreat(board, rank, file, pcolour, Rdirs[k], Fdirs[k])){
            return false;
        }
    }
    if (pcolour) {
        if (board[rank][file-2] == 'P' || board[rank][file] == 'P') {
            return false;
        }
    }
    else {
        if (board[rank-2][file-2] == 'p' || board[rank-2][file] == 'p') {
            return false;
        }
    
    }
   return true;

}
