#include <stdio.h>
#include <cstdlib>
#include "global constants.h"
#include "move functions.h"
#include "checks.h"
#include "secondary functions.h"
#include "app-state.h"

bool movePawnsAtShah(AppState& appState, int FigureColor)
{
    auto& ChessboardIsInverted = appState.ChessboardIsInverted;
    auto& GroupOfFigures = appState.GroupOfFigures;
    auto& board = appState.board;

    bool IsShah = true;
    int AmountOfFigures = NumberOfFigures(appState, FigureColor, PAWN);
    int i;
    int x, y;
    int MainFigure, MinorFigure;
    int step1, step2;

    if (FigureColor == BLACK)
    {
        step1 = 1;
        step2 = 2;
    }
    else
    {
        step1 = -1;
        step2 = -2;
    }

    if (ChessboardIsInverted)
    {
        step1 = -step1;
        step2 = -step2;
    }

    for (i = 0; i < AmountOfFigures; i++)
    {
        x = GroupOfFigures[i].x;
        y = GroupOfFigures[i].y;
        MainFigure = board[y][x];

        if (
            AreCoordsInsideBoard(BOARD_SIZE, y + step2, x) && board[y + step2][x] == 0
            &&
            AreCoordsInsideBoard(BOARD_SIZE, y + step1, x) && board[y + step1][x] == 0
            &&
            AreCoordsInsideBoard(BOARD_SIZE, y, x) && !IS_MOVE(board[y][x]))
        {
            board[y + step2][x] = MainFigure;
            board[y][x] = 0;

            IsShah = CheckingKingOnShah(appState, FigureColor);

            board[y][x] = MainFigure;
            board[y + step2][x] = 0;
            if (!IsShah)
                break;
        }

        if (AreCoordsInsideBoard(BOARD_SIZE, y + step1, x) && board[y + step1][x] == 0)
        {
            board[y + step1][x] = MainFigure;
            board[y][x] = 0;

            IsShah = CheckingKingOnShah(appState, FigureColor);

            board[y][x] = MainFigure;
            board[y + step1][x] = 0;
            if (!IsShah)
                break;
        }

        if (
            AreCoordsInsideBoard(BOARD_SIZE, y + step1, x - 1)
            &&
            board[y + step1][x - 1] > 0 && FIGURE_COLOR(board[y + step1][x - 1]) != FigureColor && FIGURE_TYPE(board[y + step1][x - 1]) != KING)
        {
            MinorFigure = board[y + step1][x - 1];
            board[y + step1][x - 1] = MainFigure;
            board[y][x] = 0;

            IsShah = CheckingKingOnShah(appState, FigureColor);

            board[y][x] = MainFigure;
            board[y + step1][x - 1] = MinorFigure;
            if (!IsShah)
                break;
        }

        if (
            AreCoordsInsideBoard(BOARD_SIZE, y + step1, x + 1)
            &&
            board[y + step1][x + 1] > 0 && FIGURE_COLOR(board[y + step1][x + 1]) != FigureColor && FIGURE_TYPE(board[y + step1][x + 1]) != KING)
        {
            MinorFigure = board[y + step1][x + 1];
            board[y + step1][x + 1] = MainFigure;
            board[y][x] = 0;

            IsShah = CheckingKingOnShah(appState, FigureColor);

            board[y][x] = MainFigure;
            board[y + step1][x + 1] = MinorFigure;
            if (!IsShah)
                break;
        }
    }

    return IsShah;
}

