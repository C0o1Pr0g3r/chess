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
    auto& CFRCPC = appState.CFRCPC;

    CC.x = MC.x / CFRCPC.x;
    CC.y = MC.y / CFRCPC.y;
}

void ChangeWSC(AppState& appState)
{
    auto& NWS = appState.NWS;
    auto& window = appState.window;
    auto& WSC = appState.WSC;
    auto& InitialWindowSize = appState.InitialWindowSize;
    auto& CFRCPC = appState.CFRCPC;
    auto& OWS = appState.OWS;

    NWS = window.getSize();
    Vector2f newCFRCPC;
    /*printf("Старые размеры окна: %dx%d\n", OWS.x, OWS.y);
    printf("Новые размеры окна: %dx%d\n", NWS.x, NWS.y);
    printf("До\n");
    printf("WSC.x =    %f     WSC.x =    %f\n", WSC.x, WSC.y);
    printf("CFRCPC.x = %d     CFRCPC.x = %d\n", CFRCPC.x, CFRCPC.y);*/

    WSC = {(float) NWS.x / (float) InitialWindowSize.x, (float) NWS.y / (float) InitialWindowSize.y};
    newCFRCPC.x = (float) CFDCP * WSC.x;
    newCFRCPC.y = (float) CFDCP * WSC.y;
    //printf("newCFRCPC.x = %f     newCFRCPC.x = %f\n", newCFRCPC.x, newCFRCPC.y);
    CFRCPC.x = newCFRCPC.x - (int) newCFRCPC.x < 0.5 ? (int) newCFRCPC.x : (int) newCFRCPC.x + 1;
    CFRCPC.y = newCFRCPC.y - (int) newCFRCPC.y < 0.5 ? (int) newCFRCPC.y : (int) newCFRCPC.y + 1;
    ChangeButtonPropertiesByCoefficient(appState, WSC);
    OWS = NWS;
    /*printf("После\n");
    printf("WSC.x =    %f     WSC.x =    %f\n", WSC.x, WSC.y);
    printf("CFRCPC.x = %d     CFRCPC.x = %d\n", CFRCPC.x, CFRCPC.y);*/
}
