#ifndef VERIFYLEGALITY_H
#define VERIFYLEGALITY_H

void verifylegality(struct move strictlylegalMoves[256], int* stotMov, bool* ctp, struct move playedMove, struct piece wPieces[16], struct piece bPieces[16], char board[8][8]);
#endif
