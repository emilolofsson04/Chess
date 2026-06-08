#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct piece {
    char type;
    bool colour;
    int rank;
    int file;
};

struct move {
    int startRank;
    int startFile;
    int targetRank;
    int targetFile;
    int pieceIndex;
    int colour;
};     
     
void initialize(struct piece wPieces[16],struct piece bPieces[16], char board[8][8]){
    
    for(int i = 0; i < 8; i++) {
        wPieces[i].type = 'p';
        wPieces[i].rank = 2;
        wPieces[i].file = i+1;
    }
    for(int i = 0; i < 16; i++) {
        wPieces[i].colour = true;
    }
     
    for(int i = 0; i < 8; i++) {
        bPieces[i].type = 'p';
        bPieces[i].rank = 7;
        bPieces[i].file = i+1;
    }
    for(int i = 0; i < 16; i++) {
        bPieces[i].colour = false;
    }
    
    for(int i = 8; i < 16; i = i+7){
        wPieces[i].type = 'r';
        bPieces[i].type = 'r';
        wPieces[i].rank = 1;
        bPieces[i].rank = 8;
        wPieces[i].file = i+1-8;
        bPieces[i].file = i+1-8;
    }
    for(int i = 9; i < 16; i = i+5){
        wPieces[i].type = 'b';
        bPieces[i].type = 'b';
        wPieces[i].rank = 1;
        bPieces[i].rank = 8;
        wPieces[i].file = i+1-8;
        bPieces[i].file = i+1-8;
    }
    for(int i = 10; i < 14; i = i+3){
        wPieces[i].type = 'n';
        bPieces[i].type = 'n';
        wPieces[i].rank = 1;
        bPieces[i].rank = 8;
        wPieces[i].file = i+1-8;
        bPieces[i].file = i+1-8;
    }
    wPieces[11].type = 'q';
    bPieces[11].type = 'q';
    wPieces[11].rank = 1;
    bPieces[11].rank = 8;
    wPieces[11].file = 4;
    bPieces[11].file = 4;
    

    wPieces[12].type = 'k';
    bPieces[12].type = 'k';
    wPieces[12].rank = 1;
    bPieces[12].rank = 8;
    wPieces[12].file = 5;
    bPieces[12].file = 5;
    
    int rank;
    int file;
    char type;
    for(int i = 0; i < 8; i++) {
        for(int k = 0; k < 8; k++) {
            board[i][k] = '.';
        }
    }
    for(int i = 0; i < 16; i++) {
        rank = wPieces[i].rank-1;
        file = wPieces[i].file-1;
        
        board[rank][file] = wPieces[i].type;
    }
    for(int i = 0; i < 16; i++) {
        rank = bPieces[i].rank-1;
        file = bPieces[i].file-1;
       board[rank][file] = bPieces[i].type;
    }
    
}
 void updateboard(char board[8][8]) {
    
    printf("------------------\n");
    for(int i = 0; i < 8; i++) {
        for(int k = 0; k < 8; k++) {
            printf("|");
            printf("%c", board[i][k]);

        }
        printf("|\n");
        printf("------------------\n");
    }

          

 }
