#include <stdio.h>
#include "global constants.h"
#include "move functions.h"
#include "secondary functions.h"
#include "checks.h"
#include "move functions at mat.h"
#include "coordinate processing functions.h"
#include "app-state.h"

bool CheckingKingOnShah(AppState& appState, int KingColor)
{
    auto& blackKing = appState.blackKing;
    auto& whiteKing = appState.whiteKing;
    auto& ChessboardIsInverted = appState.ChessboardIsInverted;
    auto& board = appState.board;

    bool IsShah = false;
    int i, j;
    int kingx, kingy;
    int OpponentPawn, OpponentRook, OpponentBishop, OpponentKnight, OpponentQueen, OpponentKing;
    int pawnstepy;

    if (KingColor == BLACK)
    {
        kingx = blackKing.x;
        kingy = blackKing.y;
        OpponentPawn = WHITE_PAWN;
        OpponentRook = WHITE_ROOK;
        OpponentBishop = WHITE_BISHOP;
        OpponentKnight = WHITE_KNIGHT;
        OpponentQueen = WHITE_QUEEN;
        OpponentKing = WHITE_KING;
        pawnstepy = 1;
    }
    else
    {
        kingx = whiteKing.x;
        kingy = whiteKing.y;
        OpponentPawn = BLACK_PAWN;
        OpponentRook = BLACK_ROOK;
        OpponentBishop = BLACK_BISHOP;
        OpponentKnight = BLACK_KNIGHT;
        OpponentQueen = BLACK_QUEEN;
        OpponentKing = BLACK_KING;
        pawnstepy = -1;
    }

    if (ChessboardIsInverted)
        pawnstepy = -pawnstepy;

    if (AreCoordsInsideBoard(BOARD_SIZE, kingy + pawnstepy, kingx - 1)
        && FIGURE(board[kingy + pawnstepy][kingx - 1]) == OpponentPawn
        ||
        AreCoordsInsideBoard(BOARD_SIZE, kingy + pawnstepy, kingx + 1)
        && FIGURE(board[kingy + pawnstepy][kingx + 1]) == OpponentPawn)
        IsShah = true;

    for (j = kingy - 1; j > TOP_EXTREME_COORDINATE - 1; j--)
        if (board[j][kingx] > 0)
            break;
    if (AreCoordsInsideBoard(BOARD_SIZE, j, kingx)
        &&
        (FIGURE(board[j][kingx]) == OpponentRook
        ||
        FIGURE(board[j][kingx]) == OpponentQueen))
        IsShah = true;
    for (j = kingy + 1; j < BOTTOM_EXTREME_COORDINATE  + 1; j++)
        if (board[j][kingx] > 0)
            break;
    if (AreCoordsInsideBoard(BOARD_SIZE, j, kingx)
        &&
        (FIGURE(board[j][kingx]) == OpponentRook
        ||
        FIGURE(board[j][kingx]) == OpponentQueen))
        IsShah = true;
    for (i = kingx - 1; i > LEFT_EXTREME_COORDINATE  - 1; i--)
        if (board[kingy][i] > 0)
            break;
    if (AreCoordsInsideBoard(BOARD_SIZE, kingy, i)
        &&
        (FIGURE(board[kingy][i]) == OpponentRook
        ||
        FIGURE(board[kingy][i]) == OpponentQueen))
        IsShah = true;
    for (i = kingx + 1; i < RIGHT_EXTREME_COORDINATE + 1; i++)
        if (board[kingy][i] > 0)
            break;
    if (AreCoordsInsideBoard(BOARD_SIZE, kingy, i)
        &&
        (FIGURE(board[kingy][i]) == OpponentRook
        ||
        FIGURE(board[kingy][i]) == OpponentQueen))
        IsShah = true;

    for (i = kingx - 1, j = kingy - 1; i > LEFT_EXTREME_COORDINATE  - 1 && j > TOP_EXTREME_COORDINATE - 1; i--, j--)
        if (board[j][i] > 0)
            break;
    if (AreCoordsInsideBoard(BOARD_SIZE, j, i)
        &&
        (FIGURE(board[j][i]) == OpponentBishop
        ||
        FIGURE(board[j][i]) == OpponentQueen))
        IsShah = true;
    for (i = kingx + 1, j = kingy + 1; i < RIGHT_EXTREME_COORDINATE + 1 && j < BOTTOM_EXTREME_COORDINATE + 1; i++, j++)
        if (board[j][i] > 0)
            break;
    if (AreCoordsInsideBoard(BOARD_SIZE, j, i)
        &&
        (FIGURE(board[j][i]) == OpponentBishop
        ||
        FIGURE(board[j][i]) == OpponentQueen))
        IsShah = true;
    for (i = kingx + 1, j = kingy - 1; i < RIGHT_EXTREME_COORDINATE + 1 && j > TOP_EXTREME_COORDINATE - 1; i++, j--)
        if (board[j][i] > 0)
            break;
    if (AreCoordsInsideBoard(BOARD_SIZE, j, i)
        &&
        (FIGURE(board[j][i]) == OpponentBishop
        ||
        FIGURE(board[j][i]) == OpponentQueen))
        IsShah = true;
    for (i = kingx - 1, j = kingy + 1; i > LEFT_EXTREME_COORDINATE  - 1 && j < BOTTOM_EXTREME_COORDINATE + 1; i--, j++)
        if (board[j][i] > 0)
            break;
    if (AreCoordsInsideBoard(BOARD_SIZE, j, i)
        &&
        (FIGURE(board[j][i]) == OpponentBishop
        ||
        FIGURE(board[j][i]) == OpponentQueen))
        IsShah = true;

    if (
        AreCoordsInsideBoard(BOARD_SIZE, kingy - 2, kingx - 1) && FIGURE(board[kingy - 2][kingx - 1]) == OpponentKnight
        ||
        AreCoordsInsideBoard(BOARD_SIZE, kingy - 2, kingx + 1) && FIGURE(board[kingy - 2][kingx + 1]) == OpponentKnight)
        IsShah = true;
    if (
        AreCoordsInsideBoard(BOARD_SIZE, kingy - 1, kingx - 2) && FIGURE(board[kingy - 1][kingx - 2]) == OpponentKnight
        ||
        AreCoordsInsideBoard(BOARD_SIZE, kingy - 1, kingx + 2) && FIGURE(board[kingy - 1][kingx + 2]) == OpponentKnight)
        IsShah = true;
    if (
        AreCoordsInsideBoard(BOARD_SIZE, kingy + 1, kingx - 2) && FIGURE(board[kingy + 1][kingx - 2]) == OpponentKnight
        ||
        AreCoordsInsideBoard(BOARD_SIZE, kingy + 1, kingx + 2) && FIGURE(board[kingy + 1][kingx + 2]) == OpponentKnight)
        IsShah = true;
    if (
        AreCoordsInsideBoard(BOARD_SIZE, kingy + 2, kingx - 1) && FIGURE(board[kingy + 2][kingx - 1]) == OpponentKnight
        ||
        AreCoordsInsideBoard(BOARD_SIZE, kingy + 2, kingx + 1) && FIGURE(board[kingy + 2][kingx + 1]) == OpponentKnight)
        IsShah = true;

    for (j = - 1; j < 2; j++)
        for (i = -1; i < 2; i++)
            if (j != 0 || i != 0)
                if (AreCoordsInsideBoard(BOARD_SIZE, kingy + j, kingx + i) && FIGURE(board[kingy + j][kingx + i]) == OpponentKing)
                    IsShah = true;

    return IsShah;
}

