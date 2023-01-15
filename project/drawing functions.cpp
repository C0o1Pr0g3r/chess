#include "global constants.h"
#include "external declaration of global variables.h"
#include "drawing functions.h"
#include "backlight functions.h"
#include "checks.h"
#include "button class.h"
#include "label class.h"

void DrawApp(void)
{
    window.clear();
    switch(CurrentScreen)
    {
        case MainMenuScreen:
            DrawMainMenuScreen();
            break;
        case ChessGameScreen:
            DrawChessGameScreen();
            break;
    }
    window.display();
}

void DrawMainMenuScreen(void)
{
    MainMenu_background.Draw(window);
    NewGame_button.Draw(window);
    Options_button.Draw(window);
    ExitFromApp_button.Draw(window);
    if (IsThereSavedGame)
        BackToGameMM_button.Draw(window);
    DrawOptionsWindow();
    DrawGameSaveWindow();
}

void DrawChessGameScreen(void)
{
    DrawStaticChessGameObjects();
    DrawWhoseMoveInscription();
    DrawFigures();
    DrawBacklight(OCC.x, OCC.y);
    DrawPawnTransformation();
    DrawGameOverWindow();
    DrawGameOnPauseWindow();
    DrawGameSaveWindow();
}

inline void DrawStaticChessGameObjects(void)
{
    ChessGame_background.Draw(window);
    PauseGame_button.Draw(window);
    FlipChessboard_button.Draw(window);
    DrawChessboard();
    EatenFigures_label.Draw(window);
    DrawSmallFigures();
}

inline void DrawWhoseMoveInscription(void)
{
    if (WhoseMove)
    {
        BlackMove_label.Draw(window);
    }
    else
    {
        WhiteMove_label.Draw(window);
    }
}

inline void DrawChessboard(void)
{
    if (ChessboardIsInverted)
        InvertedChessboard_sprite.Draw(window);
    else
        OrdinaryChessboard_sprite.Draw(window);
}

inline void DrawPawnTransformation(void)
{
    if (PawnReachedLastHorizontal)
    {
        if (CurrentGameMode == PlayerVersusPlayer || (CurrentGameMode == PlayerVersusEnvironment && WhoseMove == EnvironmentMove))
        {
            BackgroundDimmer.Draw(window);
            PawnTransformation_window.Draw(window);
            DQ->Draw(window);
            DB->Draw(window);
            DK->Draw(window);
            DR->Draw(window);
        }
    }
}

inline void DrawGameOverWindow(void)
{
    if (GameIsOver)
    {
        BackgroundDimmer.Draw(window);
        GameOver_window.Draw(window);

        if (GameIsOver == 1 || GameIsOver == 2)
        {
            Mat_label.Draw(window);

            if (GameIsOver == 1)
                BlackWin_label.Draw(window);
            else if (GameIsOver == 2)
                WhiteWin_label.Draw(window);
        }
        else if (GameIsOver == 3)
        {
            Pat_label.Draw(window);
            Standoff_label.Draw(window);
        }

        BeginNewGame_button.Draw(window);
        GoToMenu_button.Draw(window);
    }
}

inline void DrawGameOnPauseWindow(void)
{
    if (CurrentWindow == GameOnPauseWindow)
    {
        BackgroundDimmer.Draw(window);
        GamePause_window.Draw(window);
        BackToGame_button.Draw(window);
        SaveGame_button.Draw(window);
        ExitFromChessGame_button.Draw(window);
    }
}

inline void DrawOptionsWindow(void)
{
    if (CurrentWindow == OptionsWindow)
    {
        BackgroundDimmer.Draw(window);
        Options_window.Draw(window);
        ExitFromOptionsWindow_button.Draw(window);
        GameMode_label.Draw(window);
        PieceColor_label.Draw(window);
        LevelOfDifficulty_label.Draw(window);
        PvE_radioButton.Draw(window);
        PvP_radioButton.Draw(window);
        White_radioButton.Draw(window);
        Black_radioButton.Draw(window);
        EasyLvl_radioButton.Draw(window);
        MediumLvl_radioButton.Draw(window);
        DifficultLvl_radioButton.Draw(window);
    }
}

inline void DrawGameSaveWindow(void)
{
    if (CurrentWindow == GameSaveWindow)
    {
        BackgroundDimmer.Draw(window);
        GameSave_window.Draw(window);
        WouldYouLikeToSaveGame_label.Draw(window);
        GSWYes_button.Draw(window);
        GSWNo_button.Draw(window);
    }
}

