

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "structs.h"
#include "initialize.h"
#include "turn.h"
#include "printAllMoves.h"
#include "movegen.h"
#include "kingsafety.h"
#include "board.h"
#include "playmove.h"

void printBoard(char board[8][8]) {
    
    printf("------------------\n");
    for(int i = 7; i > -1; i--) {
        for(int k = 0; k < 8; k++) {
            printf("|");
            printf("%c", board[i][k]);
        }
        printf("|\n");
        printf("------------------\n");
    }
}

void updateboard(char board[8][8], struct piece wPieces[16], struct piece bPieces[16]) {

    /*
     Redraws the board 
     */
    
    int rank;
    int file;
    for(int i = 0; i < 8; i++) {
        for(int k = 0; k < 8; k++) {
            board[i][k] = '.';
        }
    }
    for(int i = 0; i < 16; i++) {
        if (wPieces[i].alive) {
            rank = wPieces[i].rank-1;
            file = wPieces[i].file-1;
        
            board[rank][file] = wPieces[i].type;
        }
    }
    for(int i = 0; i < 16; i++) {
        if (bPieces[i].alive) {
            rank = bPieces[i].rank-1;
            file = bPieces[i].file-1;
            board[rank][file] = bPieces[i].type;
        }
    }
}
