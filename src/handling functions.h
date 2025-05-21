#ifndef MAIN_FUNCTIONS_H_INCLUDED
#define MAIN_FUNCTIONS_H_INCLUDED

#include "app-state.h"

void HandleApp(AppState& appState);
void HandleMainMenuScreen(AppState& appState);
void HandleChessGameScreen(AppState& appState);
void HandleClickOnChessboard(AppState& appState);

void HandlePawnTransformationWindow(AppState& appState);
void HandleGameOverWindow(AppState& appState);
void HandleGameOnPauseWindow(AppState& appState);
void HandleOptionsWindow(AppState& appState);
void HandleGameSaveWindow(AppState& appState);

#endif // MAIN_FUNCTIONS_H_INCLUDED
