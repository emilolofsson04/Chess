#ifndef KINGSAFETY_H
#define KINGSAFETY_H
bool walkThreat(char board[8][8], int rank, int file, int pcolour, int step, int rdir, int fdir);
bool knightThreat(char board[8][8], int rank, int file, int pcolour, int rdir, int fdir);
bool isKingSafe(char board[8][8], int rank, int file, int pcolour);
bool pawnThreat(char board[8][8], int rank, int file, int pcolour, int rdir, int fdir);

#endif
