#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


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
    int colour;
    int capture;
};     

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
    printBoard(board);
}

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

void printAllMoves(struct move legalMoves[256], int* totMov) {
    /*
      Prints all possible moves if prompted
     */
    char newmove[5]; 
    printf("Playable moves: ");
    for (int i = 0; i < *totMov; i++) {
        newmove[0] = legalMoves[i].startFile +'a' -1;
        newmove[1] = legalMoves[i].startRank + '0';
        newmove[2] = legalMoves[i].targetFile +'a' -1;
        newmove[3] = legalMoves[i].targetRank + '0';
        newmove[4] = '\0';
        printf("%s, ", newmove);
    }
    printf("FF.\n");
}
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
void turn(bool* ctp, bool* agame, char move[6], char board[8][8], struct piece wPieces[16], struct piece bPieces[16], int* iteration) {
    
    // Prompt for whoevers turn it is
    if(*ctp) {
        printf("White to move\n");         
    }
    else {
        printf("Black to move\n");
    }
    
    struct move legalMoves[256];    // Initialize a set of legal moves
    int totalMoves = 0;             // The total amount of moves
    int *totMov = &totalMoves; 

    struct move strictlylegalMoves; // Initialize a set of strictly legal moves that have been filtered
    int stotalMoves = 0;    
    int *stotMov = &totalMoves;

    // Finds all legal moves in position
    AllLegalMoves(ctp, totMov, legalMoves, wPieces, bPieces, board); 
    // filterLegalMoves(ctp, totMov, legalMoves, wPieces, bPieces, board, stotMov, strictlylegalMoves);
    printf("I found %d playable moves\n",totalMoves);
    if (*ctp) {
        if (!isKingSafe(board, wPieces[12].rank, wPieces[12].file, 1)) {
            printf("White is in check\n");
        }
    }
    else {

        if (!isKingSafe(board, bPieces[12].rank, bPieces[12].file, 0)) {
            printf("Black is in check\n");
        }
    }
    // Prompt user for move
    int waitForMove = 1;
    struct move inputMove;
    struct move playedMove;
    while (waitForMove) {

        fgets(move,  6, stdin); // get input move
        inputMove = translate(move, ctp);
        
        // Forfeits game if input FF
        if (strcmp(move,"FF\n") == 0) {
            if (*ctp) {
                printf("Game over - Black wins \n");
            }
            else {
                printf("Game over - White wins \n");
            }
            *agame = 0;
            break;
        }

        // Prints all possible moves if input ?
        if (strcmp(move,"?\n")  == 0) {
            printAllMoves(legalMoves, totMov);
            continue;
        }


        if (inputMove.colour != -1  ) { // Checks if the given move was correct
            playedMove = isMoveLegal(totMov, inputMove, legalMoves);
            if (playedMove.pieceIndex != -1) {
                playmove(ctp, playedMove, wPieces, bPieces);        
                updateboard(board, wPieces, bPieces);
                waitForMove = 0;
            }
        }
    }

    // Final clean up and swap color
    if (strchr(move,'\n') == NULL) {

         while ((getchar()) != '\n');
    }
    *ctp = !*ctp;
    (*iteration)++;
}

int main() {
    
    bool game = true; // True while game is active
    bool colour = true; // True while whites turn, false else 
    char move[6]; // input move string
    struct piece whitePieces[16]; // white pieces
    struct piece blackPieces[16]; // black pieces
    char board[8][8]; // board

    initialize(whitePieces,blackPieces, board); // Sets up the pieces and board for turn 1
    
    int iteration = 0;  // Keeps track of amount of turns
    int *it = &iteration; 
   
    while(game) {
       bool *ctp = &colour; // "color to play"
       bool *agame = &game; // active game
       turn(ctp, agame, move, board, whitePieces, blackPieces, it); // One turn
    }
    
    return 0;
}

