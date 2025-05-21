#ifndef MOVE_FUNCTIONS_AT_MAT_H_INCLUDED
#define MOVE_FUNCTIONS_AT_MAT_H_INCLUDED

#include "app-state.h"

bool movePawnsAtShah(AppState& appState, int FigureColor);
bool moveRooksAtShah(AppState& appState, int FigureColor);
bool moveBishopsAtShah(AppState& appState, int FigureColor);
bool moveQueenAtShah(AppState& appState, int FigureColor);
bool moveKnightsAtShah(AppState& appState, int FigureColor);
bool moveKingAtShah(AppState& appState, int FigureColor);

#endif // MOVE_FUNCTIONS_AT_MAT_H_INCLUDED
