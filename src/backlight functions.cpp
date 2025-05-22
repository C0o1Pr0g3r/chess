#include "global constants.h"
#include "checks.h"
#include "secondary functions.h"
#include "backlight functions.h"
#include "app-state.h"

void DrawBacklight(AppState& appState, int x, int y)
{
    auto& PieceIsChoose = appState.PieceIsChoose;

    BacklightOfKingUnderShah(appState, x, y);
    if (PieceIsChoose)
    {
        SelectedFigureBacklight(appState, x, y);
        BacklightOfPossibleMovements(appState, x, y);
    }
}

inline void SelectedFigureBacklight(AppState& appState, int x, int y)
{
    auto& PieceIsChoose = appState.PieceIsChoose;
    auto& GreenSquare_sprite = appState.GreenSquare_sprite;
    auto& window = appState.window;

    if (PieceIsChoose)
    {
        GreenSquare_sprite.SetPosition(x * CFDCP, y * CFDCP);
        GreenSquare_sprite.Draw(window);
    }
}

void BacklightOfPossibleMovements(AppState& appState, int ox, int oy)
{
    auto& PieceIsChoose = appState.PieceIsChoose;
    auto& WhoseMove = appState.WhoseMove;
    auto& FigureByOldCoordinates = appState.FigureByOldCoordinates;
    auto& FigureByNewCoordinates = appState.FigureByNewCoordinates;
    auto& AnimatedRook = appState.AnimatedRook;
    auto& AnimatedRookStartingPosition = appState.AnimatedRookStartingPosition;
    auto& AnimatedRookFinalPosition = appState.AnimatedRookFinalPosition;
    auto& IsTakingOnAisleActivated = appState.IsTakingOnAisleActivated;
    auto& PawnOnAisleCoordinates = appState.PawnOnAisleCoordinates;
    auto& WhoHasMoved = appState.WhoHasMoved;
    auto& IsTakingOnAisleUsed = appState.IsTakingOnAisleUsed;

    int FigureType = DetermineFigureType(appState, ox, oy);
    int OpponentColor = DetermineFigureColor(appState, ox, oy) == BLACK ? WHITE : BLACK;

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
        case PAWN : BacklightOfPossiblePawnMovements(appState, OpponentColor, ox, oy); break;
        case ROOK : BacklightOfPossibleRookMovements(appState, OpponentColor, ox, oy); break;
        case BISHOP : BacklightOfPossibleBishopMovements(appState, OpponentColor, ox, oy); break;
        case QUEEN : BacklightOfPossibleQueenMovements(appState, OpponentColor, ox, oy); break;
        case KNIGHT : BacklightOfPossibleKnightMovements(appState, OpponentColor, ox, oy); break;
        case KING : BacklightOfPossibleKingMovements(appState, OpponentColor, ox, oy); break;
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

void BacklightOfPossiblePawnMovements(AppState& appState, int OpponentColor, int ox, int oy)
{
    auto& ChessboardIsInverted = appState.ChessboardIsInverted;
    auto& board = appState.board;
    auto& DarkCircle_sprite = appState.DarkCircle_sprite;
    auto& window = appState.window;
    auto& YellowSquare_sprite = appState.YellowSquare_sprite;
    auto& PawnOnAisleCoordinates = appState.PawnOnAisleCoordinates;
    auto& IsTakingOnAisleActivated = appState.IsTakingOnAisleActivated;

    int Figure = DetermineFigure(appState, ox, oy);
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

    if (board[oy + step1][ox] == 0 && IsAllowedMF(appState, ox, oy, ox, oy + step1))
    {
        DarkCircle_sprite.SetPosition(ox * CFDCP, (oy + step1) * CFDCP);
        DarkCircle_sprite.Draw(window);
    }
    if (board[oy + step2][ox] == 0 && board[oy + step1][ox] == 0 && !IS_MOVE(board[oy][ox]) && IsAllowedMF(appState, ox, oy, ox, oy + step2))
    {
        DarkCircle_sprite.SetPosition(ox * CFDCP, (oy + step2) * CFDCP);
        DarkCircle_sprite.Draw(window);
    }
    if (board[oy + step1][ox - 1] > 0 && FIGURE_COLOR(board[oy + step1][ox - 1]) == OpponentColor && IsAllowedMF(appState, ox, oy, ox - 1, oy + step1))
    {
        YellowSquare_sprite.SetPosition((ox - 1) * CFDCP, (oy + step1) * CFDCP);
        YellowSquare_sprite.Draw(window);
    }
    if (board[oy + step1][ox + 1] > 0 && FIGURE_COLOR(board[oy + step1][ox + 1]) == OpponentColor && IsAllowedMF(appState, ox, oy, ox + 1, oy + step1))
    {
        YellowSquare_sprite.SetPosition((ox + 1) * CFDCP, (oy + step1) * CFDCP);
        YellowSquare_sprite.Draw(window);
    }
    if (oy == PawnOnAisleCoordinates.y && board[oy + step1][PawnOnAisleCoordinates.x] == 0 && IsTakingOnAisleActivated && IsAllowedMF(appState, ox, oy, PawnOnAisleCoordinates.x, oy + step1))
    {
        DarkCircle_sprite.SetPosition(PawnOnAisleCoordinates.x * CFDCP, (oy + step1) * CFDCP);
        DarkCircle_sprite.Draw(window);
    }
}

void BacklightOfPossibleRookMovements(AppState& appState, int OpponentColor, int ox, int oy)
{
    auto& board = appState.board;
    auto& YellowSquare_sprite = appState.YellowSquare_sprite;
    auto& window = appState.window;
    auto& DarkCircle_sprite = appState.DarkCircle_sprite;

    int i, j;

    for (i = oy - 1; i > TOP_EXTREME_COORDINATE - 1; i--)   //up
    {
        if (board[i][ox] > 0)
        {
            if (FIGURE_COLOR(board[i][ox]) == OpponentColor && IsAllowedMF(appState, ox, oy, ox, i))
            {
                YellowSquare_sprite.SetPosition(ox * CFDCP, i * CFDCP);
                YellowSquare_sprite.Draw(window);
            }
            break;
        }
        if (IsAllowedMF(appState, ox, oy, ox, i))
        {
            DarkCircle_sprite.SetPosition(ox * CFDCP, i * CFDCP);
            DarkCircle_sprite.Draw(window);
        }
    }
    for (i = oy + 1; i < BOTTOM_EXTREME_COORDINATE + 1; i++)   //down
    {
        if (board[i][ox] > 0)
        {
            if (FIGURE_COLOR(board[i][ox]) == OpponentColor && IsAllowedMF(appState, ox, oy, ox, i))
            {
                YellowSquare_sprite.SetPosition(ox * CFDCP, i * CFDCP);
                YellowSquare_sprite.Draw(window);
            }
            break;
        }
        if (IsAllowedMF(appState, ox, oy, ox, i))
        {
            DarkCircle_sprite.SetPosition(ox * CFDCP, i * CFDCP);
            DarkCircle_sprite.Draw(window);
        }
    }
    for (i = ox - 1; i > LEFT_EXTREME_COORDINATE - 1; i--)   //left
    {
        if (board[oy][i] > 0)
        {
            if (FIGURE_COLOR(board[oy][i]) == OpponentColor && IsAllowedMF(appState, ox, oy, i, oy))
            {
                YellowSquare_sprite.SetPosition(i * CFDCP, oy * CFDCP);
                YellowSquare_sprite.Draw(window);
            }
            break;
        }
        if (IsAllowedMF(appState, ox, oy, i, oy))
        {
            DarkCircle_sprite.SetPosition(i * CFDCP, oy * CFDCP);
            DarkCircle_sprite.Draw(window);
        }
    }
    for (i = ox + 1; i < RIGHT_EXTREME_COORDINATE + 1; i++)   //right
    {
        if (board[oy][i] > 0)
        {
            if (FIGURE_COLOR(board[oy][i]) == OpponentColor && IsAllowedMF(appState, ox, oy, i, oy))
            {
                YellowSquare_sprite.SetPosition(i * CFDCP, oy * CFDCP);
                YellowSquare_sprite.Draw(window);
            }
            break;
        }
        if (IsAllowedMF(appState, ox, oy, i, oy))
        {
            DarkCircle_sprite.SetPosition(i * CFDCP, oy * CFDCP);
            DarkCircle_sprite.Draw(window);
        }
    }
}

void BacklightOfPossibleBishopMovements(AppState& appState, int OpponentColor, int ox, int oy)
{
    auto& board = appState.board;
    auto& YellowSquare_sprite = appState.YellowSquare_sprite;
    auto& window = appState.window;
    auto& DarkCircle_sprite = appState.DarkCircle_sprite;

    int i, j;

    for (i = ox + 1, j = oy - 1; i < RIGHT_EXTREME_COORDINATE + 1 && j > TOP_EXTREME_COORDINATE - 1; i++, j--)
    {
        if (board[j][i] > 0)
        {
            if (FIGURE_COLOR(board[j][i]) == OpponentColor && IsAllowedMF(appState, ox, oy, i, j))
            {
                YellowSquare_sprite.SetPosition(i * CFDCP, j * CFDCP);
                YellowSquare_sprite.Draw(window);
            }
            break;
        }
        if (IsAllowedMF(appState, ox, oy, i, j))
        {
            DarkCircle_sprite.SetPosition(i * CFDCP, j * CFDCP);
            DarkCircle_sprite.Draw(window);
        }
    }
    for (i = ox + 1, j = oy + 1; i < RIGHT_EXTREME_COORDINATE + 1 && j < BOTTOM_EXTREME_COORDINATE + 1; i++, j++)
        {
            if (board[j][i] > 0)
        {
            if (FIGURE_COLOR(board[j][i]) == OpponentColor && IsAllowedMF(appState, ox, oy, i, j))
            {
                YellowSquare_sprite.SetPosition(i * CFDCP, j * CFDCP);
                YellowSquare_sprite.Draw(window);
            }
            break;
        }
        if (IsAllowedMF(appState, ox, oy, i, j))
        {
            DarkCircle_sprite.SetPosition(i * CFDCP, j * CFDCP);
            DarkCircle_sprite.Draw(window);
        }
    }
    for (i = ox - 1, j = oy + 1; i > LEFT_EXTREME_COORDINATE - 1 && j < BOTTOM_EXTREME_COORDINATE + 1; i--, j++)
    {
        if (board[j][i] > 0)
        {
            if (FIGURE_COLOR(board[j][i]) == OpponentColor && IsAllowedMF(appState, ox, oy, i, j))
            {
                YellowSquare_sprite.SetPosition(i * CFDCP, j * CFDCP);
                YellowSquare_sprite.Draw(window);
            }
            break;
        }
        if (IsAllowedMF(appState, ox, oy, i, j))
        {
            DarkCircle_sprite.SetPosition(i * CFDCP, j * CFDCP);
            DarkCircle_sprite.Draw(window);
        }
    }
    for (i = ox - 1, j = oy - 1; i > LEFT_EXTREME_COORDINATE  - 1 && j > TOP_EXTREME_COORDINATE - 1; i--, j--)
    {
        if (board[j][i] > 0)
        {
            if (FIGURE_COLOR(board[j][i]) == OpponentColor && IsAllowedMF(appState, ox, oy, i, j))
            {
                YellowSquare_sprite.SetPosition(i * CFDCP, j * CFDCP);
                YellowSquare_sprite.Draw(window);
            }
            break;
        }
        if (IsAllowedMF(appState, ox, oy, i, j))
        {
            DarkCircle_sprite.SetPosition(i * CFDCP, j * CFDCP);
            DarkCircle_sprite.Draw(window);
        }
    }
}

void BacklightOfPossibleQueenMovements(AppState& appState, int OpponentColor, int ox, int oy)
{
    BacklightOfPossibleRookMovements(appState, OpponentColor, ox, oy);
    BacklightOfPossibleBishopMovements(appState, OpponentColor, ox, oy);
}

void BacklightOfPossibleKnightMovements(AppState& appState, int OpponentColor, int ox, int oy)
{
    auto& board = appState.board;
    auto& DarkCircle_sprite = appState.DarkCircle_sprite;
    auto& window = appState.window;
    auto& YellowSquare_sprite = appState.YellowSquare_sprite;

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
            //if (board[oy + j][ox + i] == 0 && IsAllowedMF(appState, ox, oy, ox + i, oy + j)) Ч правильный, но не рабочий вариант
            if (AreCoordsInsideBoard(BOARD_SIZE, oy + j, ox + i) && board[oy + j][ox + i] == 0 && IsAllowedMF(appState, ox, oy, ox + i, oy + j))
            {
                DarkCircle_sprite.SetPosition((ox + i) * CFDCP, (oy + j) * CFDCP);
                DarkCircle_sprite.Draw(window);
            }
            else if (AreCoordsInsideBoard(BOARD_SIZE, oy + j, ox + i) && board[oy + j][ox + i] > 0 && FIGURE_COLOR(board[oy + j][ox + i]) == OpponentColor && IsAllowedMF(appState, ox, oy, ox + i, oy + j))
            {
                YellowSquare_sprite.SetPosition((ox + i) * CFDCP, (oy + j) * CFDCP);
                YellowSquare_sprite.Draw(window);
            }
            i = -i;
        }
    }
}

