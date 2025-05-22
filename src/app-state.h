#ifndef APP_STATE_H_INCLUDED
#define APP_STATE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "global constants.h"
#include "drawn object class.h"
#include "button class.h"
#include "label class.h"
#include "radio button class.h"

using namespace std;
using namespace sf;

struct AppState {
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

    Vector2i blackKing, whiteKing, GroupOfFigures[8];

    int EatenFigures[10];

    RenderWindow window;
    Vector2u InitialWindowSize = {1274, 800};
    Vector2f WSC = {1, 1};   //Window Size Coefficient
    Vector2u OWS = InitialWindowSize, NWS;   //Old Window Size, New Window Size
    Vector2i MC, OCC, CC, PTC;   //Mouse Coordinates, Old Chessboard Coordinates, Chessboard Coordinates, Pawn Transformation Coordinates
    bool LeftMouseButtonIsPressed, RightMouseButtonIsPressed, EscapeIsPressed;

    AppScreens CurrentScreen;
    GameWindows CurrentWindow;
    GameModes CurrentGameMode;

    Vector2i CFRCPC = {CFDCP, CFDCP};   //Coefficient For Reading Chess Piece Coordinates

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

    string AllMovesInGame, NextEnvironmentMove, CurrentChessNote;

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
};

#endif // APP_STATE_H_INCLUDED
