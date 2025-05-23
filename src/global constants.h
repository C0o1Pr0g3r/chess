#ifndef GLOBAL_CONSTANTS_H_INCLUDED
#define GLOBAL_CONSTANTS_H_INCLUDED

#define KING 1
#define QUEEN 2
#define BISHOP 3
#define KNIGHT 4
#define ROOK 5
#define PAWN 6
#define MOVE 8
#define RIGHT 16
#define BLACK 32
#define WHITE 64

#define BLACK_KING (BLACK | KING)
#define BLACK_QUEEN (BLACK | QUEEN)
#define BLACK_BISHOP (BLACK | BISHOP)
#define BLACK_KNIGHT (BLACK | KNIGHT)
#define BLACK_ROOK (BLACK | ROOK)
#define BLACK_PAWN (BLACK | PAWN)
#define WHITE_KING (WHITE | KING)
#define WHITE_QUEEN (WHITE | QUEEN)
#define WHITE_BISHOP (WHITE | BISHOP)
#define WHITE_KNIGHT (WHITE | KNIGHT)
#define WHITE_ROOK (WHITE | ROOK)
#define WHITE_PAWN (WHITE | PAWN)

#define FIGURE_COLOR(figure) ((figure) & (BLACK | WHITE))
#define FIGURE_TYPE(figure) ((figure) & 7)
#define FIGURE(x) (FIGURE_COLOR(x) | FIGURE_TYPE(x))
#define IS_MOVE(figure) ((figure) & MOVE)

#define LENGTH 10
#define CFDCP 80   //Recoding Coordinages For Drawing

#define LEFT_EXTREME_COORDINATE 1
#define RIGHT_EXTREME_COORDINATE 8
#define TOP_EXTREME_COORDINATE 1
#define BOTTOM_EXTREME_COORDINATE 8

#define BOARD_SIZE 10
#define NUMBER_OF_EATEN_FIGURES 10
#define FIGURE_TYPE_STRING_LENGTH 24

enum AppScreens {MainMenuScreen, ChessGameScreen};
enum GameModes {PlayerVersusEnvironment, PlayerVersusPlayer};
enum GameWindows {MissingWindow, OptionsWindow, GameOnPauseWindow, GameOverWindow, PawnTransformationWindow, GameSaveWindow};

#endif // GLOBAL_CONSTANTS_H_INCLUDED