bool moveRooksAtShah(AppState& appState, int FigureColor)
{
    auto& GroupOfFigures = appState.GroupOfFigures;
    auto& board = appState.board;

    bool IsShah = true;
    int AmountOfFigures = NumberOfFigures(appState, FigureColor, ROOK);
    int i, j, k;
    int x, y;
    int MainFigure, MinorFigure;
    bool exit = false;

    for (k = 0; k < AmountOfFigures; k++)
    {
        x = GroupOfFigures[k].x;
        y = GroupOfFigures[k].y;
        MainFigure = board[y][x];

        for (i = y - 1; i > TOP_EXTREME_COORDINATE - 1; i--)   //up
        {
            if (FIGURE_COLOR(board[i][x]) == FigureColor)
                break;

            MinorFigure = board[i][x];
            board[i][x] = MainFigure;
            board[y][x] = 0;

            IsShah = CheckingKingOnShah(appState, FigureColor);

            board[y][x] = MainFigure;
            board[i][x] = MinorFigure;
            if (!IsShah)
            {
                exit = true;
                break;
            }
            if (board[i][x] > 0)
                break;
        }
        if (exit)
            break;

        for (i = x + 1; i < RIGHT_EXTREME_COORDINATE + 1; i++)   //right
        {
            if (FIGURE_COLOR(board[y][i]) == FigureColor)
                break;

            MinorFigure = board[y][i];
            board[y][i] = MainFigure;
            board[y][x] = 0;

            IsShah = CheckingKingOnShah(appState, FigureColor);

            board[y][x] = MainFigure;
            board[y][i] = MinorFigure;
            if (!IsShah)
            {
                exit = true;
                break;
            }
            if (board[y][i] > 0)
                break;
        }
        if (exit)
            break;

        for (i = y + 1; i < BOTTOM_EXTREME_COORDINATE + 1; i++)   //down
        {
            if (FIGURE_COLOR(board[i][x]) == FigureColor)
                break;

            MinorFigure = board[i][x];
            board[i][x] = MainFigure;
            board[y][x] = 0;

            IsShah = CheckingKingOnShah(appState, FigureColor);

            board[y][x] = MainFigure;
            board[i][x] = MinorFigure;
            if (!IsShah)
            {
                exit = true;
                break;
            }
            if (board[i][x] > 0)
                break;
        }
        if (exit)
            break;

        for (i = x - 1; i > LEFT_EXTREME_COORDINATE - 1; i--)   //left
        {
            if (FIGURE_COLOR(board[y][i]) == FigureColor)
                break;

            MinorFigure = board[y][i];
            board[y][i] = MainFigure;
            board[y][x] = 0;

            IsShah = CheckingKingOnShah(appState, FigureColor);

            board[y][x] = MainFigure;
            board[y][i] = MinorFigure;
            if (!IsShah)
            {
                exit = true;
                break;
            }
            if (board[y][i] > 0)
                break;
        }
        if (exit)
            break;
    }

    return IsShah;
}

