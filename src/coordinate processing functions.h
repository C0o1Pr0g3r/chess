#ifndef COORDINATE_PROCESSING_FUNCTIONS_H_INCLUDED
#define COORDINATE_PROCESSING_FUNCTIONS_H_INCLUDED

#include "app-state.h"

void RecodeMouseCoordinatesToChecssboardCoordinates(AppState& appState);
Vector2i GetMouseCoordinates(RenderWindow& window);

#endif // COORDINATE_PROCESSING_FUNCTIONS_H_INCLUDED
