

#include "structs.h"
#include <stdio.h>
#include <string.h>

#include "printAllMoves.h"

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
