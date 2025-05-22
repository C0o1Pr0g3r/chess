#include "global constants.h"
#include "drawing functions.h"
#include "backlight functions.h"
#include "checks.h"
#include "button class.h"
#include "label class.h"
#include "app-state.h"

void DrawApp(AppState& appState)
{
    auto& window = appState.window;
    auto& CurrentScreen = appState.CurrentScreen;

    window.clear();
    switch(CurrentScreen)
    {
        case MainMenuScreen:
            DrawMainMenuScreen(appState);
            break;
        case ChessGameScreen:
            DrawChessGameScreen(appState);
            break;
    }
    window.display();
}

void DrawMainMenuScreen(AppState& appState)
{
    auto& MainMenu_background = appState.MainMenu_background;
    auto& window = appState.window;
    auto& NewGame_button = appState.NewGame_button;
    auto& Options_button = appState.Options_button;
    auto& ExitFromApp_button = appState.ExitFromApp_button;
    auto& IsThereSavedGame = appState.IsThereSavedGame;
    auto& BackToGameMM_button = appState.BackToGameMM_button;

    MainMenu_background.Draw(window);
    NewGame_button.Draw(window);
    Options_button.Draw(window);
    ExitFromApp_button.Draw(window);
    if (IsThereSavedGame)
        BackToGameMM_button.Draw(window);
    DrawOptionsWindow(appState);
    DrawGameSaveWindow(appState);
}

void DrawChessGameScreen(AppState& appState)
{
    auto& OCC = appState.OCC;

    DrawStaticChessGameObjects(appState);
    DrawWhoseMoveInscription(appState);
    DrawFigures(appState);
    DrawBacklight(appState, OCC.x, OCC.y);
    DrawPawnTransformation(appState);
    DrawGameOverWindow(appState);
    DrawGameOnPauseWindow(appState);
    DrawGameSaveWindow(appState);
}

void DrawStaticChessGameObjects(AppState& appState)
{
    auto& ChessGame_background = appState.ChessGame_background;
    auto& window = appState.window;
    auto& PauseGame_button = appState.PauseGame_button;
    auto& FlipChessboard_button = appState.FlipChessboard_button;
    auto& EatenFigures_label = appState.EatenFigures_label;

    ChessGame_background.Draw(window);
    PauseGame_button.Draw(window);
    FlipChessboard_button.Draw(window);
    DrawChessboard(appState);
    EatenFigures_label.Draw(window);
    DrawSmallFigures(appState);
}

inline void DrawWhoseMoveInscription(AppState& appState)
{
    auto& WhoseMove = appState.WhoseMove;
    auto& BlackMove_label = appState.BlackMove_label;
    auto& window = appState.window;
    auto& WhiteMove_label = appState.WhiteMove_label;

    if (WhoseMove)
    {
        BlackMove_label.Draw(window);
    }
    else
    {
        WhiteMove_label.Draw(window);
    }
}

inline void DrawChessboard(AppState& appState)
{
    auto& ChessboardIsInverted = appState.ChessboardIsInverted;
    auto& InvertedChessboard_sprite = appState.InvertedChessboard_sprite;
    auto& window = appState.window;
    auto& OrdinaryChessboard_sprite = appState.OrdinaryChessboard_sprite;

    if (ChessboardIsInverted)
        InvertedChessboard_sprite.Draw(window);
    else
        OrdinaryChessboard_sprite.Draw(window);
}

