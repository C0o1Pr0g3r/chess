#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include "global constants.h"
#include "external declaration of global variables.h"
#include "secondary functions.h"
#include "checks.h"
#include "move functions.h"
#include "coordinate processing functions.h"
#include "handling functions.h"
#include "connector.hpp"
#include "button class.h"

using namespace std;

void HandleApp(void)
{
    switch(CurrentScreen)
    {
        case MainMenuScreen:
            HandleMainMenuScreen();
            break;
        case ChessGameScreen:
            HandleChessGameScreen();
            break;
    }
}

void HandleMainMenuScreen(void)
{
    if (CurrentWindow == OptionsWindow)
    {
        HandleOptionsWindow();
    }
    else
    {
        if (NewGame_button.IsPressed(window, LeftMouseButtonIsPressed))
        {
            CurrentScreen = ChessGameScreen;
            SetDefaultGameSettings(false);
        }
        else if (Options_button.IsPressed(window, LeftMouseButtonIsPressed))
        {
            CurrentWindow = OptionsWindow;
            ChangeButtonsAvailability(MainMenuScreen, false);
        }
        else if (ExitFromApp_button.IsPressed(window, LeftMouseButtonIsPressed))
        {
            if (HaveThereBeenChangesSinceTheLastSave)
            {
                WriteDataToFile();
                window.close();
            }
            else
            {
                ChangeButtonsAvailability(MainMenuScreen, false);
                CurrentWindow = GameSaveWindow;
            }
        }
        else if (BackToGameMM_button.IsPressed(window, LeftMouseButtonIsPressed))
        {
            CurrentScreen = ChessGameScreen;
        }
        else if (CurrentWindow == GameSaveWindow)
        {
            HandleGameSaveWindow();
        }
    }
}

void HandleChessGameScreen(void)
{
    bool status;
    int ox, oy, nx, ny;

    GameIsOver = IsGameOver();

    if (!GameIsOver)
    {
        if (PauseGame_button.IsPressed(window, LeftMouseButtonIsPressed))
        {
            CurrentWindow = GameOnPauseWindow;
            ChangeButtonsAvailability(ChessGameScreen, false);
        }
        else if (FlipChessboard_button.IsPressed(window, LeftMouseButtonIsPressed))
        {
            FlipChessboard();
        }
        else if (CurrentWindow == GameOnPauseWindow)
        {
            HandleGameOnPauseWindow();
        }
        else if (CurrentWindow == PawnTransformationWindow)
        {
            HandlePawnTransformationWindow();
        }
        else if (CurrentWindow == GameSaveWindow)
        {
            HandleGameSaveWindow();
        }
        else if (CurrentGameMode == PlayerVersusEnvironment && WhoseMove == EnvironmentMove)
        {
            CurrentChessNote = GetNextEnvironmentMove(&ox, &oy, &nx, &ny);
            cout << CurrentChessNote << endl;
            AdditionalActionsBeforeMovingFigure(ox, oy, nx, ny);
            status = FigureMovementPvEEnvironment(ox, oy, nx, ny);
            AdditionalActionsAfterMovingFigure(ox, oy, nx, ny, status);
        }
        else
        {
            if (LeftMouseButtonIsPressed)
            {
                RecodeMouseCoordinatesToChecssboardCoordinates();
                if (!(CC.x < LEFT_EXTREME_COORDINATE || CC.x > RIGHT_EXTREME_COORDINATE || CC.y < TOP_EXTREME_COORDINATE || CC.y > BOTTOM_EXTREME_COORDINATE))
                    HandleClickOnChessboard();
            }
            else if (RightMouseButtonIsPressed)
            {
                OutputKingsCoordinates();
                OutputKingsCoordinates();
                OutputPropertiesToConsole();
                StateOfShahs();
                OutputOfChessboardToConsole();
            }
            else if (EscapeIsPressed)
            {
                cout << "Все ходы в игре до хода: " << AllMovesInGame << endl;
            }
        }
    }
    else
    {
        ChangeButtonsAvailability(ChessGameScreen, false);
        HandleGameOverWindow();
    }
}

void HandleClickOnChessboard(void)
{
    bool status;

    if (PieceIsChoose)
    {
        AdditionalActionsBeforeMovingFigure(OCC.x, OCC.y, CC.x, CC.y);
        if (CurrentGameMode == PlayerVersusPlayer)
            status = FigureMovementPvP(OCC.x, OCC.y, CC.x, CC.y);
        else if (CurrentGameMode == PlayerVersusEnvironment)
            status = FigureMovementPvEPlayer(OCC.x, OCC.y, CC.x, CC.y);
        AdditionalActionsAfterMovingFigure(OCC.x, OCC.y, CC.x, CC.y, status);
    }
    else
    {
        FigureSelection(CC.x, CC.y);
    }
}

