#ifndef MOVE_FUNCTIONS_H_INCLUDED
#define MOVE_FUNCTIONS_H_INCLUDED

#include "app-state.h"

bool FigureMovementPvP(AppState& appState, int ox, int oy, int nx, int ny);
bool FigureMovementPvEPlayer(AppState& appState, int ox, int oy, int nx, int ny);
bool FigureMovementPvEEnvironment(AppState& appState, int ox, int oy, int nx, int ny);

bool moveFigure(AppState& appState, int ox, int oy, int nx, int ny);
bool movePawn(AppState& appState, int ox, int oy, int nx, int ny);
bool moveRook(AppState& appState, int ox, int oy, int nx, int ny);
bool moveBishop(AppState& appState, int ox, int oy, int nx, int ny);
bool moveKnight(AppState& appState, int ox, int oy, int nx, int ny);
bool moveQueen(AppState& appState, int ox, int oy, int nx, int ny);
bool moveKing(AppState& appState, int ox, int oy, int nx, int ny);
void DoCastling(AppState& appState, int okingx, int nkingx, int orookx, int nrookx, int kry);

#endif // MOVE_FUNCTIONS_H_INCLUDED
