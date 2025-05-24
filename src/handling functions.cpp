#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "global constants.h"
#include "secondary functions.h"
#include "checks.h"
#include "move functions.h"
#include "coordinate processing functions.h"
#include "handling functions.h"
#include "button class.h"
#include "app-state.h"

using namespace std;

void HandleApp(AppState& appState)
{
    auto& CurrentScreen = appState.CurrentScreen;

    switch(CurrentScreen)
    {
        case MainMenuScreen:
            HandleMainMenuScreen(appState);
            break;
        case ChessGameScreen:
            HandleChessGameScreen(appState);
            break;
    }
}

void HandleMainMenuScreen(AppState& appState)
{
    auto& CurrentWindow = appState.CurrentWindow;
    auto& NewGame_button = appState.NewGame_button;
    auto& window = appState.window;
    auto& LeftMouseButtonIsPressed = appState.LeftMouseButtonIsPressed;
    auto& CurrentScreen = appState.CurrentScreen;
    auto& Options_button = appState.Options_button;
    auto& ExitFromApp_button = appState.ExitFromApp_button;
    auto& HaveThereBeenChangesSinceTheLastSave = appState.HaveThereBeenChangesSinceTheLastSave;
    auto& BackToGameMM_button = appState.BackToGameMM_button;

    if (CurrentWindow == OptionsWindow)
    {
        HandleOptionsWindow(appState);
    }
    else
    {
        if (NewGame_button.IsPressed(window, LeftMouseButtonIsPressed))
        {
            CurrentScreen = ChessGameScreen;
            SetDefaultGameSettings(appState, false);
        }
        else if (Options_button.IsPressed(window, LeftMouseButtonIsPressed))
        {
            CurrentWindow = OptionsWindow;
            ChangeButtonsAvailability(appState, MainMenuScreen, false);
        }
        else if (ExitFromApp_button.IsPressed(window, LeftMouseButtonIsPressed))
        {
            if (HaveThereBeenChangesSinceTheLastSave)
            {
                if (!appState.gameSaveApi->save(appState.getGameStateToStore()))
                {
                    puts("Не вдалося зберегти дані гри.");
                }
                window.close();
            }
            else
            {
                ChangeButtonsAvailability(appState, MainMenuScreen, false);
                CurrentWindow = GameSaveWindow;
            }
        }
        else if (BackToGameMM_button.IsPressed(window, LeftMouseButtonIsPressed))
        {
            CurrentScreen = ChessGameScreen;
        }
        else if (CurrentWindow == GameSaveWindow)
        {
            HandleGameSaveWindow(appState);
        }
    }
}

void HandleChessGameScreen(AppState& appState)
{
    auto& GameIsOver = appState.GameIsOver;
    auto& PauseGame_button = appState.PauseGame_button;
    auto& window = appState.window;
    auto& LeftMouseButtonIsPressed = appState.LeftMouseButtonIsPressed;
    auto& CurrentWindow = appState.CurrentWindow;
    auto& FlipChessboard_button = appState.FlipChessboard_button;
    auto& CurrentGameMode = appState.CurrentGameMode;
    auto& WhoseMove = appState.WhoseMove;
    auto& EnvironmentMove = appState.EnvironmentMove;
    auto& CurrentChessNote = appState.CurrentChessNote;
    auto& CC = appState.CC;
    auto& RightMouseButtonIsPressed = appState.RightMouseButtonIsPressed;
    auto& EscapeIsPressed = appState.EscapeIsPressed;
    auto& AllMovesInGame = appState.AllMovesInGame;

    bool status;
    int ox, oy, nx, ny;

    GameIsOver = IsGameOver(appState);

    if (!GameIsOver)
    {
        if (PauseGame_button.IsPressed(window, LeftMouseButtonIsPressed))
        {
            CurrentWindow = GameOnPauseWindow;
            ChangeButtonsAvailability(appState, ChessGameScreen, false);
        }
        else if (FlipChessboard_button.IsPressed(window, LeftMouseButtonIsPressed))
        {
            FlipChessboard(appState);
        }
        else if (CurrentWindow == GameOnPauseWindow)
        {
            HandleGameOnPauseWindow(appState);
        }
        else if (CurrentWindow == PawnTransformationWindow)
        {
            HandlePawnTransformationWindow(appState);
        }
        else if (CurrentWindow == GameSaveWindow)
        {
            HandleGameSaveWindow(appState);
        }
        else if (CurrentGameMode == PlayerVersusEnvironment && WhoseMove == EnvironmentMove)
        {
            CurrentChessNote = GetNextEnvironmentMove(appState, &ox, &oy, &nx, &ny);
            printf("Наступний крок комп'ютера: %s.", CurrentChessNote.c_str());
            AdditionalActionsBeforeMovingFigure(appState, ox, oy, nx, ny);
            status = FigureMovementPvEEnvironment(appState, ox, oy, nx, ny);
            AdditionalActionsAfterMovingFigure(appState, ox, oy, nx, ny, status);
        }
        else
        {
            if (LeftMouseButtonIsPressed)
            {
                RecodeMouseCoordinatesToChecssboardCoordinates(appState);
                if (!(CC.x < LEFT_EXTREME_COORDINATE || CC.x > RIGHT_EXTREME_COORDINATE || CC.y < TOP_EXTREME_COORDINATE || CC.y > BOTTOM_EXTREME_COORDINATE))
                    HandleClickOnChessboard(appState);
            }
            else if (RightMouseButtonIsPressed)
            {
                OutputKingsCoordinates(appState);
                OutputKingsCoordinates(appState);
                OutputPropertiesToConsole(appState);
                StateOfShahs(appState);
                OutputOfChessboardToConsole(appState);
            }
        }
    }
    else
    {
        ChangeButtonsAvailability(appState, ChessGameScreen, false);
        HandleGameOverWindow(appState);
    }
}

