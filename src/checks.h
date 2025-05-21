#ifndef CHECKS_H_INCLUDED
#define CHECKS_H_INCLUDED

#include "app-state.h"

bool CheckingKingOnShah(AppState& appState, int KingColor);
bool IsAllowedMF(AppState& appState, int ox, int oy, int nx, int ny);
bool DKORM(AppState& appState, int kingx, int kingy, int rookx, int rooky);
bool IsCastlingNow(AppState& appState, int ox, int oy, int nx, int ny);
bool IsKingCrossingSafeField(AppState& appState, int sx, int ix, int y);
bool CheckingKingOnMat(AppState& appState, int FigureColor);
bool CheckingKingOnPat(AppState& appState, int FigureColor);
bool HasPawnReachedLastHorizontal(AppState& appState, int x, int y);
bool IsTherePawnToActivateTakingOnAisle(AppState& appState, int x, int y);
int IsGameOver(AppState& appState);
void EventChecking(AppState& appState);

#endif // CHECKS_H_INCLUDED
