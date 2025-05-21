#ifndef BACKLIGHT_FUNCTIONS_H_INCLUDED
#define BACKLIGHT_FUNCTIONS_H_INCLUDED

#include "app-state.h"

void DrawBacklight(AppState& appState, int x, int y);
void SelectedFigureBacklight(AppState& appState, int x, int y);
void BacklightOfPossibleMovements(AppState& appState, int ox, int oy);
void BacklightOfPossiblePawnMovements(AppState& appState, int OpponentColor, int ox, int oy);
void BacklightOfPossibleRookMovements(AppState& appState, int OpponentColor, int ox, int oy);
void BacklightOfPossibleBishopMovements(AppState& appState, int OpponentColor, int ox, int oy);
void BacklightOfPossibleQueenMovements(AppState& appState, int OpponentColor, int ox, int oy);
void BacklightOfPossibleKnightMovements(AppState& appState, int OpponentColor, int ox, int oy);
void BacklightOfPossibleKingMovements(AppState& appState, int OpponentColor, int ox, int oy);
void BacklightOfKingUnderShah(AppState& appState, int ox, int oy);

#endif // BACKLIGHT_FUNCTIONS_H_INCLUDED