void HandleClickOnChessboard(AppState& appState)
{
    auto& PieceIsChoose = appState.PieceIsChoose;
    auto& OCC = appState.OCC;
    auto& CC = appState.CC;
    auto& CurrentGameMode = appState.CurrentGameMode;

    bool status;

    if (PieceIsChoose)
    {
        AdditionalActionsBeforeMovingFigure(appState, OCC.x, OCC.y, CC.x, CC.y);
        if (CurrentGameMode == PlayerVersusPlayer)
            status = FigureMovementPvP(appState, OCC.x, OCC.y, CC.x, CC.y);
        else if (CurrentGameMode == PlayerVersusEnvironment)
            status = FigureMovementPvEPlayer(appState, OCC.x, OCC.y, CC.x, CC.y);
        AdditionalActionsAfterMovingFigure(appState, OCC.x, OCC.y, CC.x, CC.y, status);
    }
    else
    {
        FigureSelection(appState, CC.x, CC.y);
    }
}

void HandlePawnTransformationWindow(AppState& appState)
{
    auto& PawnTransformationColor = appState.PawnTransformationColor;
    auto& DQ = appState.DQ;
    auto& window = appState.window;
    auto& LeftMouseButtonIsPressed = appState.LeftMouseButtonIsPressed;
    auto& board = appState.board;
    auto& CC = appState.CC;
    auto& PawnReachedLastHorizontal = appState.PawnReachedLastHorizontal;
    auto& DB = appState.DB;
    auto& DK = appState.DK;
    auto& DR = appState.DR;
    auto& CurrentWindow = appState.CurrentWindow;

    int Rook, Bishop, Knight, Queen;

    Rook = PawnTransformationColor | ROOK;
    Bishop = PawnTransformationColor | BISHOP;
    Knight = PawnTransformationColor | KNIGHT;
    Queen = PawnTransformationColor | QUEEN;

    if (DQ->IsPressed(window, LeftMouseButtonIsPressed))
    {
        board[CC.y][CC.x] = Queen;
        PawnReachedLastHorizontal = false;
    }
    else if (DB->IsPressed(window, LeftMouseButtonIsPressed))
    {
        board[CC.y][CC.x] = Bishop;
        PawnReachedLastHorizontal = false;
    }
    else if (DK->IsPressed(window, LeftMouseButtonIsPressed))
    {
        board[CC.y][CC.x] = Knight;
        PawnReachedLastHorizontal = false;
    }
    else if (DR->IsPressed(window, LeftMouseButtonIsPressed))
    {
        board[CC.y][CC.x] = Rook;
        PawnReachedLastHorizontal = false;
    }

    if (!PawnReachedLastHorizontal)
    {
        CurrentWindow = MissingWindow;
        ChangeButtonsAvailability(appState, ChessGameScreen, true);
        RewriteChessNotation(appState);
    }
}