struct move translate(char move[5], bool* ctp) {
    struct move inputMove;
    if(strlen(move) == 3) {
        inputMove.startFile = move[0]-'a'+1;
        inputMove.targetFile = move[0]-'a'+1;
        inputMove.startRank = 0;
        inputMove.targetRank = move[1]-'0';
        inputMove.colour = *ctp;
    }
    return inputMove;

    
}
void moveupdates(struct move legalMoves[256], int* totMov, int rank, int file, int pInd, int pcolour, int targetRank, int targetFile) {

    legalMoves[*totMov].startRank = rank;
    legalMoves[*totMov].startFile = file;
    legalMoves[*totMov].targetRank = targetRank;
    legalMoves[*totMov].targetFile = targetFile; 
    legalMoves[*totMov].colour = pcolour;
    legalMoves[*totMov].pieceIndex = pInd;
    (*totMov)++;




}
bool walk(int rank, int file, char type, char board[8][8], int length, int dir) {
    bool allowed = false;
    
    if(type =='p') {
        
        for(int i = 1; i < length+1; i++) {
            
            int targetRank = rank+dir*i;

            if(targetRank > 8 | targetRank < 1) {
                allowed = false;
                break;
            }

            if(board[targetRank-1][file-1] == '.') {
                allowed = true;

               
            }
            else {
                allowed = false;
                break;
            }
        }
    
    }
    return allowed;
}
void moveChecker(bool* ctp, int* totMov, struct move legalMoves[256], int pInd, int pcolour, char type, int rank, int file, struct piece wPieces[16], struct piece bPieces[16], char board[8][8]) {
    
    /*
    Checks all available moves for the piece.
    And returns them to legalMoves,
    with the total amount of moves.
    */
    if(type == 'p') {
        if(*ctp) {
            if(rank == 2 && walk(rank, file, type, board, 2, +1)) {
                moveupdates(legalMoves, totMov, rank, file, pInd, pcolour, rank+2, file);
            }
            if (walk(rank, file, type, board,1, +1)) {
                moveupdates(legalMoves, totMov, rank, file, pInd, pcolour, rank+1, file);
            }
        }
        else {
            if(rank == 7 && walk(rank, file, type, board, 2, -1)) {
                moveupdates(legalMoves, totMov, rank, file, pInd, pcolour, rank-2, file);
            }
            if (walk(rank, file, type, board, 1, -1)) {
                moveupdates(legalMoves, totMov, rank, file, pInd, pcolour, rank-1, file);
            }
        } 
    }
    

}

void AllLegalMoves(bool* ctp, int* totMov, struct move legalMoves[256], struct piece wPieces[16], struct piece bPieces[16], char board[8][8]) {
    /* 
    Iterates over each piece and calls moveChecker for each piece
     */
    char type;
    int rank;
    int file;
    int pieceInd;
    int pcolour;
    if(*ctp) {
        for(int i = 0; i < 16; i++) {
            type = wPieces[i].type;
            rank = wPieces[i].rank;
            file = wPieces[i].file;
            pieceInd = i;
            pcolour = 1;
            moveChecker(ctp, totMov, legalMoves, pieceInd, pcolour, type, rank, file, wPieces, bPieces, board); 

        }

    }
    else {
        for(int i = 0; i < 16; i++) {
            type = bPieces[i].type;
            rank = bPieces[i].rank;
            file = bPieces[i].file;
            pieceInd = i;
            pcolour = 0;
            moveChecker(ctp, totMov, legalMoves, pieceInd, pcolour, type, rank, file, wPieces, bPieces, board); 


        }


    }

}
void turn(bool* ctp, bool* agame, char move[5], char board[8][8], struct piece wPieces[16], struct piece bPieces[16]) {
    

    if(*ctp) {
        printf("White to move\n");         
    }
    else {
        printf("Black to move\n");
    }
    
    fgets(move,  6, stdin); // get input move
    struct move inputMove = translate(move, ctp);
    
    printf("%d\n", inputMove.targetRank);
    printf("%d\n", inputMove.startRank);
    printf("%d\n", inputMove.targetFile);
    printf("%d\n", inputMove.colour);
    // find all legal moves
    struct move legalMoves[256];
    int totalMoves = 0;
    int *totMov = &totalMoves; 
    AllLegalMoves(ctp, totMov, legalMoves, wPieces, bPieces, board);
     
    printf("%d\n",totalMoves);
    updateboard(board);

    printf("Target rank %d\n",legalMoves[7].targetRank);
    printf("Target rank conrrupted %d\n", legalMoves[8].targetRank);
    printf("Target file %d\n", legalMoves[7].targetFile);
    printf("Color %d\n", legalMoves[7].colour);
    //
    //
    // Final clean up and swap color
    if (strchr(move,'\n') == NULL) {

         while ((getchar()) != '\n');
    }
    *ctp = !*ctp;


}

int main() {
    
    bool game = true; // True while game is active
    bool colour = true; // True while whites turn, false else 
    char move[5]; // input move string
    struct piece whitePieces[16]; // white pieces
    struct piece blackPieces[16]; // black pieces
    char board[8][8]; // board

    initialize(whitePieces,blackPieces, board);
    
    
    

    while(game) {
       bool *ctp = &colour; // "color to play"
       bool *agame = &game; // active game
       turn(ctp, agame, move, board, whitePieces, blackPieces); // One turn

    }
    

    return 0;
}
