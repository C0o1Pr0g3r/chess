#ifndef DRAWING_FUNCTIONS_H_INCLUDED
#define DRAWING_FUNCTIONS_H_INCLUDED

#include "app-state.h"

void DrawApp(AppState& appState);
void DrawMainMenuScreen(AppState& appState);
void DrawChessGameScreen(AppState& appState);
void DrawStaticChessGameObjects(AppState& appState);
inline void DrawWhoseMoveInscription(AppState& appState);
inline void DrawChessboard(AppState& appState);
inline void DrawPawnTransformation(AppState& appState);
inline void DrawGameOverWindow(AppState& appState);
inline void DrawGameOnPauseWindow(AppState& appState);
inline void DrawOptionsWindow(AppState& appState);
inline void DrawGameSaveWindow(AppState& appState);
void DrawFigures(AppState& appState);
void DrawSmallFigures(AppState& appState);

#endif // DRAWING_FUNCTIONS_H_INCLUDED