void HandleGameOverWindow(AppState& appState)
{
    auto& BeginNewGame_button = appState.BeginNewGame_button;
    auto& window = appState.window;
    auto& LeftMouseButtonIsPressed = appState.LeftMouseButtonIsPressed;
    auto& GameIsOver = appState.GameIsOver;
    auto& GoToMenu_button = appState.GoToMenu_button;
    auto& CurrentScreen = appState.CurrentScreen;
    auto& CurrentWindow = appState.CurrentWindow;

    if (BeginNewGame_button.IsPressed(window, LeftMouseButtonIsPressed))
    {
        GameIsOver = 0;
    }
    else if (GoToMenu_button.IsPressed(window, LeftMouseButtonIsPressed))
    {
        GameIsOver = 0;
        CurrentScreen = MainMenuScreen;
    }

    if (!GameIsOver)
    {
        CurrentWindow = MissingWindow;
        ChangeButtonsAvailability(appState, ChessGameScreen, true);
        SetDefaultGameSettings(appState, false);
    }
}

void HandleGameOnPauseWindow(AppState& appState)
{
    auto& BackToGame_button = appState.BackToGame_button;
    auto& window = appState.window;
    auto& LeftMouseButtonIsPressed = appState.LeftMouseButtonIsPressed;
    auto& CurrentWindow = appState.CurrentWindow;
    auto& SaveGame_button = appState.SaveGame_button;
    auto& IsThereSavedGame = appState.IsThereSavedGame;
    auto& HaveThereBeenChangesSinceTheLastSave = appState.HaveThereBeenChangesSinceTheLastSave;
    auto& ExitFromChessGame_button = appState.ExitFromChessGame_button;
    auto& CurrentScreen = appState.CurrentScreen;

    if (BackToGame_button.IsPressed(window, LeftMouseButtonIsPressed))
    {
        CurrentWindow = MissingWindow;
        ChangeButtonsAvailability(appState, ChessGameScreen, true);
    }
    else if (SaveGame_button.IsPressed(window, LeftMouseButtonIsPressed))
    {
#ifdef __EMSCRIPTEN__
        appState.gameSaveApi->save(appState.getGameStateToStore());
#endif // __EMSCRIPTEN__
        puts("Гра збережена.");
        IsThereSavedGame = HaveThereBeenChangesSinceTheLastSave = true;
    }
    else if (ExitFromChessGame_button.IsPressed(window, LeftMouseButtonIsPressed))
    {
        if (HaveThereBeenChangesSinceTheLastSave)
        {
            CurrentWindow = MissingWindow;
            CurrentScreen = MainMenuScreen;
            ChangeButtonsAvailability(appState, ChessGameScreen, true);
        }
        else
        {
            CurrentWindow = GameSaveWindow;
        }
    }
}