bool IsAllowedMF(AppState& appState, int ox, int oy, int nx, int ny)   //Is Allowed Movement Of Figure
{
    auto& board = appState.board;
    auto& blackKing = appState.blackKing;
    auto& whiteKing = appState.whiteKing;

    bool MovementApproved = false;
    bool status = false;
    bool IsCastling = false;
    int tmpo, tmpn;
    int FigureColor, OpponentColor;
    int * pKPx, * pKPy;

    switch (FIGURE_COLOR(board[oy][ox]))
    {
        case BLACK:
            FigureColor = BLACK;
            pKPx = &blackKing.x;
            pKPy = &blackKing.y;
            break;
        case WHITE:
            FigureColor = WHITE;
            pKPx = &whiteKing.x;
            pKPy = &whiteKing.y;
            break;
    }

    if (FIGURE_TYPE(board[oy][ox]) == KING && (nx == ox - 2 || nx == ox + 2))
        IsCastling = true;

    tmpo = board[oy][ox];
    tmpn = board[ny][nx];

    switch (FIGURE_TYPE(board[oy][ox]))
    {
        case PAWN: status = movePawn(appState, ox, oy, nx, ny); break;
        case ROOK: status = moveRook(appState, ox, oy, nx, ny); break;
        case BISHOP: status = moveBishop(appState, ox, oy, nx, ny); break;
        case KNIGHT: status = moveKnight(appState, ox, oy, nx, ny); break;
        case QUEEN: status = moveQueen(appState, ox, oy, nx, ny); break;
        case KING: status = moveKing(appState, ox, oy, nx, ny); break;
    }

    if (!CheckingKingOnShah(appState, FigureColor))
        MovementApproved = true;

    if (IsCastling)
    {
        if (FIGURE_TYPE(board[oy][ox - 2]) == KING && FIGURE_TYPE(board[oy][ox - 1]) == ROOK)
        {
            board[oy][1] = (FigureColor | ROOK);
            board[oy][ox - 2] = board[oy][ox - 1] = 0;
        }

        else if (FIGURE_TYPE(board[oy][ox + 2]) == KING && FIGURE_TYPE(board[oy][ox + 1]) == ROOK)
        {
            board[oy][8] = (FigureColor | ROOK);
            board[oy][ox + 2] = board[oy][ox + 1] = 0;
        }
    }

    board[oy][ox] = tmpo;
    board[ny][nx] = tmpn;

    if (FIGURE_TYPE(board[oy][ox]) == KING)
    {
        *pKPx = ox;
        *pKPy = oy;
    }

    return MovementApproved;
}

