#ifndef MOVEGEN_H
#define MOVEGEN_H

bool isFree(char board[8][8], int targetRank, int targetFile );
bool pawnmove(bool* ctp, int* totMov, struct move legalMoves[256], int pInd, int pcolour, char type, int rank, int file, char board[8][8], int length,  int rdir, int fdir, int step, struct move* playedMoves);

bool legalMove(bool* ctp, int* totMov, struct move legalMoves[256], int pInd, int pcolour, char type, int rank, int file, char board[8][8], int length,  int rdir, int fdir, int step);

void AllMoves(bool* ctp, int* totMov, struct move legalMoves[256], struct piece wPieces[16], struct piece bPieces[16], char board[8][8], struct move* playedMoves);
struct move isMoveLegal(int* totMov, struct move inputMove, struct move legalMoves[256]);

#endif
