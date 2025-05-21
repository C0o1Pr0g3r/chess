#ifndef ANIMATION_FUNCTIONS_H_INCLUDED
#define ANIMATION_FUNCTIONS_H_INCLUDED

#include "app-state.h"

void FigureMovementAnimation(AppState& appState, int ox, int oy, int nx, int ny);
void DrawAnimatedSprite(AppState& appState, Vector2f coord, DrawnObject * ps);

#endif // ANIMATION_FUNCTIONS_H_INCLUDED
