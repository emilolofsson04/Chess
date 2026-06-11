#ifndef PLAYMOVE_H
#define PLAYMOVE_H


struct move translate(char move[5], bool* ctp);
void moveupdates(struct move legalMoves[256], int* totMov, int rank, int file, int pInd, int pcolour, int targetRank, int targetFile, int capture);
void playmove(bool* ctp, struct move playedMove, struct piece wPieces[16], struct piece bPieces[16]);
#endif

