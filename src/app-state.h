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
    int board[10][10] =
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

    Event event;

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

    DrawnObject BlackPawn_sprite, BlackRook_sprite, BlackKnight_sprite, BlackBishop_sprite, BlackQueen_sprite, BlackKing_sprite,
    WhitePawn_sprite, WhiteRook_sprite, WhiteKnight_sprite, WhiteBishop_sprite, WhiteQueen_sprite, WhiteKing_sprite,
    SmallBlackPawn_sprite, SmallBlackRook_sprite, SmallBlackKnight_sprite, SmallBlackBishop_sprite, SmallBlackQueen_sprite, SmallBlackKing_sprite,
    SmallWhitePawn_sprite, SmallWhiteRook_sprite, SmallWhiteKnight_sprite, SmallWhiteBishop_sprite, SmallWhiteQueen_sprite, SmallWhiteKing_sprite,
    DarkCircle_sprite, LightCircle_sprite, GreenSquare_sprite, YellowSquare_sprite, RedSquare_sprite,
    MainMenu_background, ChessGame_background, BackgroundDimmer,
    PawnTransformation_window, GameOver_window, GamePause_window, Options_window, GameSave_window,
    OrdinaryChessboard_sprite, InvertedChessboard_sprite,
     * pAS, * pRAS;

    Label BlackMove_label, WhiteMove_label, EatenFigures_label,
    Mat_label, Pat_label,BlackWin_label, WhiteWin_label, Standoff_label,
    GameMode_label, PieceColor_label, LevelOfDifficulty_label,
    WouldYouLikeToSaveGame_label;

    Button NewGame_button, Options_button, ExitFromApp_button, ExitFromOptionsWindow_button,
    PauseGame_button, FlipChessboard_button,
    BeginNewGame_button, GoToMenu_button,
    BackToGame_button, SaveGame_button, ExitFromChessGame_button,
    GSWYes_button, GSWNo_button,
    BlackRookPT_icon, BlackKnightPT_icon, BlackBishopPT_icon, BlackQueenPT_icon, WhiteRookPT_icon, WhiteKnightPT_icon, WhiteBishopPT_icon, WhiteQueenPT_icon, BackToGameMM_button,
    * DQ, * DB, * DK, * DR;

    RadioButton PvE_radioButton, PvP_radioButton, White_radioButton, Black_radioButton, EasyLvl_radioButton, MediumLvl_radioButton, DifficultLvl_radioButton;
};

#endif // APP_STATE_H_INCLUDED
