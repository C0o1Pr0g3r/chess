#ifndef CHECKS_H_INCLUDED
#define CHECKS_H_INCLUDED

bool CheckingKingOnShah(int KingColor);
bool IsAllowedMF(int ox, int oy, int nx, int ny);
bool DKORM(int kingx, int kingy, int rookx, int rooky);
bool IsCastlingNow(int ox, int oy, int nx, int ny);
bool IsKingCrossingSafeField(int sx, int ix, int y);
bool CheckingKingOnMat(int FigureColor);
bool CheckingKingOnPat(int FigureColor);
bool HasPawnReachedLastHorizontal(int x, int y);
bool IsTherePawnToActivateTakingOnAisle(int x, int y);
int IsGameOver(void);
void EventChecking(void);

#endif // CHECKS_H_INCLUDED
