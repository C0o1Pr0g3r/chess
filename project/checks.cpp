#include <stdio.h>
#include "global constants.h"
#include "external declaration of global variables.h"
#include "move functions.h"
#include "secondary functions.h"
#include "checks.h"
#include "move functions at mat.h"
#include "coordinate processing functions.h"

bool CheckingKingOnShah(int KingColor)
{
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

    if (FIGURE(board[kingy + pawnstepy][kingx - 1]) == OpponentPawn || FIGURE(board[kingy + pawnstepy][kingx + 1]) == OpponentPawn)
        IsShah = true;

    for (j = kingy - 1; j > TOP_EXTREME_COORDINATE - 1; j--)
        if (board[j][kingx] > 0)
            break;
    if (FIGURE(board[j][kingx]) == OpponentRook || FIGURE(board[j][kingx]) == OpponentQueen)
        IsShah = true;
    for (j = kingy + 1; j < BOTTOM_EXTREME_COORDINATE  + 1; j++)
        if (board[j][kingx] > 0)
            break;
    if (FIGURE(board[j][kingx]) == OpponentRook || FIGURE(board[j][kingx]) == OpponentQueen)
        IsShah = true;
    for (i = kingx - 1; i > LEFT_EXTREME_COORDINATE  - 1; i--)
        if (board[kingy][i] > 0)
            break;
    if (FIGURE(board[kingy][i]) == OpponentRook || FIGURE(board[kingy][i]) == OpponentQueen)
        IsShah = true;
    for (i = kingx + 1; i < RIGHT_EXTREME_COORDINATE + 1; i++)
        if (board[kingy][i] > 0)
            break;
    if (FIGURE(board[kingy][i]) == OpponentRook || FIGURE(board[kingy][i]) == OpponentQueen)
        IsShah = true;

    for (i = kingx - 1, j = kingy - 1; i > LEFT_EXTREME_COORDINATE  - 1 && j > TOP_EXTREME_COORDINATE - 1; i--, j--)
        if (board[j][i] > 0)
            break;
    if (FIGURE(board[j][i]) == OpponentBishop || FIGURE(board[j][i]) == OpponentQueen)
        IsShah = true;
    for (i = kingx + 1, j = kingy + 1; i < RIGHT_EXTREME_COORDINATE + 1 && j < BOTTOM_EXTREME_COORDINATE + 1; i++, j++)
        if (board[j][i] > 0)
            break;
    if (FIGURE(board[j][i]) == OpponentBishop || FIGURE(board[j][i]) == OpponentQueen)
        IsShah = true;
    for (i = kingx + 1, j = kingy - 1; i < RIGHT_EXTREME_COORDINATE + 1 && j > TOP_EXTREME_COORDINATE - 1; i++, j--)
        if (board[j][i] > 0)
            break;
    if (FIGURE(board[j][i]) == OpponentBishop || FIGURE(board[j][i]) == OpponentQueen)
        IsShah = true;
    for (i = kingx - 1, j = kingy + 1; i > LEFT_EXTREME_COORDINATE  - 1 && j < BOTTOM_EXTREME_COORDINATE + 1; i--, j++)
        if (board[j][i] > 0)
            break;
    if (FIGURE(board[j][i]) == OpponentBishop || FIGURE(board[j][i]) == OpponentQueen)
        IsShah = true;

    if (FIGURE(board[kingy - 2][kingx - 1]) == OpponentKnight || FIGURE(board[kingy - 2][kingx + 1]) == OpponentKnight)
        IsShah = true;
    if (FIGURE(board[kingy - 1][kingx - 2]) == OpponentKnight || FIGURE(board[kingy - 1][kingx + 2]) == OpponentKnight)
        IsShah = true;
    if (FIGURE(board[kingy + 1][kingx - 2]) == OpponentKnight || FIGURE(board[kingy + 1][kingx + 2]) == OpponentKnight)
        IsShah = true;
    if (FIGURE(board[kingy + 2][kingx - 1]) == OpponentKnight || FIGURE(board[kingy + 2][kingx + 1]) == OpponentKnight)
        IsShah = true;

    for (j = - 1; j < 2; j++)
        for (i = -1; i < 2; i++)
            if (j != 0 || i != 0)
                if (FIGURE(board[kingy + j][kingx + i]) == OpponentKing)
                    IsShah = true;

    return IsShah;
}

