

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
#include "verifylegality.h"

void turn(bool* ctp, bool* agame, char move[6], char board[8][8], struct piece wPieces[16], struct piece bPieces[16], int* iteration, struct move playedMoves[256]) {
    
    // Prompt for whoevers turn it is
    if(*ctp) {
        printf("White to move\n");         
    }
    else {
        printf("Black to move\n");
    }
    
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

 
    struct move Moves[256];    // Initialize a set of legal moves
    int totalMoves = 0;             // The total amount of moves
    int *totMov = &totalMoves; 

    struct move legalMoves[256]; // Initialize a set of strictly legal moves that have been filtered
    int totalLegalMoves = 0;    
    int *totLegMov = &totalLegalMoves;

    // Finds all legal moves in position
    int k = (*iteration > 1) ? *iteration - 1 : 0;
    AllMoves(ctp, totMov, Moves, wPieces, bPieces, board, &playedMoves[k]); 
    for (int i = 0; i < *totMov; i++) {
        verifylegality(legalMoves, totLegMov, ctp, Moves[i], wPieces, bPieces, board);
    }
    

    printf("I found %d moves\n",totalMoves);
    printf("I found %d legal moves\n",totalLegalMoves);

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

        // Prints all moves if input ?
        if (strcmp(move,"?\n")  == 0) {
            printf("All Moves: ");
            printAllMoves(Moves, totMov);
            printf("FF.\n");
            continue;
        }
        // Prints all legal moves if input ??
        if (strcmp(move,"??\n")  == 0) {
            printf("Legal Moves: ");
            printAllMoves(legalMoves, totLegMov);
            printf("FF.\n");
            continue;
        }
        // Prints all played moves if input ???
        if (strcmp(move,"???\n")  == 0) {
            printf("Played Moves: ");
            printAllMoves(playedMoves, iteration);
            printf("...\n");
            continue;
        }
    
        if (inputMove.colour != -1  ) { // Checks if the given move was correct
            playedMove = isMoveLegal(totLegMov, inputMove, legalMoves);
            if (playedMove.pieceIndex != -1) {
                playmove(ctp, &playedMove, wPieces, bPieces);        
                updateboard(board, wPieces, bPieces);
                printBoard(board);
                waitForMove = 0;
            }
        }
    }

    // Final clean up and swap color
    playedMoves[*iteration] = playedMove;
    if (strchr(move,'\n') == NULL) {

         while ((getchar()) != '\n');
    }
    *ctp = !*ctp;
    (*iteration)++;
}