bool moveBishopsAtShah(AppState& appState, int FigureColor)
{
    auto& GroupOfFigures = appState.GroupOfFigures;
    auto& board = appState.board;

    bool IsShah = true;
    int AmountOfFigures = NumberOfFigures(appState, FigureColor, BISHOP);
    int i, j, k;
    int x, y;
    int MainFigure, MinorFigure;
    bool exit = false;

    for (k = 0; k < AmountOfFigures; k++)
    {
        x = GroupOfFigures[k].x;
        y = GroupOfFigures[k].y;
        MainFigure = board[y][x];

        for (i = x + 1, j = y - 1; i < RIGHT_EXTREME_COORDINATE + 1 && j > TOP_EXTREME_COORDINATE - 1; i++, j--)   //right up
        {
            if (FIGURE_COLOR(board[j][i]) == FigureColor)
                break;

            MinorFigure = board[j][i];
            board[j][i] = MainFigure;
            board[y][x] = 0;

            IsShah = CheckingKingOnShah(appState, FigureColor);

            board[y][x] = MainFigure;
            board[j][i] = MinorFigure;
            if (!IsShah)
            {
                exit = true;
                break;
            }
            if (board[j][i] > 0)
                break;
        }
        if (exit)
            break;

        for (i = x + 1, j = y + 1; i < RIGHT_EXTREME_COORDINATE + 1 && j < BOTTOM_EXTREME_COORDINATE + 1; i++, j++)   //right down
        {
            if (FIGURE_COLOR(board[j][i]) == FigureColor)
                break;

            MinorFigure = board[j][i];
            board[j][i] = MainFigure;
            board[y][x] = 0;

            IsShah = CheckingKingOnShah(appState, FigureColor);

            board[y][x] = MainFigure;
            board[j][i] = MinorFigure;
            if (!IsShah)
            {
                exit = true;
                break;
            }
            if (board[j][i] > 0)
                break;
        }
        if (exit)
            break;

        for (i = x - 1, j = y + 1; i > LEFT_EXTREME_COORDINATE - 1 && j < BOTTOM_EXTREME_COORDINATE + 1; i--, j++)   //left down
        {
            if (FIGURE_COLOR(board[j][i]) == FigureColor)
                break;

            MinorFigure = board[j][i];
            board[j][i] = MainFigure;
            board[y][x] = 0;

            IsShah = CheckingKingOnShah(appState, FigureColor);

            board[y][x] = MainFigure;
            board[j][i] = MinorFigure;
            if (!IsShah)
            {
                exit = true;
                break;
            }
            if (board[j][i] > 0)
                break;
        }
        if (exit)
            break;

        for (i = x - 1, j = y - 1; i > LEFT_EXTREME_COORDINATE - 1 && j > TOP_EXTREME_COORDINATE - 1; i--, j--)   //left up
        {
            if (FIGURE_COLOR(board[j][i]) == FigureColor)
                break;

            MinorFigure = board[j][i];
            board[j][i] = MainFigure;
            board[y][x] = 0;

            IsShah = CheckingKingOnShah(appState, FigureColor);

            board[y][x] = MainFigure;
            board[j][i] = MinorFigure;
            if (!IsShah)
            {
                exit = true;
                break;
            }
            if (board[j][i] > 0)
                break;
        }
        if (exit)
            break;
    }

    return IsShah;
}

