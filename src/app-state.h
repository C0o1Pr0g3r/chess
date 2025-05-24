#ifndef APP_STATE_H_INCLUDED
#define APP_STATE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <filesystem>
#include "global constants.h"
#include "drawn object class.h"
#include "button class.h"
#include "label class.h"
#include "radio button class.h"
#include "game-save-api/interface.h"
#include "get-next-move-api/interface.h"

using namespace std;
namespace fs = filesystem;
using namespace sf;

struct AppState {
    fs::path appRootDir;
    int board[BOARD_SIZE][BOARD_SIZE] =
    {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, 37, 36, 35, 34, 33, 35, 36, 37, -1,
        -1, 38, 38, 38, 38, 38, 38, 38, 38, -1,
        -1,  0,  0,  0,  0,  0,  0,  0 , 0, -1,
        -1,  0,  0,  0,  0,  0,  0,  0 , 0, -1,
        -1,  0,  0,  0,  0,  0,  0,  0 , 0, -1,
        -1,  0,  0,  0,  0,  0,  0,  0 , 0, -1,
        -1, 70, 70, 70, 70, 70, 70, 70, 70, -1,
        -1, 69, 68, 67, 66, 65, 67, 68, 69, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
    };

    Vector2i blackKing, whiteKing, GroupOfFigures[8], enPassantTargetSquare;

    int EatenFigures[NUMBER_OF_EATEN_FIGURES];

    RenderWindow window;
    Vector2u InitialWindowSize = {1274, 800};
    Vector2i MC, OCC, CC;   //Mouse Coordinates, Old Chessboard Coordinates, Chessboard Coordinates
    bool LeftMouseButtonIsPressed, RightMouseButtonIsPressed, EscapeIsPressed;

    AppScreens CurrentScreen;
    GameWindows CurrentWindow;
    GameModes CurrentGameMode;

    int GameIsOver;
    bool HaveThereBeenChangesSinceTheLastSave;
    bool IsThereSavedGame;
    bool ChessboardIsInverted;

    bool PieceIsChoose, WhoseMove;
    int PlayerColor, EnvironmentColor;
    bool PlayerMove, EnvironmentMove;
    int LevelOfDifficulty;
    int FigureByOldCoordinates, FigureByNewCoordinates;

    bool PawnReachedLastHorizontal, JustWasPawnTransformation;
    int PawnTransformationColor, AnimatedRook;
    bool IsTakingOnAisleActivated, IsTakingOnAisleUsed, WhoHasMoved;
    Vector2i PawnOnAisleCoordinates, AnimatedRookStartingPosition, AnimatedRookFinalPosition, pNC;

    string NextEnvironmentMove, CurrentChessNote;
    vector<string> AllMovesInGame;

    Texture Chessboards_texture, ChessPieces_texture, SmallChessPieces_texture, Backlight_texture, Backgrounds_texture, Windows_texture,
    MainMenuScreen_guiElements_texture, ChessGameScreen_guiElements_texture, BackgroundDimmer_texture,
    PawnTransformationWindow_guiElements_texture, GameOverWindow_guiElements_texture, GamePauseWindow_guiElements_texture, OptionsWindow_guiElements_texture, GameSaveWindow_guiElements_texture;

    DrawnObject BlackPawn_sprite {Texture()};
    DrawnObject BlackRook_sprite {Texture()};
    DrawnObject BlackKnight_sprite {Texture()};
    DrawnObject BlackBishop_sprite {Texture()};
    DrawnObject BlackQueen_sprite {Texture()};
    DrawnObject BlackKing_sprite {Texture()};

    DrawnObject WhitePawn_sprite {Texture()};
    DrawnObject WhiteRook_sprite {Texture()};
    DrawnObject WhiteKnight_sprite {Texture()};
    DrawnObject WhiteBishop_sprite {Texture()};
    DrawnObject WhiteQueen_sprite {Texture()};
    DrawnObject WhiteKing_sprite {Texture()};

    DrawnObject SmallBlackPawn_sprite {Texture()};
    DrawnObject SmallBlackRook_sprite {Texture()};
    DrawnObject SmallBlackKnight_sprite {Texture()};
    DrawnObject SmallBlackBishop_sprite {Texture()};
    DrawnObject SmallBlackQueen_sprite {Texture()};
    DrawnObject SmallBlackKing_sprite {Texture()};

    DrawnObject SmallWhitePawn_sprite {Texture()};
    DrawnObject SmallWhiteRook_sprite {Texture()};
    DrawnObject SmallWhiteKnight_sprite {Texture()};
    DrawnObject SmallWhiteBishop_sprite {Texture()};
    DrawnObject SmallWhiteQueen_sprite {Texture()};
    DrawnObject SmallWhiteKing_sprite {Texture()};

    DrawnObject DarkCircle_sprite {Texture()};
    DrawnObject LightCircle_sprite {Texture()};
    DrawnObject GreenSquare_sprite {Texture()};
    DrawnObject YellowSquare_sprite {Texture()};
    DrawnObject RedSquare_sprite {Texture()};

    DrawnObject MainMenu_background {Texture()};
    DrawnObject ChessGame_background {Texture()};
    DrawnObject BackgroundDimmer {Texture()};

    DrawnObject PawnTransformation_window {Texture()};
    DrawnObject GameOver_window {Texture()};
    DrawnObject GamePause_window {Texture()};
    DrawnObject Options_window {Texture()};
    DrawnObject GameSave_window {Texture()};

