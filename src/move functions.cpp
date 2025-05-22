#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include "global constants.h"
#include "move functions.h"
#include "checks.h"
#include "secondary functions.h"
#include "move functions at mat.h"
#include "app-state.h"

bool moveFigure(AppState& appState, int ox, int oy, int nx, int ny)
{
    auto& board = appState.board;

    bool status = false;

    switch (FIGURE_TYPE(board[oy][ox]))
    {
        case FIGURE_TYPE(PAWN): status = movePawn(appState, ox, oy, nx, ny); if (status) TransformationColorDefinition(appState, nx, ny); break;
        case FIGURE_TYPE(ROOK): status = moveRook(appState, ox, oy, nx, ny); break;
        case FIGURE_TYPE(BISHOP): status = moveBishop(appState, ox, oy, nx, ny); break;
        case FIGURE_TYPE(KNIGHT): status = moveKnight(appState, ox, oy, nx, ny); break;
        case FIGURE_TYPE(QUEEN): status = moveQueen(appState, ox, oy, nx, ny); break;
        case FIGURE_TYPE(KING): status = moveKing(appState, ox, oy, nx, ny); break;
    }

    return status;
}

bool FigureMovementPvP(AppState& appState, int ox, int oy, int nx, int ny)
{
    auto& WhoseMove = appState.WhoseMove;
    auto& board = appState.board;
    auto& PieceIsChoose = appState.PieceIsChoose;

    bool IsFigureMovementAllowed;
    bool IsMoveMade = false;
    char FigureType[FIGURE_TYPE_STRING_LENGTH];

    if (WhoseMove && FIGURE_COLOR(board[oy][ox]) == BLACK)
    {
        if (FIGURE_COLOR(board[ny][nx]) != BLACK)
        {
            IsFigureMovementAllowed = IsAllowedMF(appState, ox, oy, nx, ny);
            if (IsFigureMovementAllowed)
            {
                IsMoveMade = moveFigure(appState, ox, oy, nx, ny);
                if (IsMoveMade)
                {
                    PieceIsChoose = false;
                    WhoseMove = false;
                    if (CheckingKingOnShah(appState, WHITE))
                    {
                        printf("Поставлен шах белому королю\n");
                        if (CheckingKingOnMat(appState, WHITE))
                            printf("Поставлен мат белому королю\n");
                    }
                    printf("\n\nХод белых\n\n");
                }
                else
                {
                    PieceIsChoose = false;
                    WhichFigureIsSelected(appState, ox, oy, FigureType);
                    printf("Вы не сделали шаг \"%s\"\n", FigureType);
                }
            }
            else
            {
                PieceIsChoose = false;
                WhichFigureIsSelected(appState, ox, oy, FigureType);
                printf("Вы не сделали шаг \"%s\"\n", FigureType);
            }
        }
        else
        {
            //PieceIsChoose = false;
            WhichFigureIsSelected(appState, ox, oy, FigureType);
            printf("Вы сняли фокус с черной фигуры \"%s\"\n", FigureType);
        }
    }
    else if (!WhoseMove && FIGURE_COLOR(board[oy][ox]) == WHITE)
    {
        if (FIGURE_COLOR(board[ny][nx]) != WHITE)
        {
            IsFigureMovementAllowed = IsAllowedMF(appState, ox, oy, nx, ny);
            if (IsFigureMovementAllowed)
            {
                IsMoveMade = moveFigure(appState, ox, oy, nx, ny);
                if (IsMoveMade)
                {
                    PieceIsChoose = false;
                    WhoseMove = true;
                    if (CheckingKingOnShah(appState, BLACK))
                    {
                        printf("Поставлен шах черному королю\n");
                        if(CheckingKingOnMat(appState, BLACK))
                            printf("Поставлен мат черному королю\n");
                    }
                    printf("\n\nХод черных\n\n");
                }
                else
                {
                    PieceIsChoose = false;
                    WhichFigureIsSelected(appState, ox, oy, FigureType);
                    printf("Вы не сделали шаг фигурой \"%s\"\n", FigureType);
                }
            }
            else
            {
                PieceIsChoose = false;
                WhichFigureIsSelected(appState, ox, oy, FigureType);
                printf("Вы не сделали шаг \"%s\"\n", FigureType);
            }
        }
        else
        {
            //PieceIsChoose = false;
            WhichFigureIsSelected(appState, ox, oy, FigureType);
            printf("Вы сняли фокус с белой фигуры \"%s\"\n", FigureType);
        }
    }

    return IsMoveMade;
}

