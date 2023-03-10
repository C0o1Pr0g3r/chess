#include "global constants.h"
#include "external declaration of global variables.h"
#include "checks.h"
#include "secondary functions.h"
#include "backlight functions.h"

void DrawBacklight(int x, int y)
{
    BacklightOfKingUnderShah(x, y);
    if (PieceIsChoose)
    {
        SelectedFigureBacklight(x, y);
        BacklightOfPossibleMovements(x, y);
    }
}

inline void SelectedFigureBacklight(int x, int y)
{
    if (PieceIsChoose)
    {
        GreenSquare_sprite.SetPosition(x * CFDCP, y * CFDCP);
        GreenSquare_sprite.Draw(window);
    }
}

void BacklightOfPossibleMovements(int ox, int oy)
{
    int FigureType = DetermineFigureType(ox, oy);
    int OpponentColor = DetermineFigureColor(ox, oy) == BLACK ? WHITE : BLACK;

    bool PieceIsChoose_copy = PieceIsChoose;
    bool WhoseMove_copy = WhoseMove;
    int FigureByOldCoordinates_copy = FigureByOldCoordinates, FigureByNewCoordinates_copy = FigureByNewCoordinates;
    int AnimatedRook_copy = AnimatedRook;
    Vector2i AnimatedRookStartingPosition_copy = AnimatedRookStartingPosition, AnimatedRookFinalPosition_copy = AnimatedRookFinalPosition;
    bool IsTakingOnAisleActivated_copy = IsTakingOnAisleActivated;
    Vector2i PawnOnAisleCoordinates_copy = PawnOnAisleCoordinates;
    bool WhoHasMoved_copy = WhoHasMoved, IsTakingOnAisleUsed_copy = IsTakingOnAisleUsed;

    switch(FigureType)
    {
        case PAWN : BacklightOfPossiblePawnMovements(OpponentColor, ox, oy); break;
        case ROOK : BacklightOfPossibleRookMovements(OpponentColor, ox, oy); break;
        case BISHOP : BacklightOfPossibleBishopMovements(OpponentColor, ox, oy); break;
        case QUEEN : BacklightOfPossibleQueenMovements(OpponentColor, ox, oy); break;
        case KNIGHT : BacklightOfPossibleKnightMovements(OpponentColor, ox, oy); break;
        case KING : BacklightOfPossibleKingMovements(OpponentColor, ox, oy); break;
    }

    PieceIsChoose = PieceIsChoose_copy;
    WhoseMove = WhoseMove_copy;
    FigureByOldCoordinates = FigureByOldCoordinates_copy, FigureByNewCoordinates = FigureByNewCoordinates_copy;
    AnimatedRook = AnimatedRook_copy;
    AnimatedRookStartingPosition = AnimatedRookStartingPosition_copy, AnimatedRookFinalPosition = AnimatedRookFinalPosition_copy;
    IsTakingOnAisleActivated = IsTakingOnAisleActivated_copy;
    PawnOnAisleCoordinates = PawnOnAisleCoordinates_copy;
    WhoHasMoved = WhoHasMoved_copy, IsTakingOnAisleUsed = IsTakingOnAisleUsed_copy;
}

