#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <string>
#include "global constants.h"
#include "checks.h"
#include "secondary functions.h"
#include "animation functions.h"
#include "connector.hpp"
#include "app-state.h"
#include <nlohmann/json.hpp>

using namespace std;
using namespace sf;
using json = nlohmann::json;

void PrintErrorAboutLoadingTexture(const char* filePath)
{
    fprintf(stderr, "Виникла помилка при спробі завантажити текстуру з файлу \"%s\".", filePath);
}

bool AreCoordsInsideBoard(int boardSize, int y, int x) {
    return x >= 0 && x < boardSize && y >= 0 && y < boardSize;
}

void OutputOfChessboardToConsole(AppState& appState)
{
    auto& board = appState.board;

    int i, j;

    for (i = 1; i < LENGTH - 1; i++)
    {
        for (j = 1; j < LENGTH - 1; j++)
        {
            printf("%4d", board[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
}

void OutputPropertiesToConsole(AppState& appState)
{
    auto& window = appState.window;
    auto& MC = appState.MC;
    auto& CC = appState.CC;

    printf("Розмір вікна: %dx%d\n.", window.getSize().x, window.getSize().y);
    printf("Координати миші: (%d; %d).\n", MC.x, MC.y);
    printf("Координати дошки: (%d; %d).\n", CC.x, CC.y);
    printf("Розмір шахової клітки: %d.\n", CFDCP);
}

void StateOfShahs(AppState& appState)
{
    char IsShah[] = "поставлено шах", IsNotShah[] = "не поставлено шах";

    printf("Чорним %s.\n", CheckingKingOnShah(appState, BLACK) ? IsShah : IsNotShah);
    printf("Білим %s.\n", CheckingKingOnShah(appState, WHITE) ? IsShah : IsNotShah);
}

void OutputKingsCoordinates(AppState& appState)
{
    auto& blackKing = appState.blackKing;
    auto& whiteKing = appState.whiteKing;

    printf("Координати чорного короля: (%d; %d).\n", blackKing.x, blackKing.y);
    printf("Координати білого короля: (%d; %d).\n", whiteKing.x, whiteKing.y);
}

void SetChessPiecesToTheirOriginalPosition(AppState& appState)
{
    auto& board = appState.board;

    int i, j;

    for (i = 0; i < LENGTH; i++)
    {
        board[0][i] = board[9][i] = board[i][0] = board[i][9] = -1;
    }

    for (i = LEFT_EXTREME_COORDINATE; i < RIGHT_EXTREME_COORDINATE + 1; i++)
    {
        board[TOP_EXTREME_COORDINATE + 1][i] = 38;
        board[BOTTOM_EXTREME_COORDINATE - 1][i] = 70;

        for (j = TOP_EXTREME_COORDINATE + 2; j < BOTTOM_EXTREME_COORDINATE - 1; j++)
            board[j][i] = 0;
    }
    board[TOP_EXTREME_COORDINATE][LEFT_EXTREME_COORDINATE] = board[TOP_EXTREME_COORDINATE][RIGHT_EXTREME_COORDINATE] = BLACK_ROOK;
    board[TOP_EXTREME_COORDINATE][LEFT_EXTREME_COORDINATE + 1] = board[TOP_EXTREME_COORDINATE][RIGHT_EXTREME_COORDINATE - 1] = BLACK_KNIGHT;
    board[TOP_EXTREME_COORDINATE][LEFT_EXTREME_COORDINATE + 2] = board[TOP_EXTREME_COORDINATE][RIGHT_EXTREME_COORDINATE - 2] = BLACK_BISHOP;
    board[TOP_EXTREME_COORDINATE][LEFT_EXTREME_COORDINATE + 3] = BLACK_QUEEN;
    board[TOP_EXTREME_COORDINATE][LEFT_EXTREME_COORDINATE + 4] = BLACK_KING;

    board[BOTTOM_EXTREME_COORDINATE][LEFT_EXTREME_COORDINATE] = board[BOTTOM_EXTREME_COORDINATE][RIGHT_EXTREME_COORDINATE] = WHITE_ROOK;
    board[BOTTOM_EXTREME_COORDINATE][LEFT_EXTREME_COORDINATE + 1] = board[BOTTOM_EXTREME_COORDINATE][RIGHT_EXTREME_COORDINATE - 1] = WHITE_KNIGHT;
    board[BOTTOM_EXTREME_COORDINATE][LEFT_EXTREME_COORDINATE + 2] = board[BOTTOM_EXTREME_COORDINATE][RIGHT_EXTREME_COORDINATE - 2] = WHITE_BISHOP;
    board[BOTTOM_EXTREME_COORDINATE][LEFT_EXTREME_COORDINATE + 3] = WHITE_QUEEN;
    board[BOTTOM_EXTREME_COORDINATE][LEFT_EXTREME_COORDINATE + 4] = WHITE_KING;
}

void ClearEatenFiguresArray(AppState& appState)
{
    auto& EatenFigures = appState.EatenFigures;

    int i;

    for (i = 0; i < 10; i++)
        EatenFigures[i] = 0;
}

void PrintThatFigureSelectedOrNot(bool isSelected, int color, const char* type)
{
    if (isSelected)
    {
        printf("Вибрано %s фігуру для переміщення, а саме — \"%s\".\n", color == WHITE ? "білу" : "чорну", type);
    }
    else
    {
        printf("%s фігура не вибрана через натискання повз фігуру.\n", color == WHITE ? "Біла" : "Чорна");
    }
}

void FigureSelection(AppState& appState, int x, int y)
{
    auto& WhoseMove = appState.WhoseMove;
    auto& board = appState.board;
    auto& OCC = appState.OCC;
    auto& PieceIsChoose = appState.PieceIsChoose;
    auto& WhoHasMoved = appState.WhoHasMoved;
    auto& IsTakingOnAisleActivated = appState.IsTakingOnAisleActivated;
    auto& IsTakingOnAisleUsed = appState.IsTakingOnAisleUsed;
    auto& PawnOnAisleCoordinates = appState.PawnOnAisleCoordinates;

    bool status = false;
    char FigureType[FIGURE_TYPE_STRING_LENGTH];

    if (WhoseMove)
    {
        if (FIGURE_COLOR(board[y][x]) == BLACK && !(x < LEFT_EXTREME_COORDINATE || x > RIGHT_EXTREME_COORDINATE || y < TOP_EXTREME_COORDINATE || y > BOTTOM_EXTREME_COORDINATE))
        {
            OCC.x = x;
            OCC.y = y;
            WhichFigureIsSelected(appState, OCC.x, OCC.y, FigureType);
            PrintThatFigureSelectedOrNot(true, BLACK, FigureType);
            PieceIsChoose = true;
            status = true;
        }
        else
        {
            PrintThatFigureSelectedOrNot(false, BLACK, FigureType);
        }
    }
    else
    {
        if (FIGURE_COLOR(board[y][x]) == WHITE && !(x < LEFT_EXTREME_COORDINATE || x > RIGHT_EXTREME_COORDINATE || y < TOP_EXTREME_COORDINATE || y > BOTTOM_EXTREME_COORDINATE))
        {
            OCC.x = x;
            OCC.y = y;
            WhichFigureIsSelected(appState, OCC.x, OCC.y, FigureType);
            PrintThatFigureSelectedOrNot(true, WHITE, FigureType);
            PieceIsChoose = true;
            status = true;
        }
        else
        {
            PrintThatFigureSelectedOrNot(false, WHITE, FigureType);
        }
    }

    if (status)
    {
        if (WhoseMove == WhoHasMoved)
        {
            IsTakingOnAisleActivated = IsTakingOnAisleUsed = false;
            PawnOnAisleCoordinates = {0, 0};
        }
    }
}

void WhichFigureIsSelected(AppState& appState, int x, int y, char * FigureType)
{
    auto& board = appState.board;

    switch (FIGURE_TYPE(board[y][x]))
    {
        case PAWN: strcpy(FigureType, "Пішак"); break;
        case ROOK: strcpy(FigureType, "Ладья"); break;
        case BISHOP: strcpy(FigureType, "Слон"); break;
        case KNIGHT: strcpy(FigureType, "Кінь"); break;
        case QUEEN: strcpy(FigureType, "Королева"); break;
        case KING: strcpy(FigureType, "Король"); break;
        default: strcpy(FigureType, "Жодна"); break;
    }
}

int WhichFigureHasMoved(AppState& appState, int x, int y)
{
    auto& board = appState.board;

    int FigureColor, FigureType, Figure;

    switch (FIGURE_COLOR(board[y][x]))
    {
        case BLACK: FigureColor = BLACK; break;
        case WHITE: FigureColor = WHITE; break;
    }

    switch (FIGURE_TYPE(board[y][x]))
    {
        case PAWN: FigureType = PAWN; break;
        case ROOK: FigureType = ROOK; break;
        case KNIGHT: FigureType = KNIGHT; break;
        case BISHOP: FigureType = BISHOP; break;
        case QUEEN: FigureType = QUEEN; break;
        case KING: FigureType = KING; break;
    }

    Figure = FigureColor | FigureType;

    return Figure;
}

int DetermineFigureColor(AppState& appState, int x, int y)
{
    auto& board = appState.board;

    int FigureColor;

    switch(FIGURE_COLOR(board[y][x]))
    {
        case BLACK : FigureColor = BLACK; break;
        case WHITE : FigureColor = WHITE; break;
    }

    return FigureColor;
}

int DetermineFigureType(AppState& appState, int x, int y)
{
    auto& board = appState.board;

    int FigureType;

    switch(FIGURE_TYPE(board[y][x]))
    {
        case PAWN : FigureType = PAWN; break;
        case ROOK: FigureType = ROOK; break;
        case KNIGHT: FigureType = KNIGHT; break;
        case BISHOP: FigureType = BISHOP; break;
        case QUEEN: FigureType = QUEEN; break;
        case KING: FigureType = KING; break;
    }

    return FigureType;
}

int DetermineFigure(AppState& appState, int x, int y)
{
    int Figure;

    Figure = DetermineFigureColor(appState, x, y) | DetermineFigureType(appState, x, y);

    return Figure;
}

void DetermineAnimatedSprite(AppState& appState, int Figure, DrawnObject ** ps)
{
    auto& BlackPawn_sprite = appState.BlackPawn_sprite;
    auto& BlackRook_sprite = appState.BlackRook_sprite;
    auto& BlackKnight_sprite = appState.BlackKnight_sprite;
    auto& BlackBishop_sprite = appState.BlackBishop_sprite;
    auto& BlackQueen_sprite = appState.BlackQueen_sprite;
    auto& BlackKing_sprite = appState.BlackKing_sprite;
    auto& WhitePawn_sprite = appState.WhitePawn_sprite;
    auto& WhiteRook_sprite = appState.WhiteRook_sprite;
    auto& WhiteKnight_sprite = appState.WhiteKnight_sprite;
    auto& WhiteBishop_sprite = appState.WhiteBishop_sprite;
    auto& WhiteQueen_sprite = appState.WhiteQueen_sprite;
    auto& WhiteKing_sprite = appState.WhiteKing_sprite;

    switch(FIGURE(Figure))
    {
        case BLACK_PAWN: *ps = &BlackPawn_sprite; break;
        case BLACK_ROOK: *ps = &BlackRook_sprite; break;
        case BLACK_KNIGHT: *ps = &BlackKnight_sprite; break;
        case BLACK_BISHOP: *ps = &BlackBishop_sprite; break;
        case BLACK_QUEEN: *ps = &BlackQueen_sprite; break;
        case BLACK_KING: *ps = &BlackKing_sprite; break;
        case WHITE_PAWN: *ps = &WhitePawn_sprite; break;
        case WHITE_ROOK: *ps = &WhiteRook_sprite; break;
        case WHITE_KNIGHT: *ps = &WhiteKnight_sprite; break;
        case WHITE_BISHOP: *ps = &WhiteBishop_sprite; break;
        case WHITE_QUEEN: *ps = &WhiteQueen_sprite; break;
        case WHITE_KING: *ps = &WhiteKing_sprite; break;
    }
}

int NumberOfFigures(AppState& appState, int FigureColor, int FigureType)
{
    auto& board = appState.board;
    auto& GroupOfFigures = appState.GroupOfFigures;

    int number_of_figures;
    int i, j, k;
    for (i = k = number_of_figures = 0; i < LENGTH; i++)
    {
        for (j = 0; j < LENGTH; j++)
        {
            if (FIGURE(board[i][j]) == (FigureColor | FigureType))
            {
                GroupOfFigures[k] = {j, i};
                k++;
                number_of_figures++;
            }
        }
    }
    return number_of_figures;
}

void TransformationColorDefinition(AppState& appState, int x, int y)
{
    auto& board = appState.board;
    auto& PawnReachedLastHorizontal = appState.PawnReachedLastHorizontal;
    auto& CurrentWindow = appState.CurrentWindow;
    auto& PawnTransformationColor = appState.PawnTransformationColor;
    auto& DQ = appState.DQ;
    auto& BlackQueenPT_icon = appState.BlackQueenPT_icon;
    auto& DB = appState.DB;
    auto& BlackBishopPT_icon = appState.BlackBishopPT_icon;
    auto& DK = appState.DK;
    auto& BlackKnightPT_icon = appState.BlackKnightPT_icon;
    auto& DR = appState.DR;
    auto& BlackRookPT_icon = appState.BlackRookPT_icon;
    auto& WhiteQueenPT_icon = appState.WhiteQueenPT_icon;
    auto& WhiteBishopPT_icon = appState.WhiteBishopPT_icon;
    auto& WhiteKnightPT_icon = appState.WhiteKnightPT_icon;
    auto& WhiteRookPT_icon = appState.WhiteRookPT_icon;

    int PawnColor = FIGURE_COLOR(board[y][x]) == BLACK ? BLACK : WHITE;

    if (HasPawnReachedLastHorizontal(appState, x, y))
    {
        PawnReachedLastHorizontal = true;
        CurrentWindow = PawnTransformationWindow;
        ChangeButtonsAvailability(appState, ChessGameScreen, false);
        switch (PawnColor)
        {
            case BLACK:
                PawnTransformationColor = BLACK;
                DQ = &BlackQueenPT_icon;
                DB = &BlackBishopPT_icon;
                DK = &BlackKnightPT_icon;
                DR = &BlackRookPT_icon;
                break;
            case WHITE:
                PawnTransformationColor = WHITE;
                DQ = &WhiteQueenPT_icon;
                DB = &WhiteBishopPT_icon;
                DK = &WhiteKnightPT_icon;
                DR = &WhiteRookPT_icon;
                break;
        }
    }
}

void CreationOfObjects(AppState& appState)   //Creating Window, Loading Textures, Setting Textures To Sprites
{
    auto& window = appState.window;
    auto& InitialWindowSize = appState.InitialWindowSize;
    auto& CurrentScreen = appState.CurrentScreen;

    window.create(VideoMode({InitialWindowSize.x, InitialWindowSize.y}), "Chess");
    CurrentScreen = MainMenuScreen;

    CreateChessPieces(appState);
    CreateSmallChessPieces(appState);
    CreateBacklight(appState);
    CreateChessboards(appState);
    CreateScreensAndWindows(appState);
}

void CreateChessPieces(AppState& appState)
{
    auto& ChessPieces_texture = appState.ChessPieces_texture;
    auto& BlackPawn_sprite = appState.BlackPawn_sprite;
    auto& BlackRook_sprite = appState.BlackRook_sprite;
    auto& BlackKnight_sprite = appState.BlackKnight_sprite;
    auto& BlackBishop_sprite = appState.BlackBishop_sprite;
    auto& BlackQueen_sprite = appState.BlackQueen_sprite;
    auto& BlackKing_sprite = appState.BlackKing_sprite;
    auto& WhitePawn_sprite = appState.WhitePawn_sprite;
    auto& WhiteRook_sprite = appState.WhiteRook_sprite;
    auto& WhiteKnight_sprite = appState.WhiteKnight_sprite;
    auto& WhiteBishop_sprite = appState.WhiteBishop_sprite;
    auto& WhiteQueen_sprite = appState.WhiteQueen_sprite;
    auto& WhiteKing_sprite = appState.WhiteKing_sprite;

    IntRect BP, BR, BKn, BB, BQ, BKi, WP, WR, WKn, WB, WQ, WKi;

    BP = {{400, 0}, {80, 80}};
    BR = {{320, 0}, {80, 80}};
    BKn = {{240, 0}, {80, 80}};
    BB = {{160, 0}, {80, 80}};
    BQ = {{80, 0}, {80, 80}};
    BKi = {{0, 0}, {80, 80}};
    WP = {{400, 80}, {80, 80}};
    WR = {{320, 80}, {80, 80}};
    WKn = {{240, 80}, {80, 80}};
    WB = {{160, 80}, {80, 80}};
    WQ = {{80, 80}, {80, 80}};
    WKi = {{0, 80}, {80, 80}};

    auto FILE_PATH = "Images/Chess pieces.png";
    if (!ChessPieces_texture.loadFromFile(FILE_PATH))
    {
        PrintErrorAboutLoadingTexture(FILE_PATH);
    }

    BlackPawn_sprite.Create(ChessPieces_texture, BP);
    BlackRook_sprite.Create(ChessPieces_texture, BR);
    BlackKnight_sprite.Create(ChessPieces_texture, BKn);
    BlackBishop_sprite.Create(ChessPieces_texture, BB);
    BlackQueen_sprite.Create(ChessPieces_texture, BQ);
    BlackKing_sprite.Create(ChessPieces_texture, BKi);
    WhitePawn_sprite.Create(ChessPieces_texture, WP);
    WhiteRook_sprite.Create(ChessPieces_texture, WR);
    WhiteKnight_sprite.Create(ChessPieces_texture, WKn);
    WhiteBishop_sprite.Create(ChessPieces_texture, WB);
    WhiteQueen_sprite.Create(ChessPieces_texture, WQ);
    WhiteKing_sprite.Create(ChessPieces_texture, WKi);
}

void CreateSmallChessPieces(AppState& appState)
{
    auto& SmallChessPieces_texture = appState.SmallChessPieces_texture;
    auto& SmallBlackPawn_sprite = appState.SmallBlackPawn_sprite;
    auto& SmallBlackRook_sprite = appState.SmallBlackRook_sprite;
    auto& SmallBlackKnight_sprite = appState.SmallBlackKnight_sprite;
    auto& SmallBlackBishop_sprite = appState.SmallBlackBishop_sprite;
    auto& SmallBlackQueen_sprite = appState.SmallBlackQueen_sprite;
    auto& SmallBlackKing_sprite = appState.SmallBlackKing_sprite;
    auto& SmallWhitePawn_sprite = appState.SmallWhitePawn_sprite;
    auto& SmallWhiteRook_sprite = appState.SmallWhiteRook_sprite;
    auto& SmallWhiteKnight_sprite = appState.SmallWhiteKnight_sprite;
    auto& SmallWhiteBishop_sprite = appState.SmallWhiteBishop_sprite;
    auto& SmallWhiteQueen_sprite = appState.SmallWhiteQueen_sprite;
    auto& SmallWhiteKing_sprite = appState.SmallWhiteKing_sprite;

    IntRect SBP, SBR, SBKn, SBB, SBQ, SBKi, SWP, SWR, SWKn, SWB, SWQ, SWKi;

    SBP = {{250, 0}, {50, 50}};
    SBR = {{200, 0}, {50, 50}};
    SBKn = {{150, 0}, {50, 50}};
    SBB = {{100, 0}, {50, 50}};
    SBQ = {{50, 0}, {50, 50}};
    SBKi = {{0, 0}, {50, 50}};
    SWP = {{250, 50}, {50, 50}};
    SWR = {{200, 50}, {50, 50}};
    SWKn = {{150, 50}, {50, 50}};
    SWB = {{100, 50}, {50, 50}};
    SWQ = {{50, 50}, {50, 50}};
    SWKi = {{0, 50}, {50, 50}};

    auto FILE_PATH = "Images/Small chess pieces.png";
    if (!SmallChessPieces_texture.loadFromFile(FILE_PATH))
    {
        PrintErrorAboutLoadingTexture(FILE_PATH);
    }

    SmallBlackPawn_sprite.Create(SmallChessPieces_texture, SBP);
    SmallBlackRook_sprite.Create(SmallChessPieces_texture, SBR);
    SmallBlackKnight_sprite.Create(SmallChessPieces_texture, SBKn);
    SmallBlackBishop_sprite.Create(SmallChessPieces_texture, SBB);
    SmallBlackQueen_sprite.Create(SmallChessPieces_texture, SBQ);
    SmallBlackKing_sprite.Create(SmallChessPieces_texture, SBKi);
    SmallWhitePawn_sprite.Create(SmallChessPieces_texture, SWP);
    SmallWhiteRook_sprite.Create(SmallChessPieces_texture, SWR);
    SmallWhiteKnight_sprite.Create(SmallChessPieces_texture, SWKn);
    SmallWhiteBishop_sprite.Create(SmallChessPieces_texture, SWB);
    SmallWhiteQueen_sprite.Create(SmallChessPieces_texture, SWQ);
    SmallWhiteKing_sprite.Create(SmallChessPieces_texture, SWKi);
}

void CreateBacklight(AppState& appState)
{
    auto& Backlight_texture = appState.Backlight_texture;
    auto& DarkCircle_sprite = appState.DarkCircle_sprite;
    auto& LightCircle_sprite = appState.LightCircle_sprite;
    auto& GreenSquare_sprite = appState.GreenSquare_sprite;
    auto& YellowSquare_sprite = appState.YellowSquare_sprite;
    auto& RedSquare_sprite = appState.RedSquare_sprite;

    IntRect DC, LC, GS, YS, RS;

    DC = {{0, 0}, {80, 80}};
    LC = {{80, 0}, {80, 80}};
    GS = {{0, 80}, {80, 80}};
    YS = {{80, 80}, {80, 80}};
    RS = {{160, 80}, {80, 80}};

    auto FILE_PATH = "Images/Backlight.png";
    if (!Backlight_texture.loadFromFile(FILE_PATH))
    {
        PrintErrorAboutLoadingTexture(FILE_PATH);
    }

    DarkCircle_sprite.Create(Backlight_texture, DC);
    LightCircle_sprite.Create(Backlight_texture, LC);
    GreenSquare_sprite.Create(Backlight_texture, GS);
    YellowSquare_sprite.Create(Backlight_texture, YS);
    RedSquare_sprite.Create(Backlight_texture, RS);
}

void CreateChessboards(AppState& appState)
{
    auto& Chessboards_texture = appState.Chessboards_texture;
    auto& OrdinaryChessboard_sprite = appState.OrdinaryChessboard_sprite;
    auto& InvertedChessboard_sprite = appState.InvertedChessboard_sprite;

    IntRect OC, IC;

    OC = {{0, 0}, {800, 800}};
    IC = {{800, 0}, {800, 800}};

    auto FILE_PATH = "Images/Chessboards.png";
    if (!Chessboards_texture.loadFromFile(FILE_PATH))
    {
        PrintErrorAboutLoadingTexture(FILE_PATH);
    }

    OrdinaryChessboard_sprite.Create(Chessboards_texture, OC);
    InvertedChessboard_sprite.Create(Chessboards_texture, IC);
}

void CreateScreensAndWindows(AppState& appState)
{
    auto& Backgrounds_texture = appState.Backgrounds_texture;
    auto& Windows_texture = appState.Windows_texture;
    auto& MainMenuScreen_guiElements_texture = appState.MainMenuScreen_guiElements_texture;
    auto& ChessGameScreen_guiElements_texture = appState.ChessGameScreen_guiElements_texture;
    auto& PawnTransformationWindow_guiElements_texture = appState.PawnTransformationWindow_guiElements_texture;
    auto& GameOverWindow_guiElements_texture = appState.GameOverWindow_guiElements_texture;
    auto& GamePauseWindow_guiElements_texture = appState.GamePauseWindow_guiElements_texture;
    auto& OptionsWindow_guiElements_texture = appState.OptionsWindow_guiElements_texture;
    auto& GameSaveWindow_guiElements_texture = appState.GameSaveWindow_guiElements_texture;
    auto& BackgroundDimmer_texture = appState.BackgroundDimmer_texture;
    auto& BackgroundDimmer = appState.BackgroundDimmer;

    auto FILE_PATH = "Images/Backgrounds.jpg";
    if (!Backgrounds_texture.loadFromFile(FILE_PATH))
    {
        PrintErrorAboutLoadingTexture(FILE_PATH);
    }

    FILE_PATH = "Images/Windows.png";
    if (!Windows_texture.loadFromFile(FILE_PATH))
    {
        PrintErrorAboutLoadingTexture(FILE_PATH);
    }

    FILE_PATH = "Images/MainMenuScreen_guiElements.png";
    if (!MainMenuScreen_guiElements_texture.loadFromFile(FILE_PATH))
    {
        PrintErrorAboutLoadingTexture(FILE_PATH);
    }

    FILE_PATH = "Images/ChessGameScreen_guiElements.png";
    if (!ChessGameScreen_guiElements_texture.loadFromFile(FILE_PATH))
    {
        PrintErrorAboutLoadingTexture(FILE_PATH);
    }

    FILE_PATH = "Images/PawnTransformationWindow_guiElements.png";
    if (!PawnTransformationWindow_guiElements_texture.loadFromFile(FILE_PATH))
    {
        PrintErrorAboutLoadingTexture(FILE_PATH);
    }

    FILE_PATH = "Images/GameOverWindow_guiElements.png";
    if (!GameOverWindow_guiElements_texture.loadFromFile(FILE_PATH))
    {
        PrintErrorAboutLoadingTexture(FILE_PATH);
    }

    FILE_PATH = "Images/GamePauseWindow_guiElements.png";
    if (!GamePauseWindow_guiElements_texture.loadFromFile(FILE_PATH))
    {
        PrintErrorAboutLoadingTexture(FILE_PATH);
    }

    FILE_PATH = "Images/OptionsWindow_guiElements.png";
    if (!OptionsWindow_guiElements_texture.loadFromFile(FILE_PATH))
    {
        PrintErrorAboutLoadingTexture(FILE_PATH);
    }

    FILE_PATH = "Images/GameSaveWindow_guiElements.png";
    if (!GameSaveWindow_guiElements_texture.loadFromFile(FILE_PATH))
    {
        PrintErrorAboutLoadingTexture(FILE_PATH);
    }

    FILE_PATH = "Images/Background dimmer.png";
    if (!BackgroundDimmer_texture.loadFromFile(FILE_PATH))
    {
        PrintErrorAboutLoadingTexture(FILE_PATH);
    }

    CreateMainMenuScreen(appState);
    CreateChessGameScreen(appState);
    CreatePawnTransformationWindow(appState);
    CreateOptionsWindow(appState);
    CreateGameOverWindow(appState);
    CreateGameSaveWindow(appState);
    CreateGamePauseWindow(appState);
    BackgroundDimmer.Create(BackgroundDimmer_texture, {{0, 0}, {1274, 800}});
}

void CreateMainMenuScreen(AppState& appState)
{
    auto& InitialWindowSize = appState.InitialWindowSize;
    auto& MainMenu_background = appState.MainMenu_background;
    auto& Backgrounds_texture = appState.Backgrounds_texture;
    auto& NewGame_button = appState.NewGame_button;
    auto& MainMenuScreen_guiElements_texture = appState.MainMenuScreen_guiElements_texture;
    auto& Options_button = appState.Options_button;
    auto& ExitFromApp_button = appState.ExitFromApp_button;
    auto& BackToGameMM_button = appState.BackToGameMM_button;
    auto& GamePauseWindow_guiElements_texture = appState.GamePauseWindow_guiElements_texture;

    Vector2u NGs, Os, EFAs, BTGmms;
    Vector2f NGp, Op, EFAp,BTGmmp;
    IntRect NGr1, Or1, EFAr1, PGr1, NGr2, Or2, EFAr2, MMSBr, BTGmmr1, BTGmmr2;

    NGs = {368, 84};
    Os = {226, 78};
    EFAs = {244, 78};
    BTGmms = {544, 66};

    Op = {static_cast<float>(InitialWindowSize.x / 2 - Os.x / 2), static_cast<float>(InitialWindowSize.y / 2 - Os.y / 2)};
    NGp = {static_cast<float>(InitialWindowSize.x / 2 - NGs.x / 2), static_cast<float>(Op.y - NGs.y - 20)};
    EFAp = {static_cast<float>(InitialWindowSize.x / 2 - EFAs.x / 2), static_cast<float>(Op.y + EFAs.y + 20)};
    BTGmmp = {static_cast<float>(InitialWindowSize.x / 2 - BTGmms.x / 2), static_cast<float>(NGp.y - BTGmms.y - 20)};

    NGr1 = {{0, 0}, {368, 84}};
    NGr2 = {{0, 84}, {368, 84}};
    Or1 = {{0, 168}, {226, 78}};
    Or2 = {{0, 246}, {226, 78}};
    EFAr1 = {{0, 324}, {244, 78}};
    EFAr2 = {{0, 402}, {244, 78}};
    MMSBr = {{0, 0}, {1274, 800}};
    BTGmmr1 = {{0, 0}, {544, 66}};
    BTGmmr2 = {{0, 66}, {544, 66}};

    MainMenu_background.Create(Backgrounds_texture, MMSBr);
    NewGame_button.Create(MainMenuScreen_guiElements_texture, NGr1, NGr2, NGs, NGp);
    Options_button.Create(MainMenuScreen_guiElements_texture, Or1, Or2, Os, Op);
    ExitFromApp_button.Create(MainMenuScreen_guiElements_texture, EFAr1, EFAr2, EFAs, EFAp);
    BackToGameMM_button.Create(GamePauseWindow_guiElements_texture, BTGmmr1, BTGmmr2, BTGmms, BTGmmp);
}

void CreateChessGameScreen(AppState& appState)
{
    auto& InitialWindowSize = appState.InitialWindowSize;
    auto& PauseGame_button = appState.PauseGame_button;
    auto& ChessGameScreen_guiElements_texture = appState.ChessGameScreen_guiElements_texture;
    auto& FlipChessboard_button = appState.FlipChessboard_button;
    auto& BlackMove_label = appState.BlackMove_label;
    auto& WhiteMove_label = appState.WhiteMove_label;
    auto& EatenFigures_label = appState.EatenFigures_label;
    auto& ChessGame_background = appState.ChessGame_background;
    auto& Backgrounds_texture = appState.Backgrounds_texture;

    Vector2u PGs, FCs, BMs, WMs, EFs;
    Vector2f FCp, PGp, BNGp, BMp, WMp, EFp;
    IntRect PGr1, PGr2, FCr1, FCr2, BMr, WMr, EFr, CGSBr;
    int DBCARS = 450;   //Distance Between Chessboard And Right Side
    int CS = 800;   //Chessboard Size

    PGs = FCs = {80, 80};
    BMs = {361, 70};
    WMs = {308, 70};
    EFs = {231, 120};

    PGp = {static_cast<float>(InitialWindowSize.x - PGs.x - 10), 10};
    FCp = {PGp.x - FCs.x - 20, 10};
    BMp = {static_cast<float>((450 / 2 - BMs.x / 2) + CS), static_cast<float>(InitialWindowSize.y / 2 - BMs.y / 2)};
    WMp = {static_cast<float>((450 / 2 - WMs.x / 2) + CS), static_cast<float>(InitialWindowSize.y / 2 - WMs.y / 2)};
    EFp = {static_cast<float>((450 / 2 - EFs.x / 2) + CS), 440};

    PGr1 = {{0, 260}, {80, 80}};
    PGr2 = {{80, 260}, {80, 80}};
    FCr1 = {{160, 260}, {80, 80}};
    FCr2 = {{240, 260}, {80, 80}};
    BMr = {{0, 0}, {380, 70}};
    WMr = {{0, 70}, {380, 70}};
    EFr = {{0, 140}, {300, 120}};
    CGSBr = {{0, 800}, {1274, 800}};

    PauseGame_button.Create(ChessGameScreen_guiElements_texture, PGr1, PGr2, PGs, PGp);
    FlipChessboard_button.Create(ChessGameScreen_guiElements_texture, FCr1, FCr2, FCs, FCp);
    BlackMove_label.Create(ChessGameScreen_guiElements_texture, BMr, BMp);
    WhiteMove_label.Create(ChessGameScreen_guiElements_texture, WMr, WMp);
    EatenFigures_label.Create(ChessGameScreen_guiElements_texture, EFr, EFp);
    ChessGame_background.Create(Backgrounds_texture, CGSBr);
}

void CreatePawnTransformationWindow(AppState& appState)
{
    auto& InitialWindowSize = appState.InitialWindowSize;
    auto& PawnTransformation_window = appState.PawnTransformation_window;
    auto& Windows_texture = appState.Windows_texture;
    auto& BlackQueenPT_icon = appState.BlackQueenPT_icon;
    auto& PawnTransformationWindow_guiElements_texture = appState.PawnTransformationWindow_guiElements_texture;
    auto& BlackBishopPT_icon = appState.BlackBishopPT_icon;
    auto& BlackKnightPT_icon = appState.BlackKnightPT_icon;
    auto& BlackRookPT_icon = appState.BlackRookPT_icon;
    auto& WhiteQueenPT_icon = appState.WhiteQueenPT_icon;
    auto& WhiteBishopPT_icon = appState.WhiteBishopPT_icon;
    auto& WhiteKnightPT_icon = appState.WhiteKnightPT_icon;
    auto& WhiteRookPT_icon = appState.WhiteRookPT_icon;

    Vector2u PTWs, BQs, BBs, BKs, BRs, WQs, WBs, WKs, WRs, PiecesSize;
    Vector2f PTWp, BQp, BBp, BKp, BRp, WQp, WBp, WKp, WRp, StartPosition;
    IntRect PTWr, BQr1, BBr1, BKr1, BRr1, WQr1, WBr1, WKr1, WRr1, BQr2, BBr2, BKr2, BRr2, WQr2, WBr2, WKr2, WRr2;

    PTWs = {832, 332};
    PiecesSize = BQs = BBs = BKs = BRs = WQs = WBs = WKs = WRs = {200, 200};

    PTWp = {static_cast<float>(InitialWindowSize.x / 2 - PTWs.x / 2), static_cast<float>(InitialWindowSize.y / 2 - PTWs.y / 2)};
    StartPosition = {227, 240};
    BQp = {StartPosition.x + 10, StartPosition.y + 110};
    BBp = {StartPosition.x + 210, StartPosition.y + 110};
    BKp = {StartPosition.x + 410, StartPosition.y + 110};
    BRp = {StartPosition.x + 610, StartPosition.y + 110};
    WQp = {StartPosition.x + 10, StartPosition.y + 110};
    WBp = {StartPosition.x + 210, StartPosition.y + 110};
    WKp = {StartPosition.x + 410, StartPosition.y + 110};
    WRp = {StartPosition.x + 610, StartPosition.y + 110};

    PTWr = {{740, 0}, {832, 332}};
    BQr1 = {{0, 0}, {200, 200}};
    BBr1 = {{200, 0}, {200, 200}};
    BKr1 = {{400, 0}, {200, 200}};
    BRr1 = {{600, 0}, {200, 200}};
    WQr1 = {{0, 400}, {200, 200}};
    WBr1 = {{200, 400}, {200, 200}};
    WKr1 = {{400, 400}, {200, 200}};
    WRr1 = {{600, 400}, {200, 200}};
    BQr2 = {{0, 200}, {200, 200}};
    BBr2 = {{200, 200}, {200, 200}};
    BKr2 = {{400, 200}, {200, 200}};
    BRr2 = {{600, 200}, {200, 200}};
    WQr2 = {{0, 600}, {200, 200}};
    WBr2 = {{200, 600}, {200, 200}};
    WKr2 = {{400, 600}, {200, 200}};
    WRr2 = {{600, 600}, {200, 200}};

    PawnTransformation_window.Create(Windows_texture, PTWr, PTWp);
    BlackQueenPT_icon.Create(PawnTransformationWindow_guiElements_texture, BQr1, BQr2, PiecesSize, BQp);
    BlackBishopPT_icon.Create(PawnTransformationWindow_guiElements_texture, BBr1, BBr2, PiecesSize, BBp);
    BlackKnightPT_icon.Create(PawnTransformationWindow_guiElements_texture, BKr1, BKr2, PiecesSize, BKp);
    BlackRookPT_icon.Create(PawnTransformationWindow_guiElements_texture, BRr1, BRr2, PiecesSize, BRp);
    WhiteQueenPT_icon.Create(PawnTransformationWindow_guiElements_texture, WQr1, WQr2, PiecesSize, WQp);
    WhiteBishopPT_icon.Create(PawnTransformationWindow_guiElements_texture, WBr1, WBr2, PiecesSize, WBp);
    WhiteKnightPT_icon.Create(PawnTransformationWindow_guiElements_texture, WKr1, WKr2, PiecesSize, WKp);
    WhiteRookPT_icon.Create(PawnTransformationWindow_guiElements_texture, WRr1, WRr2, PiecesSize, WRp);
}

void CreateOptionsWindow(AppState& appState)
{
    auto& InitialWindowSize = appState.InitialWindowSize;
    auto& Options_window = appState.Options_window;
    auto& Windows_texture = appState.Windows_texture;
    auto& PvE_radioButton = appState.PvE_radioButton;
    auto& OptionsWindow_guiElements_texture = appState.OptionsWindow_guiElements_texture;
    auto& PvP_radioButton = appState.PvP_radioButton;
    auto& White_radioButton = appState.White_radioButton;
    auto& Black_radioButton = appState.Black_radioButton;
    auto& EasyLvl_radioButton = appState.EasyLvl_radioButton;
    auto& MediumLvl_radioButton = appState.MediumLvl_radioButton;
    auto& DifficultLvl_radioButton = appState.DifficultLvl_radioButton;
    auto& ExitFromOptionsWindow_button = appState.ExitFromOptionsWindow_button;
    auto& GameMode_label = appState.GameMode_label;
    auto& PieceColor_label = appState.PieceColor_label;
    auto& LevelOfDifficulty_label = appState.LevelOfDifficulty_label;

    Vector2u OWs, PvEs, PvPs, Ws, Bs, Es, Ms, Ds, EFOWs, GMs, PCs, LODs;
    Vector2f OWp, PvEp, PvPp, Wp, Bp, Ep, Mp, Dp, EFOWp, GMp, PCp, LODp;
    IntRect OWr, PvEr1, PvPr1, Wr1, Br1, Er1, Mr1, Dr1, PvEr2, PvPr2, Wr2, Br2, Er2, Mr2, Dr2, PvEr3, PvPr3, Wr3, Br3, Er3, Mr3, Dr3, EFOWr1, EFOWr2, GSSWYr1, GSSWNr1, GSSWYr2, GSSWNr2, GMr, PCr, LODr;

    OWs = {740, 640};
    PvEs = PvPs = {324, 68};
    Ws = Bs = {200, 75};
    Es = Ms = Ds ={324, 64};
    EFOWs = {80, 60};
    GMs = {487, 64};
    PCs = {366, 62};
    LODs = {626, 62};

    OWp = {static_cast<float>(InitialWindowSize.x / 2 - OWs.x / 2), static_cast<float>(InitialWindowSize.y / 2 - OWs.y / 2)};
    PvEp = {static_cast<float>(InitialWindowSize.x / 2 - PvEs.x - 7), OWp.y + 114};
    PvPp = {static_cast<float>(InitialWindowSize.x / 2 + 7), OWp.y + 114};
    Wp = {static_cast<float>(InitialWindowSize.x / 2 - Ws.x - 7), OWp.y + 266};
    Bp = {static_cast<float>(InitialWindowSize.x / 2 + 7), OWp.y + 266};
    Ep = {static_cast<float>(InitialWindowSize.x / 2 - Es.x - 7), OWp.y + 448};
    Mp = {static_cast<float>(InitialWindowSize.x / 2 + 7), OWp.y + 448};
    Dp = {static_cast<float>(InitialWindowSize.x / 2 - Ds.x / 2), OWp.y + 527};
    EFOWp = {OWp.x + 20, OWp.y + 20};
    GMp = {static_cast<float>(InitialWindowSize.x / 2 - GMs.x / 2), OWp.y + 35};
    PCp = {static_cast<float>(InitialWindowSize.x / 2 - PCs.x / 2), OWp.y + 189};
    LODp = {static_cast<float>(InitialWindowSize.x / 2 - LODs.x / 2), OWp.y + 371};

    OWr = {{0, 0}, {740, 640}};

    PvEr1 = {{0, 188}, {324, 68}};
    PvEr2 = {{0, 256}, {324, 68}};
    PvEr3 = {{0, 324}, {324, 68}};

    PvPr1 = {{324, 188}, {324, 68}};
    PvPr2 = {{324, 256}, {324, 68}};
    PvPr3 = {{324, 324}, {324, 68}};

    Wr1 = {{0, 392}, {200, 75}};
    Wr2 = {{0, 467}, {200, 75}};
    Wr3 = {{0, 542}, {200, 75}};

    Br1 = {{200, 392}, {200, 75}};
    Br2 = {{200, 467}, {200, 75}};
    Br3 = {{200, 542}, {200, 75}};

    Er1 = {{0, 617}, {324, 64}};
    Er2 = {{0, 681}, {324, 64}};
    Er3 = {{0, 745}, {324, 64}};

    Mr1 = {{324, 617}, {324, 64}};
    Mr2 = {{324, 681}, {324, 64}};
    Mr3 = {{324, 745}, {324, 64}};

    Dr1 = {{0, 809}, {324, 64}};
    Dr2 = {{324, 809}, {324, 64}};
    Dr3 = {{0, 873}, {324, 64}};

    EFOWr1 = {{366, 64}, {80, 60}};
    EFOWr2 = {{446, 64}, {80, 60}};
    GMr = {{0, 0}, {487, 64}};
    PCr = {{0, 64}, {366, 62}};
    LODr = {{0, 126}, {626, 62}};

    Options_window.Create(Windows_texture, OWr, OWp);
    PvE_radioButton.Create(OptionsWindow_guiElements_texture, PvEr1, PvEr2, PvEr3, PvEs, PvEp, false, NULL, &PvP_radioButton);
    PvP_radioButton.Create(OptionsWindow_guiElements_texture, PvPr1, PvPr2, PvPr3, PvPs, PvPp, false, &PvE_radioButton, NULL);
    White_radioButton.Create(OptionsWindow_guiElements_texture, Wr1, Wr2, Wr3, Ws, Wp, false, NULL, &Black_radioButton);
    Black_radioButton.Create(OptionsWindow_guiElements_texture, Br1, Br2, Br3, Bs, Bp, false, &White_radioButton, NULL);
    EasyLvl_radioButton.Create(OptionsWindow_guiElements_texture, Er1, Er2, Er3, Es, Ep, false, NULL, &MediumLvl_radioButton);
    MediumLvl_radioButton.Create(OptionsWindow_guiElements_texture, Mr1, Mr2, Mr3, Ms, Mp, false, &EasyLvl_radioButton, &DifficultLvl_radioButton);
    DifficultLvl_radioButton.Create(OptionsWindow_guiElements_texture, Dr1, Dr2, Dr3, Ds, Dp, false, &MediumLvl_radioButton, NULL);
    ExitFromOptionsWindow_button.Create(OptionsWindow_guiElements_texture, EFOWr1, EFOWr2, EFOWs, EFOWp);
    GameMode_label.Create(OptionsWindow_guiElements_texture, GMr, GMp);
    PieceColor_label.Create(OptionsWindow_guiElements_texture, PCr, PCp);
    LevelOfDifficulty_label.Create(OptionsWindow_guiElements_texture, LODr, LODp);
}

void CreateGameOverWindow(AppState& appState)
{
    auto& InitialWindowSize = appState.InitialWindowSize;
    auto& GameOver_window = appState.GameOver_window;
    auto& Windows_texture = appState.Windows_texture;
    auto& BeginNewGame_button = appState.BeginNewGame_button;
    auto& GameOverWindow_guiElements_texture = appState.GameOverWindow_guiElements_texture;
    auto& GoToMenu_button = appState.GoToMenu_button;
    auto& Mat_label = appState.Mat_label;
    auto& Pat_label = appState.Pat_label;
    auto& BlackWin_label = appState.BlackWin_label;
    auto& WhiteWin_label = appState.WhiteWin_label;
    auto& Standoff_label = appState.Standoff_label;

    Vector2u GOWs, BNGs, GTMs, Ms, Ps, BWs, WWs, Ss;
    Vector2f GOWp, BNGp, GTMp,Mp, Pp, BWp, WWp, Sp;
    IntRect GOWr, BNGr1, GTMr1, BNGr2, GTMr2, Mr, Pr, BWr, WWr, Sr;

    GOWs = {680, 460};
    BNGs = {522, 70};
    GTMs = {560, 68};
    Ms = Ps = {170, 74};
    BWs = WWs = Ss = {420, 166};

    GOWp = {static_cast<float>(InitialWindowSize.x / 2 - GOWs.x / 2), static_cast<float>(InitialWindowSize.y / 2 - GOWs.y / 2)};
    BNGp = {GOWs.x / 2 - BNGs.x / 2 + GOWp.x, GOWp.y + 278};
    GTMp = {GOWs.x / 2 - GTMs.x / 2 + GOWp.x, GOWp.y + 365};
    Mp = {GOWs.x / 2 - Ms.x / 2 + GOWp.x, GOWp.y + 20};
    Pp = {GOWs.x / 2 - Ps.x / 2 + GOWp.x, GOWp.y + 20};
    BWp = {GOWs.x / 2 - BWs.x / 2 + GOWp.x, GOWp.y + 90};
    WWp = {GOWs.x / 2 - WWs.x / 2 + GOWp.x, GOWp.y + 90};
    Sp = {GOWs.x / 2 - Ss.x / 2 + GOWp.x, GOWp.y + 90};

    GOWr = {{0, 640}, {680, 460}};
    BNGr1 = {{0, 572}, {522, 70}};
    BNGr2 = {{0, 642}, {522, 70}};
    GTMr1 = {{0, 712}, {560, 68}};
    GTMr2 = {{0, 780}, {560, 68}};
    Mr = {{0, 0}, {170, 74}};
    Pr = {{170, 0}, {170, 74}};
    BWr = {{0, 74}, {420, 166}};
    WWr = {{0, 240}, {420, 166}};
    Sr = {{0, 406}, {420, 166}};

    GameOver_window.Create(Windows_texture, GOWr, GOWp);
    BeginNewGame_button.Create(GameOverWindow_guiElements_texture, BNGr1, BNGr2, BNGs, BNGp);
    GoToMenu_button.Create(GameOverWindow_guiElements_texture, GTMr1, GTMr2, GTMs, GTMp);
    Mat_label.Create(GameOverWindow_guiElements_texture, Mr, Mp);
    Pat_label.Create(GameOverWindow_guiElements_texture, Pr, Pp);
    BlackWin_label.Create(GameOverWindow_guiElements_texture, BWr, BWp);
    WhiteWin_label.Create(GameOverWindow_guiElements_texture, WWr, WWp);
    Standoff_label.Create(GameOverWindow_guiElements_texture, Sr, Sp);
}

void CreateGameSaveWindow(AppState& appState)
{
    auto& InitialWindowSize = appState.InitialWindowSize;
    auto& GameSave_window = appState.GameSave_window;
    auto& Windows_texture = appState.Windows_texture;
    auto& WouldYouLikeToSaveGame_label = appState.WouldYouLikeToSaveGame_label;
    auto& GameSaveWindow_guiElements_texture = appState.GameSaveWindow_guiElements_texture;
    auto& GSWYes_button = appState.GSWYes_button;
    auto& GSWNo_button = appState.GSWNo_button;

    Vector2u GSWs, WYLTSGs, GSWYs, GSWNs;
    Vector2f GSWp, WYLTSGp, GSWYp, GSWNp;
    IntRect GSWr, WYLTSGr, GSWYr1, GSWNr1, GSWYr2, GSWNr2;

    GSWs = {620, 300};
    WYLTSGs = {548, 112};
    GSWYs = {146, 68};
    GSWNs = {84, 66};

    GSWp = {static_cast<float>(InitialWindowSize.x / 2 - GSWs.x / 2), static_cast<float>(InitialWindowSize.y / 2 - GSWs.y / 2)};
    WYLTSGp = {static_cast<float>(InitialWindowSize.x / 2 - WYLTSGs.x / 2), GSWp.y + 40};
    GSWYp = {((GSWp.x + InitialWindowSize.x / 2) / 2) - GSWYs.x / 2 + 30, GSWp.y + 182};
    GSWNp = {((GSWp.x + GSWs.x + InitialWindowSize.x / 2) / 2) - GSWNs.x / 2 - 30, GSWp.y + 183};

    GSWr = {{740, 332}, {620, 300}};
    WYLTSGr = {{0, 0}, {548, 112}};
    GSWYr1 = {{0, 112}, {146, 68}};
    GSWYr2 = {{146, 112}, {146, 68}};
    GSWNr1 = {{292, 112}, {84, 66}};
    GSWNr2 = {{376, 112}, {84, 66}};

    GameSave_window.Create(Windows_texture, GSWr, GSWp);
    WouldYouLikeToSaveGame_label.Create(GameSaveWindow_guiElements_texture, WYLTSGr, WYLTSGp);
    GSWYes_button.Create(GameSaveWindow_guiElements_texture, GSWYr1, GSWYr2, GSWYs, GSWYp);
    GSWNo_button.Create(GameSaveWindow_guiElements_texture, GSWNr1, GSWNr2, GSWNs, GSWNp);
}

void CreateGamePauseWindow(AppState& appState)
{
    auto& InitialWindowSize = appState.InitialWindowSize;
    auto& GamePause_window = appState.GamePause_window;
    auto& Windows_texture = appState.Windows_texture;
    auto& BackToGame_button = appState.BackToGame_button;
    auto& GamePauseWindow_guiElements_texture = appState.GamePauseWindow_guiElements_texture;
    auto& SaveGame_button = appState.SaveGame_button;
    auto& ExitFromChessGame_button = appState.ExitFromChessGame_button;

    Vector2u GPWs, BTGs, SGs, EFCGs;
    Vector2f GPWp, BTGp, SGp, EFCGp;
    IntRect GPWr, BTGr1, SGr1, BTGr2, SGr2, EFCGr1, EFCGr2;

    GPWs = {670, 340};
    BTGs = {544, 66};
    SGs = {422, 66};
    EFCGs = {194, 54};

    GPWp = {static_cast<float>(InitialWindowSize.x / 2 - GPWs.x / 2), static_cast<float>(InitialWindowSize.y / 2 - GPWs.y / 2)};
    BTGp = {GPWs.x / 2 - BTGs.x / 2 + GPWp.x, GPWp.y + 57};
    SGp = {GPWs.x / 2 - SGs.x / 2 + GPWp.x, GPWp.y + 143};
    EFCGp = {GPWs.x / 2 - EFCGs.x / 2 + GPWp.x, GPWp.y + 229};

    GPWr = {{0, 1100}, {670, 340}};
    BTGr1 = {{0, 0}, {544, 66}};
    BTGr2 = {{0, 66}, {544, 66}};
    SGr1 = {{0, 132}, {422, 66}};
    SGr2 = {{0, 198}, {422, 66}};
    EFCGr1 = {{0, 264}, {194, 54}};
    EFCGr2 = {{0, 318}, {194, 54}};

    GamePause_window.Create(Windows_texture, GPWr, GPWp);
    BackToGame_button.Create(GamePauseWindow_guiElements_texture, BTGr1, BTGr2, BTGs, BTGp);
    SaveGame_button.Create(GamePauseWindow_guiElements_texture, SGr1, SGr2, SGs, SGp);
    ExitFromChessGame_button.Create(GamePauseWindow_guiElements_texture, EFCGr1, EFCGr2, EFCGs, EFCGp);
}

void ChangeButtonPropertiesByCoefficient(AppState& appState, Vector2f coeff)
{
    auto& NewGame_button = appState.NewGame_button;
    auto& Options_button = appState.Options_button;
    auto& ExitFromApp_button = appState.ExitFromApp_button;
    auto& BackToGameMM_button = appState.BackToGameMM_button;
    auto& PauseGame_button = appState.PauseGame_button;
    auto& BlackQueenPT_icon = appState.BlackQueenPT_icon;
    auto& BlackBishopPT_icon = appState.BlackBishopPT_icon;
    auto& BlackKnightPT_icon = appState.BlackKnightPT_icon;
    auto& BlackRookPT_icon = appState.BlackRookPT_icon;
    auto& WhiteQueenPT_icon = appState.WhiteQueenPT_icon;
    auto& WhiteBishopPT_icon = appState.WhiteBishopPT_icon;
    auto& WhiteKnightPT_icon = appState.WhiteKnightPT_icon;
    auto& WhiteRookPT_icon = appState.WhiteRookPT_icon;
    auto& BeginNewGame_button = appState.BeginNewGame_button;
    auto& GoToMenu_button = appState.GoToMenu_button;
    auto& BackToGame_button = appState.BackToGame_button;
    auto& SaveGame_button = appState.SaveGame_button;
    auto& ExitFromChessGame_button = appState.ExitFromChessGame_button;
    auto& PvE_radioButton = appState.PvE_radioButton;
    auto& PvP_radioButton = appState.PvP_radioButton;
    auto& White_radioButton = appState.White_radioButton;
    auto& Black_radioButton = appState.Black_radioButton;
    auto& EasyLvl_radioButton = appState.EasyLvl_radioButton;
    auto& MediumLvl_radioButton = appState.MediumLvl_radioButton;
    auto& DifficultLvl_radioButton = appState.DifficultLvl_radioButton;
    auto& ExitFromOptionsWindow_button = appState.ExitFromOptionsWindow_button;
    auto& GSWYes_button = appState.GSWYes_button;
    auto& GSWNo_button = appState.GSWNo_button;

    NewGame_button.ChangePropertiesByCoefficient(coeff);
    Options_button.ChangePropertiesByCoefficient(coeff);
    ExitFromApp_button.ChangePropertiesByCoefficient(coeff);
    BackToGameMM_button.ChangePropertiesByCoefficient(coeff);
    PauseGame_button.ChangePropertiesByCoefficient(coeff);
    BlackQueenPT_icon.ChangePropertiesByCoefficient(coeff);
    BlackBishopPT_icon.ChangePropertiesByCoefficient(coeff);
    BlackKnightPT_icon.ChangePropertiesByCoefficient(coeff);
    BlackRookPT_icon.ChangePropertiesByCoefficient(coeff);
    WhiteQueenPT_icon.ChangePropertiesByCoefficient(coeff);
    WhiteBishopPT_icon.ChangePropertiesByCoefficient(coeff);
    WhiteKnightPT_icon.ChangePropertiesByCoefficient(coeff);
    WhiteRookPT_icon.ChangePropertiesByCoefficient(coeff);
    BeginNewGame_button.ChangePropertiesByCoefficient(coeff);
    GoToMenu_button.ChangePropertiesByCoefficient(coeff);
    BackToGame_button.ChangePropertiesByCoefficient(coeff);
    SaveGame_button.ChangePropertiesByCoefficient(coeff);
    ExitFromChessGame_button.ChangePropertiesByCoefficient(coeff);
    PvE_radioButton.ChangePropertiesByCoefficient(coeff);
    PvP_radioButton.ChangePropertiesByCoefficient(coeff);
    White_radioButton.ChangePropertiesByCoefficient(coeff);
    Black_radioButton.ChangePropertiesByCoefficient(coeff);
    EasyLvl_radioButton.ChangePropertiesByCoefficient(coeff);
    MediumLvl_radioButton.ChangePropertiesByCoefficient(coeff);
    DifficultLvl_radioButton.ChangePropertiesByCoefficient(coeff);
    ExitFromOptionsWindow_button.ChangePropertiesByCoefficient(coeff);
    GSWYes_button.ChangePropertiesByCoefficient(coeff);
    GSWNo_button.ChangePropertiesByCoefficient(coeff);
}

void AdditionalActionsBeforeMovingFigure(AppState& appState, int ox, int oy, int nx, int ny)
{
    auto& FigureByOldCoordinates = appState.FigureByOldCoordinates;
    auto& board = appState.board;
    auto& FigureByNewCoordinates = appState.FigureByNewCoordinates;

    FigureByOldCoordinates = board[oy][ox];
    FigureByNewCoordinates = board[ny][nx];
}

void AdditionalActionsAfterMovingFigure(AppState& appState, int ox, int oy, int nx, int ny, bool IsMoveMade)
{
    auto& IsTakingOnAisleUsed = appState.IsTakingOnAisleUsed;
    auto& board = appState.board;
    auto& pNC = appState.pNC;
    auto& PawnReachedLastHorizontal = appState.PawnReachedLastHorizontal;
    auto& CurrentGameMode = appState.CurrentGameMode;
    auto& PlayerMove = appState.PlayerMove;
    auto& CurrentChessNote = appState.CurrentChessNote;
    auto& HaveThereBeenChangesSinceTheLastSave = appState.HaveThereBeenChangesSinceTheLastSave;
    auto& FigureByOldCoordinates = appState.FigureByOldCoordinates;
    auto& FigureByNewCoordinates = appState.FigureByNewCoordinates;
    auto& WhoseMove = appState.WhoseMove;

    int EatenFigure;
    string current_chess_move;
    Vector2i o, n;

    if (IsMoveMade)
    {
        FigureMovementAnimation(appState, ox, oy, nx, ny);
        current_chess_move = toChessNote(appState, Vector2i(ox, oy));
        current_chess_move += toChessNote(appState, Vector2i(nx, ny));
        RecordChessMove(appState, current_chess_move);

        if (EatenFigure = HasFigureBeenEaten(appState))
            AddFigureToEatenFigures(appState, EatenFigure);

        if (IsTakingOnAisleUsed)
        {
            board[oy][nx] = 0;
            IsTakingOnAisleUsed = false;
        }

        pNC = {nx, ny};

        if (PawnReachedLastHorizontal && CurrentGameMode == PlayerVersusEnvironment && WhoseMove == PlayerMove)
        {
            EnvironmentPawnTransformation(appState, CurrentChessNote, nx, ny);
            RewriteChessNotation(appState);
        }

        HaveThereBeenChangesSinceTheLastSave = false;

        o = toCoord(appState, current_chess_move[0], current_chess_move[1]);
        n = toCoord(appState, current_chess_move[2], current_chess_move[3]);
        printf("Шахова нотація: %s.\n", current_chess_move.c_str());
        printf("Координатна нотація: з (%d; %d) на (%d; %d).\n", o.x, o.y , n.x, n.y);
    }
    else
    {
        FigureByOldCoordinates = 0;
        FigureByNewCoordinates = 0;
    }

    if ((FIGURE_COLOR(board[ny][nx]) == BLACK && WhoseMove) || (FIGURE_COLOR(board[ny][nx]) == WHITE && !WhoseMove))
        FigureSelection(appState, nx, ny);
}

std::string RewriteChessNotation(AppState& appState)
{
    auto& board = appState.board;
    auto& pNC = appState.pNC;
    auto& AllMovesInGame = appState.AllMovesInGame;

    string figure_letter = "";

    switch (FIGURE_TYPE(board[pNC.y][pNC.x]))
    {
        case ROOK : figure_letter = "r"; break;
        case KNIGHT : figure_letter = "n"; break;
        case BISHOP : figure_letter = "b"; break;
        case QUEEN : figure_letter = "q"; break;
    }

    AllMovesInGame += figure_letter;

    return figure_letter;
}

void EnvironmentPawnTransformation(AppState& appState, std::string current_move, int x, int y)
{
    auto& board = appState.board;
    auto& EnvironmentColor = appState.EnvironmentColor;
    auto& PawnReachedLastHorizontal = appState.PawnReachedLastHorizontal;
    auto& CurrentWindow = appState.CurrentWindow;

    char figure_letter = current_move[4];

    switch (figure_letter)
    {
        case 'r' : board[y][x] = (EnvironmentColor | ROOK); break;
        case 'n' : board[y][x] = (EnvironmentColor | KNIGHT); break;
        case 'b' : board[y][x] = (EnvironmentColor | BISHOP); break;
        case 'q' : board[y][x] = (EnvironmentColor | QUEEN); break;
    }

    PawnReachedLastHorizontal = false;
    CurrentWindow = MissingWindow;
    ChangeButtonsAvailability(appState, ChessGameScreen, true);
}

int HasFigureBeenEaten(AppState& appState)
{
    auto& FigureByNewCoordinates = appState.FigureByNewCoordinates;
    auto& IsTakingOnAisleUsed = appState.IsTakingOnAisleUsed;
    auto& board = appState.board;
    auto& PawnOnAisleCoordinates = appState.PawnOnAisleCoordinates;

    int EatenFigure = 0;

    if (FigureByNewCoordinates > 0)
        EatenFigure = FigureByNewCoordinates;
    else if (FigureByNewCoordinates == 0 && IsTakingOnAisleUsed)
        EatenFigure = board[PawnOnAisleCoordinates.y][PawnOnAisleCoordinates.x];

    return EatenFigure;
}

void AddFigureToEatenFigures(AppState& appState, int EatenFigure)
{
    auto& EatenFigures = appState.EatenFigures;

    switch(FIGURE(EatenFigure))
    {
        case BLACK_PAWN : EatenFigures[0]++; break;
        case BLACK_ROOK : EatenFigures[1]++; break;
        case BLACK_KNIGHT : EatenFigures[2]++; break;
        case BLACK_BISHOP : EatenFigures[3]++; break;
        case BLACK_QUEEN : EatenFigures[4]++; break;
        case WHITE_PAWN : EatenFigures[5]++; break;
        case WHITE_ROOK : EatenFigures[6]++; break;
        case WHITE_KNIGHT : EatenFigures[7]++; break;
        case WHITE_BISHOP : EatenFigures[8]++; break;
        case WHITE_QUEEN : EatenFigures[9]++; break;

    }
}

string toChessNote(AppState& appState, Vector2i numberPos)
{
    auto& ChessboardIsInverted = appState.ChessboardIsInverted;

    string letterPos = "";

    if (ChessboardIsInverted)
    {
        letterPos += (char) abs(numberPos.x - 9) + 96;
        letterPos += (char) numberPos.y + 48;
    }
    else
    {
        letterPos += (char) numberPos.x + 96;
        letterPos += (char) (abs(numberPos.y - 9) + 48);
    }

    return letterPos;
}

Vector2i toCoord(AppState& appState, char a, char b)
{
    auto& ChessboardIsInverted = appState.ChessboardIsInverted;

    Vector2i numberPos;

    if (ChessboardIsInverted)
    {
        numberPos.x = abs((int) a - 105);
        numberPos.y = (int) b - 48;
    }
    else
    {
        numberPos.x = (int) a - 96;
        numberPos.y = abs(((int) b - 57));
    }

    return numberPos;
}

string GetNextEnvironmentMove(AppState& appState, int * ox, int * oy, int * nx, int * ny)
{
    auto& AllMovesInGame = appState.AllMovesInGame;

    string NEM;
    Vector2i OP, NP;

    do
    {
        NEM = getNextMove(AllMovesInGame);
    } while (NEM == "error");

    OP = toCoord(appState, NEM[0], NEM[1]);
    NP = toCoord(appState, NEM[2], NEM[3]);

    *ox = OP.x;
    *oy = OP.y;
    *nx = NP.x;
    *ny = NP.y;

    return NEM;
}

void RecordChessMove(AppState& appState, std::string chess_note)
{
    auto& AllMovesInGame = appState.AllMovesInGame;
    auto& WhoseMove = appState.WhoseMove;
    auto& PlayerMove = appState.PlayerMove;
    auto& EnvironmentMove = appState.EnvironmentMove;

    AllMovesInGame += " " + chess_note;

    if (WhoseMove == PlayerMove)
        printf("Хід комп'ютера: %s.\n", chess_note.c_str());
    else if (WhoseMove == EnvironmentMove)
        printf("Хід гравця: %s.\n", chess_note.c_str());

}

void FlipChessboard(AppState& appState)
{
    auto& board = appState.board;
    auto& ChessboardIsInverted = appState.ChessboardIsInverted;
    auto& blackKing = appState.blackKing;
    auto& whiteKing = appState.whiteKing;
    auto& PieceIsChoose = appState.PieceIsChoose;
    auto& OCC = appState.OCC;
    auto& HaveThereBeenChangesSinceTheLastSave = appState.HaveThereBeenChangesSinceTheLastSave;

    int temp[LENGTH][LENGTH];
    int i, j;

    for (i = 0; i < LENGTH; i++)
        for (j = 0; j < LENGTH; j++)
            temp[i][j] = board[LENGTH - 1 - i][LENGTH - 1 - j];

    for (i = 0; i < LENGTH; i++)
        for (j = 0; j < LENGTH; j++)
            board[i][j] = temp[i][j];

    ChessboardIsInverted = !ChessboardIsInverted;

    blackKing = {LENGTH - 1 - blackKing.x, LENGTH - 1 - blackKing.y};
    whiteKing = {LENGTH - 1 - whiteKing.x, LENGTH - 1 - whiteKing.y};

    if (PieceIsChoose)
        FigureSelection(appState, LENGTH - 1 - OCC.x, LENGTH - 1 - OCC.y);

    HaveThereBeenChangesSinceTheLastSave = false;
}

void ChangeButtonsAvailability(AppState& appState, AppScreens screen, bool status)
{
    auto& NewGame_button = appState.NewGame_button;
    auto& Options_button = appState.Options_button;
    auto& ExitFromApp_button = appState.ExitFromApp_button;
    auto& PauseGame_button = appState.PauseGame_button;
    auto& FlipChessboard_button = appState.FlipChessboard_button;

    if (screen == MainMenuScreen)
    {
        NewGame_button.SetEnabled(status);
        Options_button.SetEnabled(status);
        ExitFromApp_button.SetEnabled(status);
    }
    else if (screen == ChessGameScreen)
    {
        PauseGame_button.SetEnabled(status);
        FlipChessboard_button.SetEnabled(status);
    }
}

void ChangeOptionsButtonsAvailability(AppState& appState, bool status)
{
    auto& White_radioButton = appState.White_radioButton;
    auto& Black_radioButton = appState.Black_radioButton;
    auto& EasyLvl_radioButton = appState.EasyLvl_radioButton;
    auto& MediumLvl_radioButton = appState.MediumLvl_radioButton;
    auto& DifficultLvl_radioButton = appState.DifficultLvl_radioButton;

    White_radioButton.SetEnabled(status);
    Black_radioButton.SetEnabled(status);
    EasyLvl_radioButton.SetEnabled(status);
    MediumLvl_radioButton.SetEnabled(status);
    DifficultLvl_radioButton.SetEnabled(status);
}

void DeselectOptionsButtons(AppState& appState)
{
    auto& White_radioButton = appState.White_radioButton;
    auto& Black_radioButton = appState.Black_radioButton;
    auto& EasyLvl_radioButton = appState.EasyLvl_radioButton;
    auto& MediumLvl_radioButton = appState.MediumLvl_radioButton;
    auto& DifficultLvl_radioButton = appState.DifficultLvl_radioButton;

    White_radioButton.SetChoosed(false);
    Black_radioButton.SetChoosed(false);
    EasyLvl_radioButton.SetChoosed(false);
    MediumLvl_radioButton.SetChoosed(false);
    DifficultLvl_radioButton.SetChoosed(false);
}

void SetDefaultGameSettings(AppState& appState, bool is_this_first_launch)
{
    auto& CurrentWindow = appState.CurrentWindow;
    auto& blackKing = appState.blackKing;
    auto& whiteKing = appState.whiteKing;
    auto& GameIsOver = appState.GameIsOver;
    auto& HaveThereBeenChangesSinceTheLastSave = appState.HaveThereBeenChangesSinceTheLastSave;
    auto& ChessboardIsInverted = appState.ChessboardIsInverted;
    auto& PawnReachedLastHorizontal = appState.PawnReachedLastHorizontal;
    auto& PieceIsChoose = appState.PieceIsChoose;
    auto& WhoseMove = appState.WhoseMove;
    auto& IsTakingOnAisleActivated = appState.IsTakingOnAisleActivated;
    auto& IsTakingOnAisleUsed = appState.IsTakingOnAisleUsed;
    auto& AllMovesInGame = appState.AllMovesInGame;
    auto& PvP_radioButton = appState.PvP_radioButton;

    SetChessPiecesToTheirOriginalPosition(appState);
    ClearEatenFiguresArray(appState);
    CurrentWindow = MissingWindow;

    blackKing = {LEFT_EXTREME_COORDINATE + 4, TOP_EXTREME_COORDINATE};
    whiteKing = {LEFT_EXTREME_COORDINATE + 4, BOTTOM_EXTREME_COORDINATE};

    GameIsOver = 0;
    HaveThereBeenChangesSinceTheLastSave = true;
    ChessboardIsInverted = false;
    PawnReachedLastHorizontal = false;
    PieceIsChoose = false;
    WhoseMove = false;
    IsTakingOnAisleActivated = false;
    IsTakingOnAisleUsed = false;
    AllMovesInGame = "";
}

void ChangeGameSettings(AppState& appState)
{
    auto& PvE_radioButton = appState.PvE_radioButton;
    auto& PvP_radioButton = appState.PvP_radioButton;
    auto& Black_radioButton = appState.Black_radioButton;
    auto& White_radioButton = appState.White_radioButton;
    auto& EasyLvl_radioButton = appState.EasyLvl_radioButton;
    auto& MediumLvl_radioButton = appState.MediumLvl_radioButton;
    auto& DifficultLvl_radioButton = appState.DifficultLvl_radioButton;

    auto gameMode = appState.CurrentGameMode;
    auto playerColor = appState.PlayerColor;
    auto levelOfDifficulty = appState.LevelOfDifficulty;

    SetGameMode(appState, static_cast<GameModes>(gameMode));
    SetPiecesColorOfPlayer(appState, playerColor);
    SetLevelOfDifficulty(appState, levelOfDifficulty);
    switch (gameMode)
    {
        case PlayerVersusEnvironment : PvE_radioButton.SetChoosed(true); PvE_radioButton.ChangeRadioGroupChoosed(); break;
        case PlayerVersusPlayer : PvP_radioButton.SetChoosed(true); PvP_radioButton.ChangeRadioGroupChoosed(); break;
    }
    switch (playerColor)
    {
        case BLACK : Black_radioButton.SetChoosed(true); Black_radioButton.ChangeRadioGroupChoosed(); break;
        case WHITE : White_radioButton.SetChoosed(true); White_radioButton.ChangeRadioGroupChoosed(); break;
    }
    switch (levelOfDifficulty)
    {
        case 0 : EasyLvl_radioButton.SetChoosed(true); EasyLvl_radioButton.ChangeRadioGroupChoosed(); break;
        case 1 : MediumLvl_radioButton.SetChoosed(true); MediumLvl_radioButton.ChangeRadioGroupChoosed(); break;
        case 2 : DifficultLvl_radioButton.SetChoosed(true); DifficultLvl_radioButton.ChangeRadioGroupChoosed(); break;
    }
    ChangeOptionsButtonsAvailability(appState, gameMode == PlayerVersusEnvironment);
}

void SetGameMode(AppState& appState, GameModes gamemode)
{
    auto& CurrentGameMode = appState.CurrentGameMode;

    CurrentGameMode = gamemode;

    if (gamemode == PlayerVersusEnvironment)
    {
        SetPiecesColorOfPlayer(appState, WHITE);
        SetLevelOfDifficulty(appState, 1);
    }
}

void SetPiecesColorOfPlayer(AppState& appState, int pieces_color)
{
    auto& PlayerColor = appState.PlayerColor;
    auto& EnvironmentColor = appState.EnvironmentColor;
    auto& PlayerMove = appState.PlayerMove;
    auto& EnvironmentMove = appState.EnvironmentMove;

    if (pieces_color == BLACK)
    {
        PlayerColor = BLACK, EnvironmentColor = WHITE;
        PlayerMove = true, EnvironmentMove = false;
    }
    else if (pieces_color == WHITE)
    {
        PlayerColor = WHITE, EnvironmentColor = BLACK;
        PlayerMove = false, EnvironmentMove = true;
    }
}

void SetLevelOfDifficulty(AppState& appState, int level_of_difficulty)
{
    auto& LevelOfDifficulty = appState.LevelOfDifficulty;

    LevelOfDifficulty = level_of_difficulty;

    switch (LevelOfDifficulty)
    {
        case 0 : SetEngineSkillLevel("0"); break;
        case 1 : SetEngineSkillLevel("5"); break;
        case 2 : SetEngineSkillLevel("10"); break;
    }
}

char * s_gets(char * st, int n)
{
    char * ret_val;
    char * find;

    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n'); // поиск новой строки
        if (find)                // если адрес не равен NULL,
            *find = '\0';        // поместить туда нулевой символ
        else
            while (getchar() != '\n')
                continue;        // отбросить остаток строки
    }
    return ret_val;
}