bool FigureMovementPvEPlayer(AppState& appState, int ox, int oy, int nx, int ny)
{
    auto& WhoseMove = appState.WhoseMove;
    auto& PlayerMove = appState.PlayerMove;
    auto& board = appState.board;
    auto& PlayerColor = appState.PlayerColor;
    auto& PieceIsChoose = appState.PieceIsChoose;
    auto& EnvironmentColor = appState.EnvironmentColor;

    bool IsFigureMovementAllowed;
    bool IsMoveMade = false;
    char FigureType[FIGURE_TYPE_STRING_LENGTH];

    if (WhoseMove == PlayerMove && FIGURE_COLOR(board[oy][ox]) == PlayerColor)
    {
        if (FIGURE_COLOR(board[ny][nx]) != PlayerColor)
        {
            IsFigureMovementAllowed = IsAllowedMF(appState, ox, oy, nx, ny);
            if (IsFigureMovementAllowed)
            {
                IsMoveMade = moveFigure(appState, ox, oy, nx, ny);
                if (IsMoveMade)
                {
                    PieceIsChoose = false;
                    WhoseMove = !PlayerMove;
                    if (CheckingKingOnShah(appState, EnvironmentColor))
                    {
                        printf("Поставлен шах белому королю\n");
                        if (CheckingKingOnMat(appState, EnvironmentColor))
                            printf("Поставлен мат белому королю\n");
                    }
                    printf("\n\nХод белых\n\n");
                }
                else
                {
                    PieceIsChoose = false;
                    WhichFigureIsSelected(appState, ox, oy, FigureType);
                    printf("Вы не сделали шаг \"%s\"\n", FigureType);
                }
            }
            else
            {
                PieceIsChoose = false;
                WhichFigureIsSelected(appState, ox, oy, FigureType);
                printf("Вы не сделали шаг \"%s\"\n", FigureType);
            }
        }
        else
        {
            PieceIsChoose = false;
            WhichFigureIsSelected(appState, ox, oy, FigureType);
            printf("Вы сняли фокус с черной фигуры \"%s\"\n", FigureType);
        }
    }

    return IsMoveMade;
}

bool FigureMovementPvEEnvironment(AppState& appState, int ox, int oy, int nx, int ny)
{
    auto& WhoseMove = appState.WhoseMove;
    auto& EnvironmentMove = appState.EnvironmentMove;
    auto& board = appState.board;
    auto& EnvironmentColor = appState.EnvironmentColor;
    auto& PlayerColor = appState.PlayerColor;
    auto& PieceIsChoose = appState.PieceIsChoose;

    bool IsFigureMovementAllowed;
    bool IsMoveMade = false;
    char FigureType[FIGURE_TYPE_STRING_LENGTH];

    if (WhoseMove == EnvironmentMove && FIGURE_COLOR(board[oy][ox]) == EnvironmentColor)
    {
        if (FIGURE_COLOR(board[ny][nx]) != EnvironmentColor)
        {
            IsFigureMovementAllowed = IsAllowedMF(appState, ox, oy, nx, ny);
            if (IsFigureMovementAllowed)
            {
                IsMoveMade = moveFigure(appState, ox, oy, nx, ny);
                if (IsMoveMade)
                {
                    WhoseMove = !EnvironmentMove;
                    if (CheckingKingOnShah(appState, PlayerColor))
                    {
                        printf("Поставлен шах белому королю\n");
                        if (CheckingKingOnMat(appState, PlayerColor))
                            printf("Поставлен мат белому королю\n");
                    }
                    printf("\n\nХод белых\n\n");
                }
                else
                {
                    PieceIsChoose = false;
                    WhichFigureIsSelected(appState, ox, oy, FigureType);
                    printf("Вы не сделали шаг \"%s\"\n", FigureType);
                }
            }
            else
            {
                PieceIsChoose = false;
                WhichFigureIsSelected(appState, ox, oy, FigureType);
                printf("Вы не сделали шаг \"%s\"\n", FigureType);
            }
        }
        else
        {
            PieceIsChoose = false;
            WhichFigureIsSelected(appState, ox, oy, FigureType);
            printf("Вы сняли фокус с черной фигуры \"%s\"\n", FigureType);
        }
    }

    return IsMoveMade;
}