void BacklightOfPossiblePawnMovements(int OpponentColor, int ox, int oy)
{
    int Figure = DetermineFigure(ox, oy);
    int step1, step2;

    if (Figure == BLACK_PAWN)
    {
        step1 = 1;
        step2 = 2;
    }
    else if (Figure == WHITE_PAWN)
    {
        step1 = -1;
        step2 = -2;
    }

    if (ChessboardIsInverted)
    {
        step1 = -step1;
        step2 = -step2;
    }

    if (board[oy + step1][ox] == 0 && IsAllowedMF(ox, oy, ox, oy + step1))
    {
        DarkCircle_sprite.SetPosition(ox * CFDCP, (oy + step1) * CFDCP);
        DarkCircle_sprite.Draw(window);
    }
    if (board[oy + step2][ox] == 0 && board[oy + step1][ox] == 0 && !IS_MOVE(board[oy][ox]) && IsAllowedMF(ox, oy, ox, oy + step2))
    {
        DarkCircle_sprite.SetPosition(ox * CFDCP, (oy + step2) * CFDCP);
        DarkCircle_sprite.Draw(window);
    }
    if (board[oy + step1][ox - 1] > 0 && FIGURE_COLOR(board[oy + step1][ox - 1]) == OpponentColor && IsAllowedMF(ox, oy, ox - 1, oy + step1))
    {
        YellowSquare_sprite.SetPosition((ox - 1) * CFDCP, (oy + step1) * CFDCP);
        YellowSquare_sprite.Draw(window);
    }
    if (board[oy + step1][ox + 1] > 0 && FIGURE_COLOR(board[oy + step1][ox + 1]) == OpponentColor && IsAllowedMF(ox, oy, ox + 1, oy + step1))
    {
        YellowSquare_sprite.SetPosition((ox + 1) * CFDCP, (oy + step1) * CFDCP);
        YellowSquare_sprite.Draw(window);
    }
    if (oy == PawnOnAisleCoordinates.y && board[oy + step1][PawnOnAisleCoordinates.x] == 0 && IsTakingOnAisleActivated && IsAllowedMF(ox, oy, PawnOnAisleCoordinates.x, oy + step1))
    {
        DarkCircle_sprite.SetPosition(PawnOnAisleCoordinates.x * CFDCP, (oy + step1) * CFDCP);
        DarkCircle_sprite.Draw(window);
    }
}

void BacklightOfPossibleRookMovements(int OpponentColor, int ox, int oy)
{
    int i, j;

    for (i = oy - 1; i > TOP_EXTREME_COORDINATE - 1; i--)   //up
    {
        if (board[i][ox] > 0)
        {
            if (FIGURE_COLOR(board[i][ox]) == OpponentColor && IsAllowedMF(ox, oy, ox, i))
            {
                YellowSquare_sprite.SetPosition(ox * CFDCP, i * CFDCP);
                YellowSquare_sprite.Draw(window);
            }
            break;
        }
        if (IsAllowedMF(ox, oy, ox, i))
        {
            DarkCircle_sprite.SetPosition(ox * CFDCP, i * CFDCP);
            DarkCircle_sprite.Draw(window);
        }
    }
    for (i = oy + 1; i < BOTTOM_EXTREME_COORDINATE + 1; i++)   //down
    {
        if (board[i][ox] > 0)
        {
            if (FIGURE_COLOR(board[i][ox]) == OpponentColor && IsAllowedMF(ox, oy, ox, i))
            {
                YellowSquare_sprite.SetPosition(ox * CFDCP, i * CFDCP);
                YellowSquare_sprite.Draw(window);
            }
            break;
        }
        if (IsAllowedMF(ox, oy, ox, i))
        {
            DarkCircle_sprite.SetPosition(ox * CFDCP, i * CFDCP);
            DarkCircle_sprite.Draw(window);
        }
    }
    for (i = ox - 1; i > LEFT_EXTREME_COORDINATE - 1; i--)   //left
    {
        if (board[oy][i] > 0)
        {
            if (FIGURE_COLOR(board[oy][i]) == OpponentColor && IsAllowedMF(ox, oy, i, oy))
            {
                YellowSquare_sprite.SetPosition(i * CFDCP, oy * CFDCP);
                YellowSquare_sprite.Draw(window);
            }
            break;
        }
        if (IsAllowedMF(ox, oy, i, oy))
        {
            DarkCircle_sprite.SetPosition(i * CFDCP, oy * CFDCP);
            DarkCircle_sprite.Draw(window);
        }
    }
    for (i = ox + 1; i < RIGHT_EXTREME_COORDINATE + 1; i++)   //right
    {
        if (board[oy][i] > 0)
        {
            if (FIGURE_COLOR(board[oy][i]) == OpponentColor && IsAllowedMF(ox, oy, i, oy))
            {
                YellowSquare_sprite.SetPosition(i * CFDCP, oy * CFDCP);
                YellowSquare_sprite.Draw(window);
            }
            break;
        }
        if (IsAllowedMF(ox, oy, i, oy))
        {
            DarkCircle_sprite.SetPosition(i * CFDCP, oy * CFDCP);
            DarkCircle_sprite.Draw(window);
        }
    }
}

