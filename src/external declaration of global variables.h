#ifndef EXTERNAL_DECLARATION_OF_GLOBAL_VARIABLES_H_INCLUDED
#define EXTERNAL_DECLARATION_OF_GLOBAL_VARIABLES_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "global constants.h"
#include "button class.h"
#include "radio button class.h"
#include "drawn object class.h"
#include "label class.h"

using namespace std;
using namespace sf;

extern int board[10][10];

extern Vector2i blackKing, whiteKing, GroupOfFigures[8];

extern int EatenFigures[10];

extern RenderWindow window;
extern Vector2u InitialWindowSize;
extern Vector2f WSC;   //Window Size Coefficient
extern Vector2u OWS, NWS;   //Old Window Size, New Window Size
extern Vector2i MC, OCC, CC, PTC;   //Mouse Coordinates, Old Chessboard Coordinates, Chessboard Coordinates, Pawn Transformation Coordinates
extern bool LeftMouseButtonIsPressed, RightMouseButtonIsPressed, EscapeIsPressed;

extern AppScreens CurrentScreen;
extern GameWindows CurrentWindow;
extern GameModes CurrentGameMode;

extern Event event;

extern Vector2i CFRCPC;   //Coefficient For Reading Chess Piece Coordinates

extern int GameIsOver;
extern bool HaveThereBeenChangesSinceTheLastSave;
extern bool IsThereSavedGame;
extern bool ChessboardIsInverted;

extern bool PieceIsChoose, WhoseMove;
extern int PlayerColor, EnvironmentColor;
extern bool PlayerMove, EnvironmentMove;
extern int LevelOfDifficulty;
extern int FigureByOldCoordinates, FigureByNewCoordinates;

extern bool PawnReachedLastHorizontal, JustWasPawnTransformation;
extern int PawnTransformationColor, AnimatedRook;
extern bool IsTakingOnAisleActivated, IsTakingOnAisleUsed, WhoHasMoved;
extern Vector2i PawnOnAisleCoordinates, AnimatedRookStartingPosition, AnimatedRookFinalPosition, pNC;

extern string AllMovesInGame, NextEnvironmentMove, CurrentChessNote;

extern Texture Chessboards_texture, ChessPieces_texture, SmallChessPieces_texture, Backlight_texture, Backgrounds_texture, Windows_texture,
MainMenuScreen_guiElements_texture, ChessGameScreen_guiElements_texture, BackgroundDimmer_texture,
PawnTransformationWindow_guiElements_texture, GameOverWindow_guiElements_texture, GamePauseWindow_guiElements_texture, OptionsWindow_guiElements_texture, GameSaveWindow_guiElements_texture;

extern DrawnObject BlackPawn_sprite, BlackRook_sprite, BlackKnight_sprite, BlackBishop_sprite, BlackQueen_sprite, BlackKing_sprite,
WhitePawn_sprite, WhiteRook_sprite, WhiteKnight_sprite, WhiteBishop_sprite, WhiteQueen_sprite, WhiteKing_sprite,
SmallBlackPawn_sprite, SmallBlackRook_sprite, SmallBlackKnight_sprite, SmallBlackBishop_sprite, SmallBlackQueen_sprite, SmallBlackKing_sprite,
SmallWhitePawn_sprite, SmallWhiteRook_sprite, SmallWhiteKnight_sprite, SmallWhiteBishop_sprite, SmallWhiteQueen_sprite, SmallWhiteKing_sprite,
DarkCircle_sprite, LightCircle_sprite, GreenSquare_sprite, YellowSquare_sprite, RedSquare_sprite,
MainMenu_background, ChessGame_background, BackgroundDimmer,
PawnTransformation_window, GameOver_window, GamePause_window, Options_window, GameSave_window,
OrdinaryChessboard_sprite, InvertedChessboard_sprite,
 * pAS, * pRAS;

extern Label BlackMove_label, WhiteMove_label, EatenFigures_label,
Mat_label, Pat_label,BlackWin_label, WhiteWin_label, Standoff_label,
GameMode_label, PieceColor_label, LevelOfDifficulty_label,
WouldYouLikeToSaveGame_label;

extern Button NewGame_button, Options_button, ExitFromApp_button, ExitFromOptionsWindow_button,
PauseGame_button, FlipChessboard_button,
BeginNewGame_button, GoToMenu_button,
BackToGame_button, SaveGame_button, ExitFromChessGame_button,
GSWYes_button, GSWNo_button,
BlackRookPT_icon, BlackKnightPT_icon, BlackBishopPT_icon, BlackQueenPT_icon, WhiteRookPT_icon, WhiteKnightPT_icon, WhiteBishopPT_icon, WhiteQueenPT_icon, BackToGameMM_button,
* DQ, * DB, * DK, * DR;

extern RadioButton PvE_radioButton, PvP_radioButton, White_radioButton, Black_radioButton, EasyLvl_radioButton, MediumLvl_radioButton, DifficultLvl_radioButton;

#endif // EXTERNAL_DECLARATION_OF_GLOBAL_VARIABLES_H_INCLUDED