bool movePawn(AppState& appState, int ox, int oy, int nx, int ny)
{
    auto& board = appState.board;
    auto& ChessboardIsInverted = appState.ChessboardIsInverted;
    auto& PieceIsChoose = appState.PieceIsChoose;
    auto& IsTakingOnAisleActivated = appState.IsTakingOnAisleActivated;
    auto& PawnOnAisleCoordinates = appState.PawnOnAisleCoordinates;
    auto& WhoHasMoved = appState.WhoHasMoved;
    auto& WhoseMove = appState.WhoseMove;
    auto& IsTakingOnAisleUsed = appState.IsTakingOnAisleUsed;

    bool FigureHasMoved = false;
    int step1, step2;

    switch(FIGURE_COLOR(board[oy][ox]))
    {
        case BLACK:
            step1 = 1;
            step2 = 2;
            break;
        case WHITE:
            step1 = -1;
            step2 = -2;
            break;
    }

    if (ChessboardIsInverted)
    {
        step1 = -step1;
        step2 = -step2;
    }

    if (IS_MOVE(board[oy][ox]) && nx == ox && ny == oy + step1 && board[ny][nx] == 0)
    {
        board[ny][nx] = board[oy][ox];
        board[oy][ox] = 0;
        PieceIsChoose = false;
        FigureHasMoved = true;
    }
    else if (!IS_MOVE(board[oy][ox]) && nx == ox && (ny == oy + step1 || (ny == oy + step2 && board[oy + step1][ox] == 0)) && board[ny][nx] == 0)
    {
        board[ny][nx] = board[oy][ox];
        board[oy][ox] = 0;
        PieceIsChoose = false;
        board[ny][nx] |= MOVE;
        FigureHasMoved = true;

        if (ny == oy + step2)
        {
            if (IsTherePawnToActivateTakingOnAisle(appState, nx, ny))
            {
                IsTakingOnAisleActivated = true;
                PawnOnAisleCoordinates = {nx, ny};
                WhoHasMoved = WhoseMove;
            }
        }
    }
    else if ((nx == ox - 1 || nx == ox + 1) && ny == oy + step1 && board[ny][nx] > 0)
    {
        board[ny][nx] = board[oy][ox];
        board[oy][ox] = 0;
        PieceIsChoose = false;
        board[ny][nx] |= MOVE;
        FigureHasMoved = true;
    }
    else if (nx == PawnOnAisleCoordinates.x && ny == oy + step1 && board[ny][nx] == 0 && IsTakingOnAisleActivated)
    {
        board[ny][nx] = board[oy][ox];
        board[oy][ox] = 0;
        PieceIsChoose = false;
        FigureHasMoved = true;
        IsTakingOnAisleUsed = true;
    }

    return FigureHasMoved;
}

bool moveRook(AppState& appState, int ox, int oy, int nx, int ny)
{
    auto& board = appState.board;
    auto& PieceIsChoose = appState.PieceIsChoose;

    bool FigureHasMoved = false;
    int i;

    if (nx == ox && ny > TOP_EXTREME_COORDINATE - 1 && ny < BOTTOM_EXTREME_COORDINATE + 1 && board[ny][nx] >= 0)
    {
        if (ny - oy < 0)
        {
            for (i = oy - 1; i > ny; i--)   //up
            {
                if (board[i][ox] > 0)
                    break;
            }
        }
        else if (ny - oy > 0)
        {
             for (i = oy + 1; i < ny; i++)   //down
             {
                 if (board[i][ox] > 0)
                    break;
             }
        }
        if (i == ny)
        {
            board[ny][nx] = board[oy][ox];
            board[oy][ox] = 0;
            PieceIsChoose = false;
            FigureHasMoved = true;
        }
    }
    else if (nx > LEFT_EXTREME_COORDINATE - 1 && nx < RIGHT_EXTREME_COORDINATE + 1 && ny == oy && board[ny][nx] >= 0)
    {
        if (nx - ox < 0)
        {
             for (i = ox - 1; i > nx; i--)   //left
             {
                 if (board[oy][i] > 0)
                    break;
             }
        }
        else if (nx - ox > 0)
        {
            for (i = ox + 1; i < nx; i++)   //right
            {
                if (board[oy][i] > 0)
                    break;
            }
        }
        if (i == nx)
        {
            board[ny][nx] = board[oy][ox];
            board[oy][ox] = 0;
            PieceIsChoose = false;
            FigureHasMoved = true;
        }
    }
    if (FigureHasMoved && !IS_MOVE(board[ny][nx]))
        board[ny][nx] |= MOVE;
    return FigureHasMoved;
}