void HandlePawnTransformationWindow(void)
{
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
        ChangeButtonsAvailability(ChessGameScreen, true);
        RewriteChessNotation();
    }
}

void HandleGameOverWindow(void)
{
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
        ChangeButtonsAvailability(ChessGameScreen, true);
        SetDefaultGameSettings(false);
    }
}

void HandleGameOnPauseWindow(void)
{
    if (BackToGame_button.IsPressed(window, LeftMouseButtonIsPressed))
    {
        CurrentWindow = MissingWindow;
        ChangeButtonsAvailability(ChessGameScreen, true);
    }
    else if (SaveGame_button.IsPressed(window, LeftMouseButtonIsPressed))
    {
        printf("Игра сохранена\n");
        IsThereSavedGame = HaveThereBeenChangesSinceTheLastSave = true;
    }
    else if (ExitFromChessGame_button.IsPressed(window, LeftMouseButtonIsPressed))
    {
        if (HaveThereBeenChangesSinceTheLastSave)
        {
            CurrentWindow = MissingWindow;
            CurrentScreen = MainMenuScreen;
            ChangeButtonsAvailability(ChessGameScreen, true);
        }
        else
        {
            CurrentWindow = GameSaveWindow;
        }
    }
}

void HandleOptionsWindow(void)
{
    if (ExitFromOptionsWindow_button.IsPressed(window, LeftMouseButtonIsPressed))
    {
        CurrentWindow = MissingWindow;
        ChangeButtonsAvailability(MainMenuScreen, true);
        HaveThereBeenChangesSinceTheLastSave = false;
    }
    else if (PvE_radioButton.IsPressed(window, LeftMouseButtonIsPressed))
    {
        SetGameMode(PlayerVersusEnvironment);
        PvE_radioButton.ChangeRadioGroupChoosed();
        White_radioButton.ChangeRadioGroupChoosed();
        MediumLvl_radioButton.ChangeRadioGroupChoosed();
        ChangeOptionsButtonsAvailability(true);
        HaveThereBeenChangesSinceTheLastSave = false;
    }
    else if (PvP_radioButton.IsPressed(window, LeftMouseButtonIsPressed))
    {
        PvP_radioButton.ChangeRadioGroupChoosed();
        SetGameMode(PlayerVersusPlayer);
        ChangeOptionsButtonsAvailability(false);
        DeselectOptionsButtons();
        HaveThereBeenChangesSinceTheLastSave = false;
    }
    else if (White_radioButton.IsPressed(window, LeftMouseButtonIsPressed))
    {
        SetPiecesColorOfPlayer(WHITE);
        White_radioButton.ChangeRadioGroupChoosed();
        HaveThereBeenChangesSinceTheLastSave = false;
    }
    else if (Black_radioButton.IsPressed(window, LeftMouseButtonIsPressed))
    {
        SetPiecesColorOfPlayer(BLACK);
        Black_radioButton.ChangeRadioGroupChoosed();
        HaveThereBeenChangesSinceTheLastSave = false;
    }
    else if (EasyLvl_radioButton.IsPressed(window, LeftMouseButtonIsPressed))
    {
        SetLevelOfDifficulty(0);
        EasyLvl_radioButton.ChangeRadioGroupChoosed();
        HaveThereBeenChangesSinceTheLastSave = false;
    }
    else if (MediumLvl_radioButton.IsPressed(window, LeftMouseButtonIsPressed))
    {
        SetLevelOfDifficulty(1);
        MediumLvl_radioButton.ChangeRadioGroupChoosed();
        HaveThereBeenChangesSinceTheLastSave = false;
    }
    else if (DifficultLvl_radioButton.IsPressed(window, LeftMouseButtonIsPressed))
    {
        SetLevelOfDifficulty(2);
        DifficultLvl_radioButton.ChangeRadioGroupChoosed();
        HaveThereBeenChangesSinceTheLastSave = false;
    }
}

void HandleGameSaveWindow(void)
{
    bool status = false;

    if (GSWYes_button.IsPressed(window, LeftMouseButtonIsPressed))
    {
        printf("Игра сохранена\n");
        status = true;
        IsThereSavedGame = true;
    }
    else if (GSWNo_button.IsPressed(window, LeftMouseButtonIsPressed))
    {
        printf("Игра не сохранена\n");
        SetDefaultGameSettings(false);
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
            ChangeButtonsAvailability(ChessGameScreen, true);
            HaveThereBeenChangesSinceTheLastSave = true;
        }
        else if (CurrentScreen == MainMenuScreen)
        {
            CurrentWindow = MissingWindow;
            ChangeButtonsAvailability(MainMenuScreen, true);
            WriteDataToFile();
            window.close();
        }
    }
}