bool IsAllowedMF(int ox, int oy, int nx, int ny)   //Is Allowed Movement Of Figure
{
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
        case PAWN: status = movePawn(ox, oy, nx, ny); break;
        case ROOK: status = moveRook(ox, oy, nx, ny); break;
        case BISHOP: status = moveBishop(ox, oy, nx, ny); break;
        case KNIGHT: status = moveKnight(ox, oy, nx, ny); break;
        case QUEEN: status = moveQueen(ox, oy, nx, ny); break;
        case KING: status = moveKing(ox, oy, nx, ny); break;
    }

    if (!CheckingKingOnShah(FigureColor))
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

bool DKORM(int kingx, int kingy, int rookx, int rooky)   //Did King Or Rook Move
{
    bool status = false;

    if (IS_MOVE(board[kingy][kingx]) || IS_MOVE(board[rooky][rookx]))
        status = true;
    return status;
}

bool IsCastlingNow(int ox, int oy, int nx, int ny)
{
    bool status = false;

    if (FIGURE_TYPE(FigureByOldCoordinates) == KING && (nx == ox - 2 || nx == ox + 2) && ny == oy)
        status = true;

    return status;
}

bool IsKingCrossingSafeField(int sx, int ix, int y)
{
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

    status = !CheckingKingOnShah(KingColor);

    *KPx = KSPx;

    return status;
}

bool CheckingKingOnMat(int FigureColor)
{
    bool IsMat = true;

    if (!movePawnsAtShah(FigureColor) || !moveRooksAtShah(FigureColor) || !moveBishopsAtShah(FigureColor) || !moveQueenAtShah(FigureColor) || !moveKnightsAtShah(FigureColor) || !moveKingAtShah(FigureColor))
        IsMat = false;

    return IsMat;
}

bool CheckingKingOnPat(int FigureColor)
{
    bool IsPat = true;

    if (!movePawnsAtShah(FigureColor) || !moveRooksAtShah(FigureColor) || !moveBishopsAtShah(FigureColor) || !moveQueenAtShah(FigureColor) || !moveKnightsAtShah(FigureColor) || !moveKingAtShah(FigureColor))
        IsPat = false;

    return IsPat;
}

bool HasPawnReachedLastHorizontal(int x, int y)   //Has Pawn Reached Last Horizontal
{
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

bool IsTherePawnToActivateTakingOnAisle(int x, int y)
{
    bool status = false;
    int PawnColor = DetermineFigureColor(x, y);
    int OpponentColor = PawnColor == BLACK ? WHITE : BLACK;
    int OpponentPawn = OpponentColor | PAWN;

    if (FIGURE(board[y][x - 1]) == OpponentPawn || FIGURE(board[y][x + 1]) == OpponentPawn)
        status = true;

    return status;
}

int IsGameOver(void)
{
    int status = 0;

    if (CheckingKingOnShah(BLACK) || CheckingKingOnShah(WHITE))
    {
        if (CheckingKingOnMat(WHITE))
            status = 1;

        if (CheckingKingOnMat(BLACK))
            status = 2;
    }
    else
    {
        if ((CheckingKingOnPat(BLACK)) && WhoseMove || (CheckingKingOnPat(WHITE) && !WhoseMove))
            status = 3;
    }

    return status;
}

void EventChecking(void)
{
    MC = Mouse::getPosition(window);

    LeftMouseButtonIsPressed = RightMouseButtonIsPressed = EscapeIsPressed = false;

    while (window.pollEvent(event))
    {
        switch(event.type)
        {
            case Event::Closed:
                WriteDataToFile();
                window.close();
                break;
            case Event::Resized:
                ChangeWSC();
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