void DrawFigures(void)
{
    int i, j;

    for (i = 0; i < LENGTH; i++)
    {
        for (j = 0; j < LENGTH; j++)
        {
            if (board[i][j] > 0)
            {
                if (FIGURE(board[i][j]) == FIGURE(BLACK_PAWN))
                {
                    BlackPawn_sprite.SetPosition(j * CFDCP, i * CFDCP);
                    BlackPawn_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(WHITE_PAWN))
                {
                    WhitePawn_sprite.SetPosition(j * CFDCP, i * CFDCP);
                    WhitePawn_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(BLACK_ROOK))
                {
                    BlackRook_sprite.SetPosition(j * CFDCP, i * CFDCP);
                    BlackRook_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(WHITE_ROOK))
                {
                    WhiteRook_sprite.SetPosition(j * CFDCP, i * CFDCP);
                    WhiteRook_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(BLACK_KNIGHT))
                {
                    BlackKnight_sprite.SetPosition(j * CFDCP, i * CFDCP);
                    BlackKnight_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(WHITE_KNIGHT))
                {
                    WhiteKnight_sprite.SetPosition(j * CFDCP, i * CFDCP);
                    WhiteKnight_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(BLACK_BISHOP))
                {
                    BlackBishop_sprite.SetPosition(j * CFDCP, i * CFDCP);
                    BlackBishop_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(WHITE_BISHOP))
                {
                    WhiteBishop_sprite.SetPosition(j * CFDCP, i * CFDCP);
                    WhiteBishop_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(BLACK_QUEEN))
                {
                    BlackQueen_sprite.SetPosition(j * CFDCP, i * CFDCP);
                    BlackQueen_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(WHITE_QUEEN))
                {
                    WhiteQueen_sprite.SetPosition(j * CFDCP, i * CFDCP);
                    WhiteQueen_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(BLACK_KING))
                {
                    BlackKing_sprite.SetPosition(j * CFDCP, i * CFDCP);
                    BlackKing_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(WHITE_KING))
                {
                    WhiteKing_sprite.SetPosition(j * CFDCP, i * CFDCP);
                    WhiteKing_sprite.Draw(window);
                }
            }
        }
    }
}

void DrawSmallFigures(void)
{
    int i, j;
    int BPs, BRs, BKs, BBs, BQs, WPs, WRs, WKs, WBs, WQs;
    int BPp, BRp, BKp, BBp, BQp, WPp, WRp, WKp, WBp, WQp;
    float BFpy, WFpy;
    BFpy = 580;
    WFpy = 650;

    j = 5;
    BPs = WPs = 50;
    BRs = BKs = BBs = WRs = WKs = WBs = 20;
    BQs = WQs = 15;
    BPp = WPp = 800;
    BRp = WRp = BPp + 140;
    BKp = WKp = BRp + 80;
    BBp = WBp = BKp + 80;
    BQp = WQp = BBp + 80;

    for (i = 0; i < EatenFigures[0]; i++)
        BPs -= j;
    for (i = 0; i < EatenFigures[1]; i++)
        BRs -= j;
    for (i = 0; i < EatenFigures[2]; i++)
        BKs -= j;
    for (i = 0; i < EatenFigures[3]; i++)
        BBs -= j;
    for (i = 0; i < EatenFigures[4]; i++)
        BQs -= j;

    for (i = 0; i < EatenFigures[5]; i++)
        WPs -= j;
    for (i = 0; i < EatenFigures[6]; i++)
        WRs -= j;
    for (i = 0; i < EatenFigures[7]; i++)
        WKs -= j;
    for (i = 0; i < EatenFigures[8]; i++)
        WBs -= j;
    for (i = 0; i < EatenFigures[9]; i++)
        WQs -= j;

    BPp += BPs;
    BRp += BRs;
    BKp += BKs;
    BBp += BBs;
    BQp += BQs;
    WPp += WPs;
    WRp += WRs;
    WKp += WKs;
    WBp += WBs;
    WQp += WQs;

    for (i = 0; i < EatenFigures[0]; i++)
    {
        SmallBlackPawn_sprite.SetPosition(BPp, BFpy);
        SmallBlackPawn_sprite.Draw(window);
        BPp += 10;
    }
    for (i = 0; i < EatenFigures[1]; i++)
    {
        SmallBlackRook_sprite.SetPosition(BRp, BFpy);
        SmallBlackRook_sprite.Draw(window);
        BRp += 10;
    }
    for (i = 0; i < EatenFigures[2]; i++)
    {
        SmallBlackKnight_sprite.SetPosition(BKp, BFpy);
        SmallBlackKnight_sprite.Draw(window);
        BKp += 10;
    }
    for (i = 0; i < EatenFigures[3]; i++)
    {
        SmallBlackBishop_sprite.SetPosition(BBp, BFpy);
        SmallBlackBishop_sprite.Draw(window);
        BBp += 10;
    }
    for (i = 0; i < EatenFigures[4]; i++)
    {
        SmallBlackQueen_sprite.SetPosition(BQp, BFpy);
        SmallBlackQueen_sprite.Draw(window);
        BQp += 10;
    }

    for (i = 0; i < EatenFigures[5]; i++)
    {
        SmallWhitePawn_sprite.SetPosition(WPp, WFpy);
        SmallWhitePawn_sprite.Draw(window);
        WPp += 10;
    }
    for (i = 0; i < EatenFigures[6]; i++)
    {
        SmallWhiteRook_sprite.SetPosition(WRp, WFpy);
        SmallWhiteRook_sprite.Draw(window);
        WRp += 10;
    }
    for (i = 0; i < EatenFigures[7]; i++)
    {
        SmallWhiteKnight_sprite.SetPosition(WKp, WFpy);
        SmallWhiteKnight_sprite.Draw(window);
        WKp += 10;
    }
    for (i = 0; i < EatenFigures[8]; i++)
    {
        SmallWhiteBishop_sprite.SetPosition(WBp, WFpy);
        SmallWhiteBishop_sprite.Draw(window);
        WBp += 10;
    }
    for (i = 0; i < EatenFigures[9]; i++)
    {
        SmallWhiteQueen_sprite.SetPosition(WQp, WFpy);
        SmallWhiteQueen_sprite.Draw(window);
        WQp += 10;
    }
}
