
#include <stdbool.h>

#include "structs.h"
#include "initialize.h"
#include "board.h"

void initialize(struct piece wPieces[16], struct piece bPieces[16], char board[8][8]){
    /*
     Initializes all pieces, and the board
     */
    for(int i = 0; i < 8; i++) {
        wPieces[i].type = 'p';
        wPieces[i].rank = 2;
        wPieces[i].file = i+1;
    }
    for(int i = 0; i < 16; i++) {
        wPieces[i].colour = true;
        wPieces[i].alive = 1;
    }
     
    for(int i = 0; i < 8; i++) {
        bPieces[i].type = 'P';
        bPieces[i].rank = 7;
        bPieces[i].file = i+1;
    }
    for(int i = 0; i < 16; i++) {
        bPieces[i].colour = false;
        bPieces[i].alive = 1;
    }
    
    for(int i = 8; i < 16; i = i+7){
        wPieces[i].type = 'r';
        bPieces[i].type = 'R';
        wPieces[i].rank = 1;
        bPieces[i].rank = 8;
        wPieces[i].file = i+1-8;
        bPieces[i].file = i+1-8;
    }
    for(int i = 9; i < 16; i = i+5){
        wPieces[i].type = 'n';
        bPieces[i].type = 'N';
        wPieces[i].rank = 1;
        bPieces[i].rank = 8;
        wPieces[i].file = i+1-8;
        bPieces[i].file = i+1-8;
    }
    for(int i = 10; i < 14; i = i+3){
        wPieces[i].type = 'b';
        bPieces[i].type = 'B';
        wPieces[i].rank = 1;
        bPieces[i].rank = 8;
        wPieces[i].file = i+1-8;
        bPieces[i].file = i+1-8;
    }
    wPieces[11].type = 'q';
    bPieces[11].type = 'Q';
    wPieces[11].rank = 1;
    bPieces[11].rank = 8;
    wPieces[11].file = 4;
    bPieces[11].file = 4;
    

    wPieces[12].type = 'k';
    bPieces[12].type = 'K';
    wPieces[12].rank = 1;
    bPieces[12].rank = 8;
    wPieces[12].file = 5;
    bPieces[12].file = 5;
    
    updateboard(board, wPieces, bPieces);
}
