#include <stdbool.h>

#include "structs.h"
#include "initialize.h"
#include "turn.h"


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
    
    struct move playedMoves[256];

    while(game) {
       bool *ctp = &colour; // "color to play"
       bool *agame = &game; // active game
       turn(ctp, agame, move, board, whitePieces, blackPieces, it, playedMoves); // One turn
    }
    
    return 0;
}