bool DKORM(AppState& appState, int kingx, int kingy, int rookx, int rooky)   //Did King Or Rook Move
{
    auto& board = appState.board;

    bool status = false;

    if (IS_MOVE(board[kingy][kingx]) || IS_MOVE(board[rooky][rookx]))
        status = true;
    return status;
}

bool IsCastlingNow(AppState& appState, int ox, int oy, int nx, int ny)
{
    auto& FigureByOldCoordinates = appState.FigureByOldCoordinates;

    bool status = false;

    if (FIGURE_TYPE(FigureByOldCoordinates) == KING && (nx == ox - 2 || nx == ox + 2) && ny == oy)
        status = true;

    return status;
}

bool IsKingCrossingSafeField(AppState& appState, int sx, int ix, int y)
{
    auto& board = appState.board;
    auto& blackKing = appState.blackKing;
    auto& whiteKing = appState.whiteKing;

    bool status;
    int KingColor;
    int * KPx, KSPx;

    switch(FIGURE_COLOR(board[y][sx]))
    {
        case BLACK:
            KingColor = BLACK;
            KPx = &blackKing.x;
            break;
        case WHITE:
            KingColor = WHITE;
            KPx = &whiteKing.x;
            break;
    }

    KSPx = *KPx;

    *KPx = ix;

    status = !CheckingKingOnShah(appState, KingColor);

    *KPx = KSPx;

    return status;
}