    DrawnObject OrdinaryChessboard_sprite {Texture()};
    DrawnObject InvertedChessboard_sprite {Texture()};

    DrawnObject *pAS;
    DrawnObject *pRAS;

    Label BlackMove_label {Texture()};
    Label WhiteMove_label {Texture()};
    Label EatenFigures_label {Texture()};
    Label Mat_label {Texture()};
    Label Pat_label {Texture()};
    Label BlackWin_label {Texture()};
    Label WhiteWin_label {Texture()};
    Label Standoff_label {Texture()};
    Label GameMode_label {Texture()};
    Label PieceColor_label {Texture()};
    Label LevelOfDifficulty_label {Texture()};
    Label WouldYouLikeToSaveGame_label {Texture()};

    Button NewGame_button {Texture()};
    Button Options_button {Texture()};
    Button ExitFromApp_button {Texture()};
    Button ExitFromOptionsWindow_button {Texture()};
    Button PauseGame_button {Texture()};
    Button FlipChessboard_button {Texture()};
    Button BeginNewGame_button {Texture()};
    Button GoToMenu_button {Texture()};
    Button BackToGame_button {Texture()};
    Button SaveGame_button {Texture()};
    Button ExitFromChessGame_button {Texture()};
    Button GSWYes_button {Texture()};
    Button GSWNo_button {Texture()};
    Button BlackRookPT_icon {Texture()};
    Button BlackKnightPT_icon {Texture()};
    Button BlackBishopPT_icon {Texture()};
    Button BlackQueenPT_icon {Texture()};
    Button WhiteRookPT_icon {Texture()};
    Button WhiteKnightPT_icon {Texture()};
    Button WhiteBishopPT_icon {Texture()};
    Button WhiteQueenPT_icon {Texture()};
    Button BackToGameMM_button {Texture()};
    Button * DQ;
    Button * DB;
    Button * DK;
    Button * DR;

    RadioButton PvE_radioButton {Texture()};
    RadioButton PvP_radioButton {Texture()};
    RadioButton White_radioButton {Texture()};
    RadioButton Black_radioButton {Texture()};
    RadioButton EasyLvl_radioButton {Texture()};
    RadioButton MediumLvl_radioButton {Texture()};
    RadioButton DifficultLvl_radioButton {Texture()};

    GameSaveApi* gameSaveApi;
    GetNextMoveApi* getNextMoveApi;

    SavedGameState getGameStateToStore()
    {
        SavedGameState gameState;

        gameState.blackKing = this->blackKing;
        gameState.whiteKing = this->whiteKing;
        gameState.PawnOnAisleCoordinates = this->PawnOnAisleCoordinates;
        gameState.enPassantTargetSquare = this->enPassantTargetSquare;
        gameState.ChessboardIsInverted = this->ChessboardIsInverted;
        gameState.WhoseMove = this->WhoseMove;
        gameState.IsTakingOnAisleActivated = this->IsTakingOnAisleActivated;
        gameState.IsTakingOnAisleUsed = this->IsTakingOnAisleUsed;
        gameState.CurrentGameMode = this->CurrentGameMode;
        gameState.PlayerColor = this->PlayerColor;
        gameState.LevelOfDifficulty = this->LevelOfDifficulty;
        gameState.AllMovesInGame = this->AllMovesInGame;

        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j){
                gameState.board[i][j] = this->board[i][j];
            }
        }

        for (int i = 0; i < NUMBER_OF_EATEN_FIGURES; ++i)
        {
            gameState.EatenFigures[i] = this->EatenFigures[i];
        }

        return gameState;
    }

    void setStoredGameState(const SavedGameState& gameState)
    {
        this->blackKing = gameState.blackKing;
        this->whiteKing = gameState.whiteKing;
        this->PawnOnAisleCoordinates = gameState.PawnOnAisleCoordinates;
        this->enPassantTargetSquare = gameState.enPassantTargetSquare;
        this->ChessboardIsInverted = gameState.ChessboardIsInverted;
        this->WhoseMove = gameState.WhoseMove;
        this->IsTakingOnAisleActivated = gameState.IsTakingOnAisleActivated;
        this->IsTakingOnAisleUsed = gameState.IsTakingOnAisleUsed;
        this->CurrentGameMode = gameState.CurrentGameMode;
        this->PlayerColor = gameState.PlayerColor;
        this->LevelOfDifficulty = gameState.LevelOfDifficulty;
        this->AllMovesInGame = gameState.AllMovesInGame;

        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            for (int j = 0; j < BOARD_SIZE; ++j){
                this->board[i][j] = gameState.board[i][j];
            }
        }

        for (int i = 0; i < NUMBER_OF_EATEN_FIGURES; ++i)
        {
            this->EatenFigures[i] = gameState.EatenFigures[i];
        }
    }

    AppState(const fs::path& appRootDir, GameSaveApi* gameSaveApi, GetNextMoveApi* getNextMoveApi)
    :
        appRootDir(appRootDir),
        gameSaveApi(gameSaveApi),
        getNextMoveApi(getNextMoveApi)
    {}

    ~AppState()
    {
        delete this->gameSaveApi;
        delete this->getNextMoveApi;
    }
};

#endif // APP_STATE_H_INCLUDED