inline void DrawPawnTransformation(AppState& appState)
{
    auto& PawnReachedLastHorizontal = appState.PawnReachedLastHorizontal;
    auto& CurrentGameMode = appState.CurrentGameMode;
    auto& WhoseMove = appState.WhoseMove;
    auto& EnvironmentMove = appState.EnvironmentMove;
    auto& BackgroundDimmer = appState.BackgroundDimmer;
    auto& window = appState.window;
    auto& PawnTransformation_window = appState.PawnTransformation_window;
    auto& DQ = appState.DQ;
    auto& DB = appState.DB;
    auto& DK = appState.DK;
    auto& DR = appState.DR;

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

inline void DrawGameOverWindow(AppState& appState)
{
    auto& GameIsOver = appState.GameIsOver;
    auto& BackgroundDimmer = appState.BackgroundDimmer;
    auto& window = appState.window;
    auto& GameOver_window = appState.GameOver_window;
    auto& Mat_label = appState.Mat_label;
    auto& BlackWin_label = appState.BlackWin_label;
    auto& WhiteWin_label = appState.WhiteWin_label;
    auto& Pat_label = appState.Pat_label;
    auto& Standoff_label = appState.Standoff_label;
    auto& BeginNewGame_button = appState.BeginNewGame_button;
    auto& GoToMenu_button = appState.GoToMenu_button;

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

inline void DrawGameOnPauseWindow(AppState& appState)
{
    auto& CurrentWindow = appState.CurrentWindow;
    auto& BackgroundDimmer = appState.BackgroundDimmer;
    auto& window = appState.window;
    auto& GamePause_window = appState.GamePause_window;
    auto& BackToGame_button = appState.BackToGame_button;
    auto& SaveGame_button = appState.SaveGame_button;
    auto& ExitFromChessGame_button = appState.ExitFromChessGame_button;

    if (CurrentWindow == GameOnPauseWindow)
    {
        BackgroundDimmer.Draw(window);
        GamePause_window.Draw(window);
        BackToGame_button.Draw(window);
        SaveGame_button.Draw(window);
        ExitFromChessGame_button.Draw(window);
    }
}

inline void DrawOptionsWindow(AppState& appState)
{
    auto& CurrentWindow = appState.CurrentWindow;
    auto& BackgroundDimmer = appState.BackgroundDimmer;
    auto& window = appState.window;
    auto& Options_window = appState.Options_window;
    auto& ExitFromOptionsWindow_button = appState.ExitFromOptionsWindow_button;
    auto& GameMode_label = appState.GameMode_label;
    auto& PieceColor_label = appState.PieceColor_label;
    auto& LevelOfDifficulty_label = appState.LevelOfDifficulty_label;
    auto& PvE_radioButton = appState.PvE_radioButton;
    auto& PvP_radioButton = appState.PvP_radioButton;
    auto& White_radioButton = appState.White_radioButton;
    auto& Black_radioButton = appState.Black_radioButton;
    auto& EasyLvl_radioButton = appState.EasyLvl_radioButton;
    auto& MediumLvl_radioButton = appState.MediumLvl_radioButton;
    auto& DifficultLvl_radioButton = appState.DifficultLvl_radioButton;

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

inline void DrawGameSaveWindow(AppState& appState)
{
    auto& CurrentWindow = appState.CurrentWindow;
    auto& BackgroundDimmer = appState.BackgroundDimmer;
    auto& window = appState.window;
    auto& GameSave_window = appState.GameSave_window;
    auto& WouldYouLikeToSaveGame_label = appState.WouldYouLikeToSaveGame_label;
    auto& GSWYes_button = appState.GSWYes_button;
    auto& GSWNo_button = appState.GSWNo_button;

    if (CurrentWindow == GameSaveWindow)
    {
        BackgroundDimmer.Draw(window);
        GameSave_window.Draw(window);
        WouldYouLikeToSaveGame_label.Draw(window);
        GSWYes_button.Draw(window);
        GSWNo_button.Draw(window);
    }
}

void DrawFigures(AppState& appState)
{
    auto& board = appState.board;
    auto& BlackPawn_sprite = appState.BlackPawn_sprite;
    auto& window = appState.window;
    auto& WhitePawn_sprite = appState.WhitePawn_sprite;
    auto& BlackRook_sprite = appState.BlackRook_sprite;
    auto& WhiteRook_sprite = appState.WhiteRook_sprite;
    auto& BlackKnight_sprite = appState.BlackKnight_sprite;
    auto& WhiteKnight_sprite = appState.WhiteKnight_sprite;
    auto& BlackBishop_sprite = appState.BlackBishop_sprite;
    auto& WhiteBishop_sprite = appState.WhiteBishop_sprite;
    auto& BlackQueen_sprite = appState.BlackQueen_sprite;
    auto& WhiteQueen_sprite = appState.WhiteQueen_sprite;
    auto& BlackKing_sprite = appState.BlackKing_sprite;
    auto& WhiteKing_sprite = appState.WhiteKing_sprite;

    int i, j;

    for (i = 0; i < LENGTH; i++)
    {
        for (j = 0; j < LENGTH; j++)
        {
            if (board[i][j] > 0)
            {
                if (FIGURE(board[i][j]) == FIGURE(BLACK_PAWN))
                {
                    BlackPawn_sprite.SetPosition({static_cast<float>(j * CFDCP), static_cast<float>(i * CFDCP)});
                    BlackPawn_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(WHITE_PAWN))
                {
                    WhitePawn_sprite.SetPosition({static_cast<float>(j * CFDCP), static_cast<float>(i * CFDCP)});
                    WhitePawn_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(BLACK_ROOK))
                {
                    BlackRook_sprite.SetPosition({static_cast<float>(j * CFDCP), static_cast<float>(i * CFDCP)});
                    BlackRook_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(WHITE_ROOK))
                {
                    WhiteRook_sprite.SetPosition({static_cast<float>(j * CFDCP), static_cast<float>(i * CFDCP)});
                    WhiteRook_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(BLACK_KNIGHT))
                {
                    BlackKnight_sprite.SetPosition({static_cast<float>(j * CFDCP), static_cast<float>(i * CFDCP)});
                    BlackKnight_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(WHITE_KNIGHT))
                {
                    WhiteKnight_sprite.SetPosition({static_cast<float>(j * CFDCP), static_cast<float>(i * CFDCP)});
                    WhiteKnight_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(BLACK_BISHOP))
                {
                    BlackBishop_sprite.SetPosition({static_cast<float>(j * CFDCP), static_cast<float>(i * CFDCP)});
                    BlackBishop_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(WHITE_BISHOP))
                {
                    WhiteBishop_sprite.SetPosition({static_cast<float>(j * CFDCP), static_cast<float>(i * CFDCP)});
                    WhiteBishop_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(BLACK_QUEEN))
                {
                    BlackQueen_sprite.SetPosition({static_cast<float>(j * CFDCP), static_cast<float>(i * CFDCP)});
                    BlackQueen_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(WHITE_QUEEN))
                {
                    WhiteQueen_sprite.SetPosition({static_cast<float>(j * CFDCP), static_cast<float>(i * CFDCP)});
                    WhiteQueen_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(BLACK_KING))
                {
                    BlackKing_sprite.SetPosition({static_cast<float>(j * CFDCP), static_cast<float>(i * CFDCP)});
                    BlackKing_sprite.Draw(window);
                }
                if (FIGURE(board[i][j]) == FIGURE(WHITE_KING))
                {
                    WhiteKing_sprite.SetPosition({static_cast<float>(j * CFDCP), static_cast<float>(i * CFDCP)});
                    WhiteKing_sprite.Draw(window);
                }
            }
        }
    }
}

void DrawSmallFigures(AppState& appState)
{
    auto& EatenFigures = appState.EatenFigures;
    auto& SmallBlackPawn_sprite = appState.SmallBlackPawn_sprite;
    auto& window = appState.window;
    auto& SmallBlackRook_sprite = appState.SmallBlackRook_sprite;
    auto& SmallBlackKnight_sprite = appState.SmallBlackKnight_sprite;
    auto& SmallBlackBishop_sprite = appState.SmallBlackBishop_sprite;
    auto& SmallBlackQueen_sprite = appState.SmallBlackQueen_sprite;
    auto& SmallWhitePawn_sprite = appState.SmallWhitePawn_sprite;
    auto& SmallWhiteRook_sprite = appState.SmallWhiteRook_sprite;
    auto& SmallWhiteKnight_sprite = appState.SmallWhiteKnight_sprite;
    auto& SmallWhiteBishop_sprite = appState.SmallWhiteBishop_sprite;
    auto& SmallWhiteQueen_sprite = appState.SmallWhiteQueen_sprite;

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
        SmallBlackPawn_sprite.SetPosition({static_cast<float>(BPp), BFpy});
        SmallBlackPawn_sprite.Draw(window);
        BPp += 10;
    }
    for (i = 0; i < EatenFigures[1]; i++)
    {
        SmallBlackRook_sprite.SetPosition({static_cast<float>(BRp), BFpy});
        SmallBlackRook_sprite.Draw(window);
        BRp += 10;
    }
    for (i = 0; i < EatenFigures[2]; i++)
    {
        SmallBlackKnight_sprite.SetPosition({static_cast<float>(BKp), BFpy});
        SmallBlackKnight_sprite.Draw(window);
        BKp += 10;
    }
    for (i = 0; i < EatenFigures[3]; i++)
    {
        SmallBlackBishop_sprite.SetPosition({static_cast<float>(BBp), BFpy});
        SmallBlackBishop_sprite.Draw(window);
        BBp += 10;
    }
    for (i = 0; i < EatenFigures[4]; i++)
    {
        SmallBlackQueen_sprite.SetPosition({static_cast<float>(BQp), BFpy});
        SmallBlackQueen_sprite.Draw(window);
        BQp += 10;
    }

    for (i = 0; i < EatenFigures[5]; i++)
    {
        SmallWhitePawn_sprite.SetPosition({static_cast<float>(WPp), WFpy});
        SmallWhitePawn_sprite.Draw(window);
        WPp += 10;
    }
    for (i = 0; i < EatenFigures[6]; i++)
    {
        SmallWhiteRook_sprite.SetPosition({static_cast<float>(WRp), WFpy});
        SmallWhiteRook_sprite.Draw(window);
        WRp += 10;
    }
    for (i = 0; i < EatenFigures[7]; i++)
    {
        SmallWhiteKnight_sprite.SetPosition({static_cast<float>(WKp), WFpy});
        SmallWhiteKnight_sprite.Draw(window);
        WKp += 10;
    }
    for (i = 0; i < EatenFigures[8]; i++)
    {
        SmallWhiteBishop_sprite.SetPosition({static_cast<float>(WBp), WFpy});
        SmallWhiteBishop_sprite.Draw(window);
        WBp += 10;
    }
    for (i = 0; i < EatenFigures[9]; i++)
    {
        SmallWhiteQueen_sprite.SetPosition({static_cast<float>(WQp), WFpy});
        SmallWhiteQueen_sprite.Draw(window);
        WQp += 10;
    }
}