bool CheckingKingOnMat(AppState& appState, int FigureColor)
{
    bool IsMat = true;

    if (!movePawnsAtShah(appState, FigureColor) || !moveRooksAtShah(appState, FigureColor) || !moveBishopsAtShah(appState, FigureColor) || !moveQueenAtShah(appState, FigureColor) || !moveKnightsAtShah(appState, FigureColor) || !moveKingAtShah(appState, FigureColor))
        IsMat = false;

    return IsMat;
}

bool CheckingKingOnPat(AppState& appState, int FigureColor)
{
    bool IsPat = true;

    if (!movePawnsAtShah(appState, FigureColor) || !moveRooksAtShah(appState, FigureColor) || !moveBishopsAtShah(appState, FigureColor) || !moveQueenAtShah(appState, FigureColor) || !moveKnightsAtShah(appState, FigureColor) || !moveKingAtShah(appState, FigureColor))
        IsPat = false;

    return IsPat;
}

bool HasPawnReachedLastHorizontal(AppState& appState, int x, int y)   //Has Pawn Reached Last Horizontal
{
    auto& board = appState.board;
    auto& ChessboardIsInverted = appState.ChessboardIsInverted;

    bool HasPawnReached = false;
    int RHC;   //Required Horizontal Coordinate

    switch(FIGURE_COLOR(board[y][x]))
    {
        case BLACK : RHC = ChessboardIsInverted ? TOP_EXTREME_COORDINATE : BOTTOM_EXTREME_COORDINATE; break;
        case WHITE : RHC = ChessboardIsInverted ? BOTTOM_EXTREME_COORDINATE : TOP_EXTREME_COORDINATE; break;
    }

    if (y == RHC)
        HasPawnReached = true;

    return HasPawnReached;
}

bool IsTherePawnToActivateTakingOnAisle(AppState& appState, int x, int y)
{
    auto& board = appState.board;

    bool status = false;
    int PawnColor = DetermineFigureColor(appState, x, y);
    int OpponentColor = PawnColor == BLACK ? WHITE : BLACK;
    int OpponentPawn = OpponentColor | PAWN;

    if (FIGURE(board[y][x - 1]) == OpponentPawn || FIGURE(board[y][x + 1]) == OpponentPawn)
        status = true;

    return status;
}

int IsGameOver(AppState& appState)
{
    auto& WhoseMove = appState.WhoseMove;

    int status = 0;

    if (CheckingKingOnShah(appState, BLACK) || CheckingKingOnShah(appState, WHITE))
    {
        if (CheckingKingOnMat(appState, WHITE))
            status = 1;

        if (CheckingKingOnMat(appState, BLACK))
            status = 2;
    }
    else
    {
        if ((CheckingKingOnPat(appState, BLACK)) && WhoseMove || (CheckingKingOnPat(appState, WHITE) && !WhoseMove))
            status = 3;
    }

    return status;
}

void EventChecking(AppState& appState)
{
    auto& MC = appState.MC;
    auto& window = appState.window;
    auto& LeftMouseButtonIsPressed = appState.LeftMouseButtonIsPressed;
    auto& RightMouseButtonIsPressed = appState.RightMouseButtonIsPressed;
    auto& EscapeIsPressed = appState.EscapeIsPressed;
    auto& event = appState.event;

    MC = Mouse::getPosition(window);

    LeftMouseButtonIsPressed = RightMouseButtonIsPressed = EscapeIsPressed = false;

    while (window.pollEvent(event))
    {
        switch(event.type)
        {
            case Event::Closed:
                WriteDataToFile(appState);
                window.close();
                break;
            case Event::Resized:
                ChangeWSC(appState);
                break;
            case Event::MouseButtonPressed:
                switch(event.key.code)
                {
                    case Mouse::Left : LeftMouseButtonIsPressed = true; break;
                    case Mouse::Right : RightMouseButtonIsPressed = true; break;
                }
                break;
            case Event::KeyPressed:
                switch(event.key.code)
                {
                    case Keyboard::Escape: EscapeIsPressed = true; break;
                }
                break;
        }
    }
}