void BacklightOfPossibleBishopMovements(int OpponentColor, int ox, int oy)
{
    int i, j;

    for (i = ox + 1, j = oy - 1; i < RIGHT_EXTREME_COORDINATE + 1 && j > TOP_EXTREME_COORDINATE - 1; i++, j--)
    {
        if (board[j][i] > 0)
        {
            if (FIGURE_COLOR(board[j][i]) == OpponentColor && IsAllowedMF(ox, oy, i, j))
            {
                YellowSquare_sprite.SetPosition(i * CFDCP, j * CFDCP);
                YellowSquare_sprite.Draw(window);
            }
            break;
        }
        if (IsAllowedMF(ox, oy, i, j))
        {
            DarkCircle_sprite.SetPosition(i * CFDCP, j * CFDCP);
            DarkCircle_sprite.Draw(window);
        }
    }
    for (i = ox + 1, j = oy + 1; i < RIGHT_EXTREME_COORDINATE + 1 && j < BOTTOM_EXTREME_COORDINATE + 1; i++, j++)
        {
            if (board[j][i] > 0)
        {
            if (FIGURE_COLOR(board[j][i]) == OpponentColor && IsAllowedMF(ox, oy, i, j))
            {
                YellowSquare_sprite.SetPosition(i * CFDCP, j * CFDCP);
                YellowSquare_sprite.Draw(window);
            }
            break;
        }
        if (IsAllowedMF(ox, oy, i, j))
        {
            DarkCircle_sprite.SetPosition(i * CFDCP, j * CFDCP);
            DarkCircle_sprite.Draw(window);
        }
    }
    for (i = ox - 1, j = oy + 1; i > LEFT_EXTREME_COORDINATE - 1 && j < BOTTOM_EXTREME_COORDINATE + 1; i--, j++)
    {
        if (board[j][i] > 0)
        {
            if (FIGURE_COLOR(board[j][i]) == OpponentColor && IsAllowedMF(ox, oy, i, j))
            {
                YellowSquare_sprite.SetPosition(i * CFDCP, j * CFDCP);
                YellowSquare_sprite.Draw(window);
            }
            break;
        }
        if (IsAllowedMF(ox, oy, i, j))
        {
            DarkCircle_sprite.SetPosition(i * CFDCP, j * CFDCP);
            DarkCircle_sprite.Draw(window);
        }
    }
    for (i = ox - 1, j = oy - 1; i > LEFT_EXTREME_COORDINATE  - 1 && j > TOP_EXTREME_COORDINATE - 1; i--, j--)
    {
        if (board[j][i] > 0)
        {
            if (FIGURE_COLOR(board[j][i]) == OpponentColor && IsAllowedMF(ox, oy, i, j))
            {
                YellowSquare_sprite.SetPosition(i * CFDCP, j * CFDCP);
                YellowSquare_sprite.Draw(window);
            }
            break;
        }
        if (IsAllowedMF(ox, oy, i, j))
        {
            DarkCircle_sprite.SetPosition(i * CFDCP, j * CFDCP);
            DarkCircle_sprite.Draw(window);
        }
    }
}

void BacklightOfPossibleQueenMovements(int OpponentColor, int ox, int oy)
{
    BacklightOfPossibleRookMovements(OpponentColor, ox, oy);
    BacklightOfPossibleBishopMovements(OpponentColor, ox, oy);
}