bool moveBishop(AppState& appState, int ox, int oy, int nx, int ny)
{
    auto& board = appState.board;
    auto& PieceIsChoose = appState.PieceIsChoose;

    bool FigureHasMoved = false;
    int i, j;

    if (nx - ox == ny - oy && nx < ox && ny < oy && board[ny][nx] >= 0)   //left up
    {
        for (i = ox - 1, j = oy - 1; i > nx; i--, j--)
            if (board[j][i] > 0)
                break;
        if (i == nx)
        {
            board[ny][nx] = board[oy][ox];
            board[oy][ox] = 0;
            PieceIsChoose = false;
            FigureHasMoved = true;
        }
    }
    else if (nx - ox == ny - oy && nx > ox && ny > oy && board[ny][nx] >= 0)   //right down
    {
        for (i = ox + 1, j = oy + 1; i < nx; i++, j++)
            if (board[j][i] > 0)
                break;
        if (i == nx)
        {
            board[ny][nx] = board[oy][ox];
            board[oy][ox] = 0;
            PieceIsChoose = false;
            FigureHasMoved = true;
        }
    }
    else if (-(nx - ox) == ny - oy && nx > ox && ny < oy && board[ny][nx] >= 0)   //right up
    {
        for (i = ox + 1, j = oy - 1; i < nx; i++, j--)
            if (board[j][i] > 0)
                break;
        if (i == nx)
        {
            board[ny][nx] = board[oy][ox];
            board[oy][ox] = 0;
            PieceIsChoose = false;
            FigureHasMoved = true;
        }
    }
    else if (nx - ox == -(ny - oy) && nx < ox && ny > oy && board[ny][nx] >= 0)   //left down
    {
        for (i = ox - 1, j = oy + 1; i > nx; i--, j++)
            if (board[j][i] > 0)
                break;
        if (i == nx)
        {
            board[ny][nx] = board[oy][ox];
            board[oy][ox] = 0;
            PieceIsChoose = false;
            FigureHasMoved = true;
        }
    }
    return FigureHasMoved;
}

bool moveQueen(AppState& appState, int ox, int oy, int nx, int ny)
{
    bool FigureHasMoved = false;
    int i, j;

    FigureHasMoved = moveRook(appState, ox, oy, nx, ny);

    if (!FigureHasMoved)
        FigureHasMoved = moveBishop(appState, ox, oy, nx, ny);

    return FigureHasMoved;
}

bool moveKnight(AppState& appState, int ox, int oy, int nx, int ny)
{
    auto& board = appState.board;
    auto& PieceIsChoose = appState.PieceIsChoose;

    bool FigureHasMoved = false;

    if (ny == oy - 2 && (nx == ox - 1 || nx == ox + 1) && board[ny][nx] >= 0)
    {
        board[ny][nx] = board[oy][ox];
        board[oy][ox] = 0;
        PieceIsChoose = false;
        FigureHasMoved = true;
    }
    else if (ny == oy - 1 && (nx == ox - 2 || nx == ox + 2) && board[ny][nx] >= 0)
    {
        board[ny][nx] = board[oy][ox];
        board[oy][ox] = 0;
        PieceIsChoose = false;
        FigureHasMoved = true;
    }
    else if (ny == oy + 1 && (nx == ox - 2 || nx == ox + 2) && board[ny][nx] >= 0)
    {
        board[ny][nx] = board[oy][ox];
        board[oy][ox] = 0;
        PieceIsChoose = false;
        FigureHasMoved = true;
    }
    else if (ny == oy + 2 && (nx == ox - 1 || nx == ox + 1) && board[ny][nx] >= 0)
    {
        board[ny][nx] = board[oy][ox];
        board[oy][ox] = 0;
        PieceIsChoose = false;
        FigureHasMoved = true;
    }
    return FigureHasMoved;
}