bool moveQueenAtShah(AppState& appState, int FigureColor)
{
    auto& GroupOfFigures = appState.GroupOfFigures;
    auto& board = appState.board;

    bool IsShah = true;
    int AmountOfFigures = NumberOfFigures(appState, FigureColor, QUEEN);
    int i, j, k;
    int x, y;
    int MainFigure, MinorFigure;
    bool exit = false;

    for (k = 0; k < AmountOfFigures; k++)
    {
        x = GroupOfFigures[k].x;
        y = GroupOfFigures[k].y;
        MainFigure = board[y][x];

        for (i = y - 1; i > TOP_EXTREME_COORDINATE - 1; i--)   //up
        {
            if (FIGURE_COLOR(board[i][x]) == FigureColor)
                break;

            MinorFigure = board[i][x];
            board[i][x] = MainFigure;
            board[y][x] = 0;

            IsShah = CheckingKingOnShah(appState, FigureColor);

            board[y][x] = MainFigure;
            board[i][x] = MinorFigure;
            if (!IsShah)
            {
                exit = true;
                break;
            }
            if (board[i][x] > 0)
                break;
        }
        if (exit)
            break;

        for (i = x + 1; i < RIGHT_EXTREME_COORDINATE + 1; i++)   //right
        {
            if (FIGURE_COLOR(board[y][i]) == FigureColor)
                break;

            MinorFigure = board[y][i];
            board[y][i] = MainFigure;
            board[y][x] = 0;

            IsShah = CheckingKingOnShah(appState, FigureColor);

            board[y][x] = MainFigure;
            board[y][i] = MinorFigure;
            if (!IsShah)
            {
                exit = true;
                break;
            }
            if (board[y][i] > 0)
                break;
        }
        if (exit)
            break;

        for (i = y + 1; i < BOTTOM_EXTREME_COORDINATE + 1; i++)   //down
        {
            if (FIGURE_COLOR(board[i][x]) == FigureColor)
                break;

            MinorFigure = board[i][x];
            board[i][x] = MainFigure;
            board[y][x] = 0;

            IsShah = CheckingKingOnShah(appState, FigureColor);

            board[y][x] = MainFigure;
            board[i][x] = MinorFigure;
            if (!IsShah)
            {
                exit = true;
                break;
            }
            if (board[i][x] > 0)
                break;
        }
        if (exit)
            break;

        for (i = x - 1; i > LEFT_EXTREME_COORDINATE - 1; i--)   //left
        {
            if (FIGURE_COLOR(board[y][i]) == FigureColor)
                break;

            MinorFigure = board[y][i];
            board[y][i] = MainFigure;
            board[y][x] = 0;

            IsShah = CheckingKingOnShah(appState, FigureColor);

            board[y][x] = MainFigure;
            board[y][i] = MinorFigure;
            if (!IsShah)
            {
                exit = true;
                break;
            }
            if (board[y][i] > 0)
                break;
        }
        if (exit)
            break;

        for (i = x + 1, j = y - 1; i < RIGHT_EXTREME_COORDINATE + 1 && j > TOP_EXTREME_COORDINATE - 1; i++, j--)   //right up
        {
            if (FIGURE_COLOR(board[j][i]) == FigureColor)
                break;

            MinorFigure = board[j][i];
            board[j][i] = MainFigure;
            board[y][x] = 0;

            IsShah = CheckingKingOnShah(appState, FigureColor);

            board[y][x] = MainFigure;
            board[j][i] = MinorFigure;
            if (!IsShah)
            {
                exit = true;
                break;
            }
            if (board[j][i] > 0)
                break;
        }
        if (exit)
            break;

        for (i = x + 1, j = y + 1; i < RIGHT_EXTREME_COORDINATE + 1 && j < BOTTOM_EXTREME_COORDINATE + 1; i++, j++)   //right down
        {
            if (FIGURE_COLOR(board[j][i]) == FigureColor)
                break;

            MinorFigure = board[j][i];
            board[j][i] = MainFigure;
            board[y][x] = 0;

            IsShah = CheckingKingOnShah(appState, FigureColor);

            board[y][x] = MainFigure;
            board[j][i] = MinorFigure;
            if (!IsShah)
            {
                exit = true;
                break;
            }
            if (board[j][i] > 0)
                break;
        }
        if (exit)
            break;

        for (i = x - 1, j = y + 1; i > LEFT_EXTREME_COORDINATE - 1 && j < BOTTOM_EXTREME_COORDINATE + 1; i--, j++)   //left down
        {
            if (FIGURE_COLOR(board[j][i]) == FigureColor)
                break;

            MinorFigure = board[j][i];
            board[j][i] = MainFigure;
            board[y][x] = 0;

            IsShah = CheckingKingOnShah(appState, FigureColor);

            board[y][x] = MainFigure;
            board[j][i] = MinorFigure;
            if (!IsShah)
            {
                exit = true;
                break;
            }
            if (board[j][i] > 0)
                break;
        }
        if (exit)
            break;

        for (i = x - 1, j = y - 1; i > LEFT_EXTREME_COORDINATE - 1 && j > TOP_EXTREME_COORDINATE - 1; i--, j--)   //left up
        {
            if (FIGURE_COLOR(board[j][i]) == FigureColor)
                break;

            MinorFigure = board[j][i];
            board[j][i] = MainFigure;
            board[y][x] = 0;

            IsShah = CheckingKingOnShah(appState, FigureColor);

            board[y][x] = MainFigure;
            board[j][i] = MinorFigure;
            if (!IsShah)
            {
                exit = true;
                break;
            }
            if (board[j][i] > 0)
                break;
        }
        if (exit)
            break;
    }

    return IsShah;
}