void BacklightOfPossibleKnightMovements(int OpponentColor, int ox, int oy)
{
    int i, j, l;

    for (j = -2; j < 3; j++)
    {
        if (j == 0)
            continue;
        else if (j == -2 || j == 2)
            i = -1;
        else if (j == -1 || j == 1)
            i = -2;
        for (l= 0; l < 2; l++)
        {
            //if (board[oy + j][ox + i] == 0 && IsAllowedMF(ox, oy, ox + i, oy + j)) ? ??????????, ?? ?? ??????? ???????
            if (board[oy + j][ox + i] == 0)
            {
                DarkCircle_sprite.SetPosition((ox + i) * CFDCP, (oy + j) * CFDCP);
                DarkCircle_sprite.Draw(window);
            }
            else if (board[oy + j][ox + i] > 0 && FIGURE_COLOR(board[oy + j][ox + i]) == OpponentColor && IsAllowedMF(ox, oy, ox + i, oy + j))
            {
                YellowSquare_sprite.SetPosition((ox + i) * CFDCP, (oy + j) * CFDCP);
                YellowSquare_sprite.Draw(window);
            }
            i = -i;
        }
    }
}

void BacklightOfPossibleKingMovements(int OpponentColor, int ox, int oy)
{
    int i, j;
    int KingColor = OpponentColor == BLACK ? WHITE : BLACK;
    int Rook = KingColor | ROOK;
    int rox, rnx, knx;
    bool IsCastlingAllowed;

    for (j = -1; j < 2; j++)
    {
        for (i = -1; i < 2; i++)
        {
            if (j == 0 && i == 0)
                continue;

            if (board[oy + j][ox + i] == 0 && IsAllowedMF(ox, oy, ox + i, oy + j))
            {
                DarkCircle_sprite.SetPosition((ox + i) * CFDCP, (oy + j) * CFDCP);
                DarkCircle_sprite.Draw(window);
            }
            else if (board[oy + j][ox + i] > 0 && FIGURE_COLOR(board[oy + j][ox + i]) == OpponentColor && IsAllowedMF(ox, oy, ox + i, oy + j))
            {
                YellowSquare_sprite.SetPosition((ox + i) * CFDCP, (oy + j) * CFDCP);
                YellowSquare_sprite.Draw(window);
            }
        }
    }

    if (!IS_MOVE(board[oy][ox]))
    {
        for (i = ox - 1; i > LEFT_EXTREME_COORDINATE  - 1; i--)
            if (board[oy][i] > 0)
                break;

        if (i == 1 && FIGURE(board[oy][i]) == Rook)
        {
            rox = 1;
            rnx = ox - 1;
            knx = ox - 2;
            IsCastlingAllowed = !CheckingKingOnShah(KingColor) && IsKingCrossingSafeField(ox, rnx, oy) && IsKingCrossingSafeField(ox, knx, oy) && !DKORM(ox, oy, rox, oy);
            if (IsCastlingAllowed)
            {
                LightCircle_sprite.SetPosition((ox - 2) * CFDCP, oy * CFDCP);
                LightCircle_sprite.Draw(window);
            }
        }

        for (i = ox + 1; i < RIGHT_EXTREME_COORDINATE + 1; i++)
            if (board[oy][i] > 0)
                break;

        if (i == 8 && FIGURE(board[oy][i]) == Rook)
        {
            rox = 8;
            rnx = ox + 1;
            knx = ox + 2;
            IsCastlingAllowed = !CheckingKingOnShah(KingColor) && IsKingCrossingSafeField(ox, rnx, oy) && IsKingCrossingSafeField(ox, knx, oy) && !DKORM(ox, oy, rox, oy);
            if (IsCastlingAllowed)
            {
                LightCircle_sprite.SetPosition((ox + 2) * CFDCP, oy * CFDCP);
                LightCircle_sprite.Draw(window);
            }
        }
    }
}

void BacklightOfKingUnderShah(int ox, int oy)
{
    int kingx, kingy;
    kingx = kingy = 0;

    if (CheckingKingOnShah(BLACK))
    {
        kingx = blackKing.x;
        kingy = blackKing.y;
    }
    else if (CheckingKingOnShah(WHITE))
    {
        kingx = whiteKing.x;
        kingy = whiteKing.y;
    }

    if (kingx != 0 && kingy != 0)
    {
        RedSquare_sprite.SetPosition(kingx * CFDCP, kingy * CFDCP);
        RedSquare_sprite.Draw(window);
    }
}
