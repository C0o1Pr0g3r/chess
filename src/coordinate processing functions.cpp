#include <SFML/Graphics.hpp>
#include "global constants.h"
#include "checks.h"
#include "secondary functions.h"
#include "app-state.h"

using namespace sf;

void RecodeMouseCoordinatesToChecssboardCoordinates(AppState& appState)
{
    auto& CC = appState.CC;
    auto& MC = appState.MC;

    CC.x = MC.x / CFDCP;
    CC.y = MC.y / CFDCP;
}

Vector2i GetMouseCoordinates(RenderWindow& window)
{
    return Vector2i(window.mapPixelToCoords(Mouse::getPosition(window)));
}