void BacklightOfPossibleKingMovements(AppState& appState, int OpponentColor, int ox, int oy)
{
    auto& board = appState.board;
    auto& DarkCircle_sprite = appState.DarkCircle_sprite;
    auto& window = appState.window;
    auto& YellowSquare_sprite = appState.YellowSquare_sprite;
    auto& LightCircle_sprite = appState.LightCircle_sprite;

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

            if (board[oy + j][ox + i] == 0 && IsAllowedMF(appState, ox, oy, ox + i, oy + j))
            {
                DarkCircle_sprite.SetPosition((ox + i) * CFDCP, (oy + j) * CFDCP);
                DarkCircle_sprite.Draw(window);
            }
            else if (board[oy + j][ox + i] > 0 && FIGURE_COLOR(board[oy + j][ox + i]) == OpponentColor && IsAllowedMF(appState, ox, oy, ox + i, oy + j))
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
            IsCastlingAllowed = !CheckingKingOnShah(appState, KingColor) && IsKingCrossingSafeField(appState, ox, rnx, oy) && IsKingCrossingSafeField(appState, ox, knx, oy) && !DKORM(appState, ox
, oy, rox, oy);
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
            IsCastlingAllowed = !CheckingKingOnShah(appState, KingColor) && IsKingCrossingSafeField(appState, ox, rnx, oy) && IsKingCrossingSafeField(appState, ox, knx, oy) && !DKORM(appState, ox
, oy, rox, oy);
            if (IsCastlingAllowed)
            {
                LightCircle_sprite.SetPosition((ox + 2) * CFDCP, oy * CFDCP);
                LightCircle_sprite.Draw(window);
            }
        }
    }
}

void BacklightOfKingUnderShah(AppState& appState, int ox, int oy)
{
    auto& blackKing = appState.blackKing;
    auto& whiteKing = appState.whiteKing;
    auto& RedSquare_sprite = appState.RedSquare_sprite;
    auto& window = appState.window;

    int kingx, kingy;
    kingx = kingy = 0;

    if (CheckingKingOnShah(appState, BLACK))
    {
        kingx = blackKing.x;
        kingy = blackKing.y;
    }
    else if (CheckingKingOnShah(appState, WHITE))
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
