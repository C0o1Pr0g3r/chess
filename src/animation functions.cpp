#include <SFML/Graphics.hpp>
// #include <windows.h>
#include "global constants.h"
#include "checks.h"
#include "secondary functions.h"
#include "drawing functions.h"
#include "animation functions.h"
#include "app-state.h"

void FigureMovementAnimation(AppState& appState, int ox, int oy, int nx, int ny)
{
    auto& FigureByOldCoordinates = appState.FigureByOldCoordinates;
    auto& pAS = appState.pAS;
    auto& FigureByNewCoordinates = appState.FigureByNewCoordinates;
    auto& board = appState.board;
    auto& AnimatedRookStartingPosition = appState.AnimatedRookStartingPosition;
    auto& AnimatedRookFinalPosition = appState.AnimatedRookFinalPosition;
    auto& AnimatedRook = appState.AnimatedRook;
    auto& pRAS = appState.pRAS;
    auto& window = appState.window;

    Vector2f FigureStartingPosition, FigureFinalPosition, FigureCurrentPosition, FigureDistance, FigureStep,
    RookStartingPosition, RookFinalPosition, RookCurrentPosition, RookDistance, RookStep;
    int rox, rnx, ry;
    bool IsCastling;
    Clock clock;
    int elapsedTime, remainingTime;
    float timeCoefficient;
    const int animationTime = 300000;

    remainingTime = animationTime;
    IsCastling = IsCastlingNow(appState, ox, oy, nx, ny);

    FigureStartingPosition = {static_cast<float>(ox * CFDCP), static_cast<float>(oy * CFDCP)};
    FigureFinalPosition = {static_cast<float>(nx * CFDCP), static_cast<float>(ny * CFDCP)};
    FigureCurrentPosition = FigureStartingPosition;
    FigureDistance = FigureFinalPosition - FigureStartingPosition;
    DetermineAnimatedSprite(appState, FigureByOldCoordinates, &pAS);
    board[ny][nx] = FigureByNewCoordinates;

    if (IsCastling)
    {
        RookStartingPosition = {static_cast<float>(AnimatedRookStartingPosition.x * CFDCP), static_cast<float>(AnimatedRookStartingPosition.y * CFDCP)};
        RookFinalPosition = {static_cast<float>(AnimatedRookFinalPosition.x * CFDCP), static_cast<float>(AnimatedRookFinalPosition.y * CFDCP)};
        RookCurrentPosition = RookStartingPosition;
        RookDistance = RookFinalPosition - RookStartingPosition;
        rox = AnimatedRookStartingPosition.x;
        rnx = AnimatedRookFinalPosition.x;
        ry = oy;
        DetermineAnimatedSprite(appState, AnimatedRook, &pRAS);
        board[ry][rnx] = 0;
    }

    while (remainingTime > 0)
    {
        elapsedTime = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        timeCoefficient = (float) elapsedTime / animationTime;
        FigureStep = FigureDistance * timeCoefficient;
        remainingTime -= elapsedTime;
        window.clear();
        DrawStaticChessGameObjects(appState);
        DrawFigures(appState);
        DrawAnimatedSprite(appState, FigureCurrentPosition, pAS);
        FigureCurrentPosition.x += FigureStep.x;
        FigureCurrentPosition.y += FigureStep.y;

        if (IsCastling)
        {
            RookStep = RookDistance * timeCoefficient;;
            DrawAnimatedSprite(appState, RookCurrentPosition, pRAS);
            RookCurrentPosition.x += RookStep.x;
            RookCurrentPosition.y += RookStep.y;
        }
        window.display();
    }

    switch(FIGURE_TYPE(FigureByOldCoordinates))
    {
        case PAWN : board[ny][nx] = FigureByOldCoordinates | MOVE; break;
        case ROOK : board[ny][nx] = FigureByOldCoordinates | MOVE; break;
        case KING : board[ny][nx] = FigureByOldCoordinates | MOVE; break;
        default : board[ny][nx] = FigureByOldCoordinates; break;
    }

    if (IsCastling)
        board[ry][rnx] = AnimatedRook | MOVE;
}

void DrawAnimatedSprite(AppState& appState, Vector2f coord, DrawnObject * ps)
{
    auto& window = appState.window;

    ps->SetPosition(coord);
    ps->Draw(window);
}