bool moveKing(AppState& appState, int ox, int oy, int nx, int ny)
{
    auto& board = appState.board;
    auto& PieceIsChoose = appState.PieceIsChoose;
    auto& AnimatedRook = appState.AnimatedRook;
    auto& AnimatedRookStartingPosition = appState.AnimatedRookStartingPosition;
    auto& AnimatedRookFinalPosition = appState.AnimatedRookFinalPosition;
    auto& blackKing = appState.blackKing;
    auto& whiteKing = appState.whiteKing;

    bool FigureHasMoved = false;
    bool IsCastlingAllowed = false;
    int i, rox, rnx;
    int KingColor = DetermineFigureColor(appState, ox, oy);

    if ((nx == ox - 1 || nx == ox || nx == ox + 1) && (ny == oy - 1 || ny == oy || ny == oy + 1) && board[ny][nx] >= 0)
    {
        board[ny][nx] = board[oy][ox];
        board[oy][ox] = 0;
        PieceIsChoose = false;
        FigureHasMoved = true;
    }

    else if ((nx == ox - 2 || nx == ox + 2) && ny == oy)
    {
        if (nx < ox)
        {
            for (i = ox - 1; i > LEFT_EXTREME_COORDINATE - 1; i--)
                if (board[oy][i] > 0)
                    break;
            if (FIGURE_TYPE(board[oy][i]) == ROOK)
            {
                rox = i;
                rnx = ox - 1;
                IsCastlingAllowed = !CheckingKingOnShah(appState, KingColor) && IsKingCrossingSafeField(appState, ox, rnx, oy) && !DKORM(appState, ox, oy, rox, oy);
            }
        }
        else if (nx > ox)
        {
            for (i = ox + 1; i < RIGHT_EXTREME_COORDINATE + 1; i++)
                if (board[oy][i] > 0)
                    break;
            if (FIGURE_TYPE(board[oy][i]) == ROOK)
            {
                rox = i;
                rnx = ox + 1;
                IsCastlingAllowed = !CheckingKingOnShah(appState, KingColor) && IsKingCrossingSafeField(appState, ox, rnx, oy) && !DKORM(appState, ox, oy, rox, oy);
            }
        }

        if (IsCastlingAllowed)
        {
            AnimatedRook = board[oy][rox];
            AnimatedRookStartingPosition = {rox, oy};
            AnimatedRookFinalPosition = {rnx, ny};
            DoCastling(appState, ox, nx, rox, rnx, oy);
            PieceIsChoose = false;
            FigureHasMoved = true;
        }
    }

    switch (FIGURE(board[ny][nx]))
    {
        case BLACK_KING: blackKing.x = nx; blackKing.y = ny; break;
        case WHITE_KING: whiteKing.x = nx; whiteKing.y = ny; break;
    }

    if (FigureHasMoved && !IS_MOVE(board[ny][nx]))
        board[ny][nx] |= MOVE;

    return FigureHasMoved;
}

void DoCastling(AppState& appState, int okingx, int nkingx, int orookx, int nrookx, int kry)
{
    auto& board = appState.board;
    auto& blackKing = appState.blackKing;
    auto& whiteKing = appState.whiteKing;

    board[kry][nkingx] = board[kry][okingx];
    board[kry][okingx] = 0;
    board[kry][nrookx] = board[kry][orookx];
    board[kry][orookx] = 0;

    switch (FIGURE(board[kry][nkingx]))
    {
        case BLACK_KING: blackKing.x = nkingx; break;
        case WHITE_KING: whiteKing.x = nkingx; break;
    }

    board[kry][nkingx] |= MOVE;
    board[kry][nrookx] |= MOVE;
}