void HandleOptionsWindow(AppState& appState)
{
    auto& ExitFromOptionsWindow_button = appState.ExitFromOptionsWindow_button;
    auto& window = appState.window;
    auto& LeftMouseButtonIsPressed = appState.LeftMouseButtonIsPressed;
    auto& CurrentWindow = appState.CurrentWindow;
    auto& HaveThereBeenChangesSinceTheLastSave = appState.HaveThereBeenChangesSinceTheLastSave;
    auto& PvE_radioButton = appState.PvE_radioButton;
    auto& White_radioButton = appState.White_radioButton;
    auto& MediumLvl_radioButton = appState.MediumLvl_radioButton;
    auto& PvP_radioButton = appState.PvP_radioButton;
    auto& Black_radioButton = appState.Black_radioButton;
    auto& EasyLvl_radioButton = appState.EasyLvl_radioButton;
    auto& DifficultLvl_radioButton = appState.DifficultLvl_radioButton;

    if (ExitFromOptionsWindow_button.IsPressed(window, LeftMouseButtonIsPressed))
    {
        CurrentWindow = MissingWindow;
        ChangeButtonsAvailability(appState, MainMenuScreen, true);
        HaveThereBeenChangesSinceTheLastSave = false;
    }
    else if (PvE_radioButton.IsPressed(window, LeftMouseButtonIsPressed))
    {
        SetGameMode(appState, PlayerVersusEnvironment);
        PvE_radioButton.ChangeRadioGroupChoosed();
        White_radioButton.ChangeRadioGroupChoosed();
        MediumLvl_radioButton.ChangeRadioGroupChoosed();
        ChangeOptionsButtonsAvailability(appState, true);
        HaveThereBeenChangesSinceTheLastSave = false;
    }
    else if (PvP_radioButton.IsPressed(window, LeftMouseButtonIsPressed))
    {
        PvP_radioButton.ChangeRadioGroupChoosed();
        SetGameMode(appState, PlayerVersusPlayer);
        ChangeOptionsButtonsAvailability(appState, false);
        DeselectOptionsButtons(appState);
        HaveThereBeenChangesSinceTheLastSave = false;
    }
    else if (White_radioButton.IsPressed(window, LeftMouseButtonIsPressed))
    {
        SetPiecesColorOfPlayer(appState, WHITE);
        White_radioButton.ChangeRadioGroupChoosed();
        HaveThereBeenChangesSinceTheLastSave = false;
    }
    else if (Black_radioButton.IsPressed(window, LeftMouseButtonIsPressed))
    {
        SetPiecesColorOfPlayer(appState, BLACK);
        Black_radioButton.ChangeRadioGroupChoosed();
        HaveThereBeenChangesSinceTheLastSave = false;
    }
    else if (EasyLvl_radioButton.IsPressed(window, LeftMouseButtonIsPressed))
    {
        SetLevelOfDifficulty(appState, 0);
        EasyLvl_radioButton.ChangeRadioGroupChoosed();
        HaveThereBeenChangesSinceTheLastSave = false;
    }
    else if (MediumLvl_radioButton.IsPressed(window, LeftMouseButtonIsPressed))
    {
        SetLevelOfDifficulty(appState, 1);
        MediumLvl_radioButton.ChangeRadioGroupChoosed();
        HaveThereBeenChangesSinceTheLastSave = false;
    }
    else if (DifficultLvl_radioButton.IsPressed(window, LeftMouseButtonIsPressed))
    {
        SetLevelOfDifficulty(appState, 2);
        DifficultLvl_radioButton.ChangeRadioGroupChoosed();
        HaveThereBeenChangesSinceTheLastSave = false;
    }
}

void HandleGameSaveWindow(AppState& appState)
{
    auto& GSWYes_button = appState.GSWYes_button;
    auto& window = appState.window;
    auto& LeftMouseButtonIsPressed = appState.LeftMouseButtonIsPressed;
    auto& IsThereSavedGame = appState.IsThereSavedGame;
    auto& GSWNo_button = appState.GSWNo_button;
    auto& EscapeIsPressed = appState.EscapeIsPressed;
    auto& CurrentWindow = appState.CurrentWindow;
    auto& CurrentScreen = appState.CurrentScreen;
    auto& HaveThereBeenChangesSinceTheLastSave = appState.HaveThereBeenChangesSinceTheLastSave;

    bool status = false;

    if (GSWYes_button.IsPressed(window, LeftMouseButtonIsPressed))
    {
#ifdef __EMSCRIPTEN__
        appState.gameSaveApi->save(appState.getGameStateToStore());
#endif // __EMSCRIPTEN__
        puts("Гра збережена.");
        status = true;
        IsThereSavedGame = true;
    }
    else if (GSWNo_button.IsPressed(window, LeftMouseButtonIsPressed))
    {
        puts("Гра не збережена.");
        SetDefaultGameSettings(appState, false);
        status = true;
        IsThereSavedGame = false;
    }
    else if (EscapeIsPressed)
    {
        CurrentWindow = MissingWindow;
    }

    if (status)
    {
        if (CurrentScreen == ChessGameScreen)
        {
            CurrentWindow = MissingWindow;
            CurrentScreen = MainMenuScreen;
            ChangeButtonsAvailability(appState, ChessGameScreen, true);
            HaveThereBeenChangesSinceTheLastSave = true;
        }
        else if (CurrentScreen == MainMenuScreen)
        {
            CurrentWindow = MissingWindow;
            ChangeButtonsAvailability(appState, MainMenuScreen, true);
            if (!appState.gameSaveApi->save(appState.getGameStateToStore()))
            {
                puts("Не вдалося зберегти дані гри.");
            }
            window.close();
        }
    }
}