bool moveKnightsAtShah(AppState& appState, int FigureColor)
{
    auto& GroupOfFigures = appState.GroupOfFigures;
    auto& board = appState.board;

    bool IsShah = true;
    int AmountOfFigures = NumberOfFigures(appState, FigureColor, KNIGHT);
    int i, j, k, l;
    int x, y;
    int MainFigure, MinorFigure;
    bool exit = false;

    for (k = 0; k < AmountOfFigures; k++)
    {
        x = GroupOfFigures[k].x;
        y = GroupOfFigures[k].y;
        MainFigure = board[y][x];

        for (j = -2; j < 3; j++)
        {
            if (j == 0)
                continue;
            else if (j == -2 || j == 2)
                i = -1;
            else if (j == -1 || j == 1)
                i = -2;

            for (l = 0; l < 2; l++)
            {
                if (y + j > TOP_EXTREME_COORDINATE - 1 && y + j < BOTTOM_EXTREME_COORDINATE + 1 && x + i > LEFT_EXTREME_COORDINATE - 1 && x + i < RIGHT_EXTREME_COORDINATE + 1 && FIGURE_COLOR(board[y + j][x + i]) != FigureColor && FIGURE_TYPE(board[y + j][x + i]) != KING)
                {
                    MinorFigure = board[y + j][x + i];
                    board[y + j][x + i] = MainFigure;
                    board[y][x] = 0;

                    IsShah = CheckingKingOnShah(appState, FigureColor);

                    board[y][x] = MainFigure;
                    board[y + j][x + i] = MinorFigure;

                    if (!IsShah)
                    {
                        exit = true;
                        break;
                    }
                }
                i = -i;
            }
            if (exit)
                break;
        }
        if (exit)
            break;
    }

    return IsShah;
}

bool moveKingAtShah(AppState& appState, int FigureColor)
{
    auto& blackKing = appState.blackKing;
    auto& whiteKing = appState.whiteKing;
    auto& GroupOfFigures = appState.GroupOfFigures;
    auto& board = appState.board;

    bool IsShah = true;
    int AmountOfFigures = NumberOfFigures(appState, FigureColor, KING);
    int i, j, k;
    int x, y;
    int MainFigure, MinorFigure;
    bool exit = false;
    int KSPx, KSPy;   //King's Starting Position
    int * pKSPx, * pKSPy;

    if (FigureColor == BLACK)
    {
        pKSPx = &blackKing.x;
        pKSPy = &blackKing.y;
    }
    else
    {
        pKSPx = &whiteKing.x;
        pKSPy = &whiteKing.y;
    }

    for (k = 0; k < AmountOfFigures; k++)
    {
        x = GroupOfFigures[k].x;
        y = GroupOfFigures[k].y;
        MainFigure = board[y][x];

        for (j = -1; j < 2; j++)
        {
            for (i = -1; i < 2; i++)
            {
                if (j == 0 && i == 0)
                    continue;

                if (y + j > TOP_EXTREME_COORDINATE - 1 && y + j < BOTTOM_EXTREME_COORDINATE + 1 && x + i > LEFT_EXTREME_COORDINATE - 1 && x + i < RIGHT_EXTREME_COORDINATE + 1 && FIGURE_COLOR(board[y + j][x + i]) != FigureColor && FIGURE_TYPE(board[y + j][x + i]) != KING)   // left up up
                {
                    MinorFigure = board[y + j][x + i];
                    board[y + j][x + i] = MainFigure;
                    board[y][x] = 0;
                    *pKSPx = x + i;
                    *pKSPy = y + j;

                    IsShah = CheckingKingOnShah(appState, FigureColor);

                    board[y][x] = MainFigure;
                    board[y + j][x + i] = MinorFigure;

                    if (!IsShah)
                    {
                        exit = true;
                        break;
                    }
                }
            }
            if (exit)
                break;
        }
        if (exit)
                break;
    }
    *pKSPx = x;
    *pKSPy = y;

    return IsShah;
}
