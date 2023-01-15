#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <string>
#include "global constants.h"
#include "external declaration of global variables.h"
#include "checks.h"
#include "secondary functions.h"
#include "animation functions.h"
#include "connector.hpp"

using namespace std;
using namespace sf;

void OutputOfChessboardToConsole(void)
{
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

void OutputPropertiesToConsole(void)
{
    printf("\nРазмер окна: %dx%d\n", window.getSize().x, window.getSize().y);
    printf("Координаты мыши: x = %d; y = %d\n", MC.x, MC.y);
    printf("Координаты доски: x = %d; y = %d\n", CC.x, CC.y);
    printf("Размер шахматной клетки: %d\n\n", CFDCP);
}

void StateOfShahs(void)
{
    char IsShah[] = "поставлен шах", IsNotShah[] = "\"НЕ\" поставлен шах";

    printf("Черным %s\n", CheckingKingOnShah(BLACK) ? IsShah : IsNotShah);
    printf("Белым %s\n\n", CheckingKingOnShah(WHITE) ? IsShah : IsNotShah);
}

void OutputKingsCoordinates(void)
{
    printf("Координаты черного короля: %dx%d\n", blackKing.x, blackKing.y);
    printf("Координаты белого короля: %dx%d\n", whiteKing.x, whiteKing.y);
}

void SetChessPiecesToTheirOriginalPosition(void)
{
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

void ClearEatenFiguresArray(void)
{
    int i;

    for (i = 0; i < 10; i++)
        EatenFigures[i] = 0;
}

void FigureSelection(int x, int y)
{
    bool status = false;
    char FigureType[10];

    if (WhoseMove)
    {
        if (FIGURE_COLOR(board[y][x]) == BLACK && !(x < LEFT_EXTREME_COORDINATE || x > RIGHT_EXTREME_COORDINATE || y < TOP_EXTREME_COORDINATE || y > BOTTOM_EXTREME_COORDINATE))
        {
            OCC.x = x;
            OCC.y = y;
            WhichFigureIsSelected(OCC.x, OCC.y, FigureType);
            printf("Выбрана черная фигура для перемещения, а именно — %s\n", FigureType);
            PieceIsChoose = true;
            status = true;
        }
        else
        {
            printf("Черная фигура не выбрана из-за нажатия мимо фигуры\n");
        }
    }
    else
    {
        if (FIGURE_COLOR(board[y][x]) == WHITE && !(x < LEFT_EXTREME_COORDINATE || x > RIGHT_EXTREME_COORDINATE || y < TOP_EXTREME_COORDINATE || y > BOTTOM_EXTREME_COORDINATE))
        {
            OCC.x = x;
            OCC.y = y;
            WhichFigureIsSelected(OCC.x, OCC.y, FigureType);
            printf("Выбрана белая фигура для перемещения, а именно — %s\n", FigureType);
            PieceIsChoose = true;
            status = true;
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

void WhichFigureIsSelected(int x, int y, char * FigureType)
{
    switch (FIGURE_TYPE(board[y][x]))
    {
        case PAWN: strcpy(FigureType, "Пешка"); break;
        case ROOK: strcpy(FigureType, "Ладья"); break;
        case BISHOP: strcpy(FigureType, "Слон"); break;
        case KNIGHT: strcpy(FigureType, "Конь"); break;
        case QUEEN: strcpy(FigureType, "Королева"); break;
        case KING: strcpy(FigureType, "Король"); break;
        default: strcpy(FigureType, "Никакая"); break;
    }
}

int WhichFigureHasMoved(int x, int y)
{
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

int DetermineFigureColor(int x, int y)
{
    int FigureColor;

    switch(FIGURE_COLOR(board[y][x]))
    {
        case BLACK : FigureColor = BLACK; break;
        case WHITE : FigureColor = WHITE; break;
    }

    return FigureColor;
}

int DetermineFigureType(int x, int y)
{
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

int DetermineFigure(int x, int y)
{
    int Figure;

    Figure = DetermineFigureColor(x, y) | DetermineFigureType(x, y);

    return Figure;
}

void DetermineAnimatedSprite(int Figure, DrawnObject ** ps)
{
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

int NumberOfFigures(int FigureColor, int FigureType)
{
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

void TransformationColorDefinition(int x, int y)
{
    int PawnColor = FIGURE_COLOR(board[y][x]) == BLACK ? BLACK : WHITE;

    if (HasPawnReachedLastHorizontal(x, y))
    {
        PawnReachedLastHorizontal = true;
        CurrentWindow = PawnTransformationWindow;
        ChangeButtonsAvailability(ChessGameScreen, false);
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

void CreationOfObjects(void)   //Creating Window, Loading Textures, Setting Textures To Sprites
{
    window.create(VideoMode(InitialWindowSize.x, InitialWindowSize.y), "Chess");
    CurrentScreen = MainMenuScreen;

    CreateChessPieces();
    CreateSmallChessPieces();
    CreateBacklight();
    CreateChessboards();
    CreateScreensAndWindows();
}

void CreateChessPieces(void)
{
    IntRect BP, BR, BKn, BB, BQ, BKi, WP, WR, WKn, WB, WQ, WKi;

    BP = {400, 0, 80, 80};
    BR = {320, 0, 80, 80};
    BKn = {240, 0, 80, 80};
    BB = {160, 0, 80, 80};
    BQ = {80, 0, 80, 80};
    BKi = {0, 0, 80, 80};
    WP = {400, 80, 80, 80};
    WR = {320, 80, 80, 80};
    WKn = {240, 80, 80, 80};
    WB = {160, 80, 80, 80};
    WQ = {80, 80, 80, 80};
    WKi = {0, 80, 80, 80};

    ChessPieces_texture.loadFromFile("Images\\Chess pieces.png");

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

void CreateSmallChessPieces(void)
{
    IntRect SBP, SBR, SBKn, SBB, SBQ, SBKi, SWP, SWR, SWKn, SWB, SWQ, SWKi;

    SBP = {250, 0, 50, 50};
    SBR = {200, 0, 50, 50};
    SBKn = {150, 0, 50, 50};
    SBB = {100, 0, 50, 50};
    SBQ = {50, 0, 50, 50};
    SBKi = {0, 0, 50, 50};
    SWP = {250, 50, 50, 50};
    SWR = {200, 50, 50, 50};
    SWKn = {150, 50, 50, 50};
    SWB = {100, 50, 50, 50};
    SWQ = {50, 50, 50, 50};
    SWKi = {0, 50, 50, 50};

    SmallChessPieces_texture.loadFromFile("Images\\Small chess pieces.png");

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

void CreateBacklight(void)
{
    IntRect DC, LC, GS, YS, RS;

    DC = {0, 0, 80, 80};
    LC = {80, 0, 80, 80};
    GS = {0, 80, 80, 80};
    YS = {80, 80, 80, 80};
    RS = {160, 80, 80, 80};

    Backlight_texture.loadFromFile("Images\\Backlight.png");

    DarkCircle_sprite.Create(Backlight_texture, DC);
    LightCircle_sprite.Create(Backlight_texture, LC);
    GreenSquare_sprite.Create(Backlight_texture, GS);
    YellowSquare_sprite.Create(Backlight_texture, YS);
    RedSquare_sprite.Create(Backlight_texture, RS);
}

void CreateChessboards(void)
{
    IntRect OC, IC;

    OC = {0, 0, 800, 800};
    IC = {800, 0, 800, 800};

    Chessboards_texture.loadFromFile("Images\\Chessboards.png");

    OrdinaryChessboard_sprite.Create(Chessboards_texture, OC);
    InvertedChessboard_sprite.Create(Chessboards_texture, IC);
}

void CreateScreensAndWindows(void)
{
    Backgrounds_texture.loadFromFile("Images\\Backgrounds.jpg");
    Windows_texture.loadFromFile("Images\\Windows.png");
    MainMenuScreen_guiElements_texture.loadFromFile("Images\\MainMenuScreen_guiElements.png");
    ChessGameScreen_guiElements_texture.loadFromFile("Images\\ChessGameScreen_guiElements.png");
    PawnTransformationWindow_guiElements_texture.loadFromFile("Images\\PawnTransformationWindow_guiElements.png");
    GameOverWindow_guiElements_texture.loadFromFile("Images\\GameOverWindow_guiElements.png");
    GamePauseWindow_guiElements_texture.loadFromFile("Images\\GamePauseWindow_guiElements.png");
    OptionsWindow_guiElements_texture.loadFromFile("Images\\OptionsWindow_guiElements.png");
    GameSaveWindow_guiElements_texture.loadFromFile("Images\\GameSaveWindow_guiElements.png");
    BackgroundDimmer_texture.loadFromFile("Images\\Background dimmer.png");

    CreateMainMenuScreen();
    CreateChessGameScreen();
    CreatePawnTransformationWindow();
    CreateOptionsWindow();
    CreateGameOverWindow();
    CreateGameSaveWindow();
    CreateGamePauseWindow();
    BackgroundDimmer.Create(BackgroundDimmer_texture, {0, 0, 1274, 800});
}

void CreateMainMenuScreen(void)
{
    Vector2u NGs, Os, EFAs, BTGmms;
    Vector2f NGp, Op, EFAp,BTGmmp;
    IntRect NGr1, Or1, EFAr1, PGr1, NGr2, Or2, EFAr2, MMSBr, BTGmmr1, BTGmmr2;

    NGs = {368, 84};
    Os = {226, 78};
    EFAs = {244, 78};
    BTGmms = {544, 66};

    Op = {InitialWindowSize.x / 2 - Os.x / 2, InitialWindowSize.y / 2 - Os.y / 2};
    NGp = {InitialWindowSize.x / 2 - NGs.x / 2, Op.y - NGs.y - 20};
    EFAp = {InitialWindowSize.x / 2 - EFAs.x / 2, Op.y + EFAs.y + 20};
    BTGmmp = {InitialWindowSize.x / 2 - BTGmms.x / 2, NGp.y - BTGmms.y - 20};

    NGr1 = {0, 0, 368, 84};
    NGr2 = {0, 84, 368, 84};
    Or1 = {0, 168, 226, 78};
    Or2 = {0, 246, 226, 78};
    EFAr1 = {0, 324, 244, 78};
    EFAr2 = {0, 402, 244, 78};
    MMSBr = {0, 0, 1274, 800};
    BTGmmr1 = {0, 0, 544, 66};
    BTGmmr2 = {0, 66, 544, 66};

    MainMenu_background.Create(Backgrounds_texture, MMSBr);
    NewGame_button.Create(MainMenuScreen_guiElements_texture, NGr1, NGr2, NGs, NGp);
    Options_button.Create(MainMenuScreen_guiElements_texture, Or1, Or2, Os, Op);
    ExitFromApp_button.Create(MainMenuScreen_guiElements_texture, EFAr1, EFAr2, EFAs, EFAp);
    BackToGameMM_button.Create(GamePauseWindow_guiElements_texture, BTGmmr1, BTGmmr2, BTGmms, BTGmmp);
}

void CreateChessGameScreen(void)
{
    Vector2u PGs, FCs, BMs, WMs, EFs;
    Vector2f FCp, PGp, BNGp, BMp, WMp, EFp;
    IntRect PGr1, PGr2, FCr1, FCr2, BMr, WMr, EFr, CGSBr;
    int DBCARS = 450;   //Distance Between Chessboard And Right Side
    int CS = 800;   //Chessboard Size

    PGs = FCs = {80, 80};
    BMs = {361, 70};
    WMs = {308, 70};
    EFs = {231, 120};

    PGp = {InitialWindowSize.x - PGs.x - 10, 10};
    FCp = {PGp.x - FCs.x - 20, 10};
    BMp = {(450 / 2 - BMs.x / 2) + CS, InitialWindowSize.y / 2 - BMs.y / 2};
    WMp = {(450 / 2 - WMs.x / 2) + CS, InitialWindowSize.y / 2 - WMs.y / 2};
    EFp = {(450 / 2 - EFs.x / 2) + CS, 440};

    PGr1 = {0, 260, 80, 80};
    PGr2 = {80, 260, 80, 80};
    FCr1 = {160, 260, 80, 80};
    FCr2 = {240, 260, 80, 80};
    BMr = {0, 0, 380, 70};
    WMr = {0, 70, 380, 70};
    EFr = {0, 140, 300, 120};
    CGSBr = {0, 800, 1274, 800};

    PauseGame_button.Create(ChessGameScreen_guiElements_texture, PGr1, PGr2, PGs, PGp);
    FlipChessboard_button.Create(ChessGameScreen_guiElements_texture, FCr1, FCr2, FCs, FCp);
    BlackMove_label.Create(ChessGameScreen_guiElements_texture, BMr, BMp);
    WhiteMove_label.Create(ChessGameScreen_guiElements_texture, WMr, WMp);
    EatenFigures_label.Create(ChessGameScreen_guiElements_texture, EFr, EFp);
    ChessGame_background.Create(Backgrounds_texture, CGSBr);
}

void CreatePawnTransformationWindow(void)
{
    Vector2u PTWs, BQs, BBs, BKs, BRs, WQs, WBs, WKs, WRs, PiecesSize;
    Vector2f PTWp, BQp, BBp, BKp, BRp, WQp, WBp, WKp, WRp, StartPosition;
    IntRect PTWr, BQr1, BBr1, BKr1, BRr1, WQr1, WBr1, WKr1, WRr1, BQr2, BBr2, BKr2, BRr2, WQr2, WBr2, WKr2, WRr2;

    PTWs = {832, 332};
    PiecesSize = BQs = BBs = BKs = BRs = WQs = WBs = WKs = WRs = {200, 200};

    PTWp = {InitialWindowSize.x / 2 - PTWs.x / 2, InitialWindowSize.y / 2 - PTWs.y / 2};
    StartPosition = {227, 240};
    BQp = {StartPosition.x + 10, StartPosition.y + 110};
    BBp = {StartPosition.x + 210, StartPosition.y + 110};
    BKp = {StartPosition.x + 410, StartPosition.y + 110};
    BRp = {StartPosition.x + 610, StartPosition.y + 110};
    WQp = {StartPosition.x + 10, StartPosition.y + 110};
    WBp = {StartPosition.x + 210, StartPosition.y + 110};
    WKp = {StartPosition.x + 410, StartPosition.y + 110};
    WRp = {StartPosition.x + 610, StartPosition.y + 110};

    PTWr = {740, 0, 832, 332};
    BQr1 = {0, 0, 200, 200};
    BBr1 = {200, 0, 200, 200};
    BKr1 = {400, 0, 200, 200};
    BRr1 = {600, 0, 200, 200};
    WQr1 = {0, 400, 200, 200};
    WBr1 = {200, 400, 200, 200};
    WKr1 = {400, 400, 200, 200};
    WRr1 = {600, 400, 200, 200};
    BQr2 = {0, 200, 200, 200};
    BBr2 = {200, 200, 200, 200};
    BKr2 = {400, 200, 200, 200};
    BRr2 = {600, 200, 200, 200};
    WQr2 = {0, 600, 200, 200};
    WBr2 = {200, 600, 200, 200};
    WKr2 = {400, 600, 200, 200};
    WRr2 = {600, 600, 200, 200};

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

void CreateOptionsWindow(void)
{
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

    OWp = {InitialWindowSize.x / 2 - OWs.x / 2, InitialWindowSize.y / 2 - OWs.y / 2};
    PvEp = {InitialWindowSize.x / 2 - PvEs.x - 7, OWp.y + 114};
    PvPp = {InitialWindowSize.x / 2 + 7, OWp.y + 114};
    Wp = {InitialWindowSize.x / 2 - Ws.x - 7, OWp.y + 266};
    Bp = {InitialWindowSize.x / 2 + 7, OWp.y + 266};
    Ep = {InitialWindowSize.x / 2 - Es.x - 7, OWp.y + 448};
    Mp = {InitialWindowSize.x / 2 + 7, OWp.y + 448};
    Dp = {InitialWindowSize.x / 2 - Ds.x / 2, OWp.y + 527};
    EFOWp = {OWp.x + 20, OWp.y + 20};
    GMp = {InitialWindowSize.x / 2 - GMs.x / 2, OWp.y + 35};
    PCp = {InitialWindowSize.x / 2 - PCs.x / 2, OWp.y + 189};
    LODp = {InitialWindowSize.x / 2 - LODs.x / 2, OWp.y + 371};

    OWr = {0, 0, 740, 640};

    PvEr1 = {0, 188, 324, 68};
    PvEr2 = {0, 256, 324, 68};
    PvEr3 = {0, 324, 324, 68};

    PvPr1 = {324, 188,324, 68};
    PvPr2 = {324, 256, 324, 68};
    PvPr3 = {324, 324, 324, 68};

    Wr1 = {0, 392, 200, 75};
    Wr2 = {0, 467, 200, 75};
    Wr3 = {0, 542, 200, 75};

    Br1 = {200, 392, 200, 75};
    Br2 = {200, 467, 200, 75};
    Br3 = {200, 542, 200, 75};

    Er1 = {0, 617, 324, 64};
    Er2 = {0, 681, 324, 64};
    Er3 = {0, 745, 324, 64};

    Mr1 = {324, 617, 324, 64};
    Mr2 = {324, 681, 324, 64};
    Mr3 = {324, 745, 324, 64};

    Dr1 = {0, 809, 324, 64};
    Dr2 = {324, 809, 324, 64};
    Dr3 = {0, 873, 324, 64};

    EFOWr1 = {366, 64, 80, 60};
    EFOWr2 = {446, 64, 80, 60};
    GMr = {0, 0, 487, 64};
    PCr = {0, 64, 366, 62};
    LODr = {0, 126, 626, 62};

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

void CreateGameOverWindow(void)
{
    Vector2u GOWs, BNGs, GTMs, Ms, Ps, BWs, WWs, Ss;
    Vector2f GOWp, BNGp, GTMp,Mp, Pp, BWp, WWp, Sp;
    IntRect GOWr, BNGr1, GTMr1, BNGr2, GTMr2, Mr, Pr, BWr, WWr, Sr;

    GOWs = {680, 460};
    BNGs = {522, 70};
    GTMs = {560, 68};
    Ms = Ps = {170, 74};
    BWs = WWs = Ss = {420, 166};

    GOWp = {InitialWindowSize.x / 2 - GOWs.x / 2, InitialWindowSize.y / 2 - GOWs.y / 2};
    BNGp = {GOWs.x / 2 - BNGs.x / 2 + GOWp.x, GOWp.y + 278};
    GTMp = {GOWs.x / 2 - GTMs.x / 2 + GOWp.x, GOWp.y + 365};
    Mp = {GOWs.x / 2 - Ms.x / 2 + GOWp.x, GOWp.y + 20};
    Pp = {GOWs.x / 2 - Ps.x / 2 + GOWp.x, GOWp.y + 20};
    BWp = {GOWs.x / 2 - BWs.x / 2 + GOWp.x, GOWp.y + 90};
    WWp = {GOWs.x / 2 - WWs.x / 2 + GOWp.x, GOWp.y + 90};
    Sp = {GOWs.x / 2 - Ss.x / 2 + GOWp.x, GOWp.y + 90};

    GOWr = {0, 640, 680, 460};
    BNGr1 = {0, 572, 522, 70};
    BNGr2 = {0, 642, 522, 70};
    GTMr1 = {0, 712, 560, 68};
    GTMr2 = {0, 780, 560, 68};
    Mr = {0, 0, 170, 74};
    Pr = {170, 0, 170, 74};
    BWr = {0, 74, 420, 166};
    WWr = {0, 240, 420, 166};
    Sr = {0, 406, 420, 166};

    GameOver_window.Create(Windows_texture, GOWr, GOWp);
    BeginNewGame_button.Create(GameOverWindow_guiElements_texture, BNGr1, BNGr2, BNGs, BNGp);
    GoToMenu_button.Create(GameOverWindow_guiElements_texture, GTMr1, GTMr2, GTMs, GTMp);
    Mat_label.Create(GameOverWindow_guiElements_texture, Mr, Mp);
    Pat_label.Create(GameOverWindow_guiElements_texture, Pr, Pp);
    BlackWin_label.Create(GameOverWindow_guiElements_texture, BWr, BWp);
    WhiteWin_label.Create(GameOverWindow_guiElements_texture, WWr, WWp);
    Standoff_label.Create(GameOverWindow_guiElements_texture, Sr, Sp);
}

void CreateGameSaveWindow(void)
{
    Vector2u GSWs, WYLTSGs, GSWYs, GSWNs;
    Vector2f GSWp, WYLTSGp, GSWYp, GSWNp;
    IntRect GSWr, WYLTSGr, GSWYr1, GSWNr1, GSWYr2, GSWNr2;

    GSWs = {620, 300};
    WYLTSGs = {548, 112};
    GSWYs = {146, 68};
    GSWNs = {84, 66};

    GSWp = {InitialWindowSize.x / 2 - GSWs.x / 2, InitialWindowSize.y / 2 - GSWs.y / 2};
    WYLTSGp = {InitialWindowSize.x / 2 - WYLTSGs.x / 2, GSWp.y + 40};
    GSWYp = {((GSWp.x + InitialWindowSize.x / 2) / 2) - GSWYs.x / 2 + 30, GSWp.y + 182};
    GSWNp = {((GSWp.x + GSWs.x + InitialWindowSize.x / 2) / 2) - GSWNs.x / 2 - 30, GSWp.y + 183};

    GSWr = {740, 332, 620, 300};
    WYLTSGr = {0, 0, 548, 112};
    GSWYr1 = {0, 112, 146, 68};
    GSWYr2 = {146, 112, 146, 68};
    GSWNr1 = {292, 112, 84, 66};
    GSWNr2 = {376, 112, 84, 66};

    GameSave_window.Create(Windows_texture, GSWr, GSWp);
    WouldYouLikeToSaveGame_label.Create(GameSaveWindow_guiElements_texture, WYLTSGr, WYLTSGp);
    GSWYes_button.Create(GameSaveWindow_guiElements_texture, GSWYr1, GSWYr2, GSWYs, GSWYp);
    GSWNo_button.Create(GameSaveWindow_guiElements_texture, GSWNr1, GSWNr2, GSWNs, GSWNp);
}

void CreateGamePauseWindow(void)
{
    Vector2u GPWs, BTGs, SGs, EFCGs;
    Vector2f GPWp, BTGp, SGp, EFCGp;
    IntRect GPWr, BTGr1, SGr1, BTGr2, SGr2, EFCGr1, EFCGr2;

    GPWs = {670, 340};
    BTGs = {544, 66};
    SGs = {422, 66};
    EFCGs = {194, 54};

    GPWp = {InitialWindowSize.x / 2 - GPWs.x / 2, InitialWindowSize.y / 2 - GPWs.y / 2};
    BTGp = {GPWs.x / 2 - BTGs.x / 2 + GPWp.x, GPWp.y + 57};
    SGp = {GPWs.x / 2 - SGs.x / 2 + GPWp.x, GPWp.y + 143};
    EFCGp = {GPWs.x / 2 - EFCGs.x / 2 + GPWp.x, GPWp.y + 229};

    GPWr = {0, 1100, 670, 340};
    BTGr1 = {0, 0, 544, 66};
    BTGr2 = {0, 66, 544, 66};
    SGr1 = {0, 132, 422, 66};
    SGr2 = {0, 198, 422, 66};
    EFCGr1 = {0, 264, 194, 54};
    EFCGr2 = {0, 318, 194, 54};

    GamePause_window.Create(Windows_texture, GPWr, GPWp);
    BackToGame_button.Create(GamePauseWindow_guiElements_texture, BTGr1, BTGr2, BTGs, BTGp);
    SaveGame_button.Create(GamePauseWindow_guiElements_texture, SGr1, SGr2, SGs, SGp);
    ExitFromChessGame_button.Create(GamePauseWindow_guiElements_texture, EFCGr1, EFCGr2, EFCGs, EFCGp);
}

void ChangeButtonPropertiesByCoefficient(Vector2f coeff)
{
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

void AdditionalActionsBeforeMovingFigure(int ox, int oy, int nx, int ny)
{
    FigureByOldCoordinates = board[oy][ox];
    FigureByNewCoordinates = board[ny][nx];
}

void AdditionalActionsAfterMovingFigure(int ox, int oy, int nx, int ny, bool IsMoveMade)
{
    int EatenFigure;
    string current_chess_move;
    Vector2i o, n;

    if (IsMoveMade)
    {
        FigureMovementAnimation(ox, oy, nx, ny);
        current_chess_move = toChessNote(Vector2i(ox, oy));
        current_chess_move += toChessNote(Vector2i(nx, ny));
        RecordChessMove(current_chess_move);

        if (EatenFigure = HasFigureBeenEaten())
            AddFigureToEatenFigures(EatenFigure);

        if (IsTakingOnAisleUsed)
        {
            board[oy][nx] = 0;
            IsTakingOnAisleUsed = false;
        }

        pNC = {nx, ny};

        if (PawnReachedLastHorizontal && CurrentGameMode == PlayerVersusEnvironment && WhoseMove == PlayerMove)
        {
            EnvironmentPawnTransformation(CurrentChessNote, nx, ny);
            RewriteChessNotation();
        }

        HaveThereBeenChangesSinceTheLastSave = false;

        o = toCoord(current_chess_move[0], current_chess_move[1]);
        n = toCoord(current_chess_move[2], current_chess_move[3]);
        cout << "Шахматная нотация: " << current_chess_move << endl;
        printf("Координатная нотация: oldPos = %d, %d   ;   newPos = %d, %d\n", o.x, o.y , n.x, n.y);
    }
    else
    {
        FigureByOldCoordinates = 0;
        FigureByNewCoordinates = 0;
    }

    if ((FIGURE_COLOR(board[ny][nx]) == BLACK && WhoseMove) || (FIGURE_COLOR(board[ny][nx]) == WHITE && !WhoseMove))
        FigureSelection(nx, ny);
}

std::string RewriteChessNotation(void)
{
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

void EnvironmentPawnTransformation(std::string current_move, int x, int y)
{
    cout << "current_move: " << current_move << endl;
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
    ChangeButtonsAvailability(ChessGameScreen, true);
}

int HasFigureBeenEaten(void)
{
    int EatenFigure = 0;

    if (FigureByNewCoordinates > 0)
        EatenFigure = FigureByNewCoordinates;
    else if (FigureByNewCoordinates == 0 && IsTakingOnAisleUsed)
        EatenFigure = board[PawnOnAisleCoordinates.y][PawnOnAisleCoordinates.x];

    return EatenFigure;
}

void AddFigureToEatenFigures(int EatenFigure)
{
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

string toChessNote(Vector2i numberPos)
{
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

Vector2i toCoord(char a, char b)
{
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

string GetNextEnvironmentMove(int * ox, int * oy, int * nx, int * ny)
{
    string NEM;
    Vector2i OP, NP;

    do
    {
        NEM = getNextMove(AllMovesInGame);
    } while (NEM == "error");

    OP = toCoord(NEM[0], NEM[1]);
    NP = toCoord(NEM[2], NEM[3]);

    *ox = OP.x;
    *oy = OP.y;
    *nx = NP.x;
    *ny = NP.y;

    return NEM;
}

void RecordChessMove(std::string chess_note)
{
    cout << "chess_note: " << "\"" << chess_note << "\"" << endl;
    AllMovesInGame += " " + chess_note;

    if (WhoseMove == PlayerMove)
        cout << "Ход компьютера: " << chess_note << endl;
    else if (WhoseMove == EnvironmentMove)
        cout << "Ход игрока: " << chess_note << endl;

    //cout << "Все ходы в игре: " << AllMovesInGame << endl;
}

void FlipChessboard(void)
{
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
        FigureSelection(LENGTH - 1 - OCC.x, LENGTH - 1 - OCC.y);

    HaveThereBeenChangesSinceTheLastSave = false;
}

void ChangeButtonsAvailability(AppScreens screen, bool status)
{
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

void ChangeOptionsButtonsAvailability(bool status)
{
    White_radioButton.SetEnabled(status);
    Black_radioButton.SetEnabled(status);
    EasyLvl_radioButton.SetEnabled(status);
    MediumLvl_radioButton.SetEnabled(status);
    DifficultLvl_radioButton.SetEnabled(status);
}

void DeselectOptionsButtons(void)
{
    White_radioButton.SetChoosed(false);
    Black_radioButton.SetChoosed(false);
    EasyLvl_radioButton.SetChoosed(false);
    MediumLvl_radioButton.SetChoosed(false);
    DifficultLvl_radioButton.SetChoosed(false);
}

void SetDefaultGameSettings(bool is_this_first_launch)
{
    SetChessPiecesToTheirOriginalPosition();
    ClearEatenFiguresArray();
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

void SetGameMode(GameModes gamemode)
{
    CurrentGameMode = gamemode;

    if (gamemode == PlayerVersusEnvironment)
    {
        SetPiecesColorOfPlayer(WHITE);
        SetLevelOfDifficulty(1);
    }
}

void SetPiecesColorOfPlayer(int pieces_color)
{
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

void SetLevelOfDifficulty(int level_of_difficulty)
{
    LevelOfDifficulty = level_of_difficulty;

    switch (LevelOfDifficulty)
    {
        case 0 : SetEngineSkillLevel("0"); break;
        case 1 : SetEngineSkillLevel("5"); break;
        case 2 : SetEngineSkillLevel("10"); break;
    }
}

bool WriteDataToFile(void)
{
    ofstream out;
    int i, j;
    bool status = true;

    out.open("saved data.txt");

    if (out.is_open())
    {
        if (IsThereSavedGame)
        {
            out << 1 << endl;
            out << blackKing.x << " " << blackKing.y << endl;
            out << whiteKing.x << " " << whiteKing.y << endl;
            out << PawnOnAisleCoordinates.x << " " << PawnOnAisleCoordinates.y << endl;
            out << ChessboardIsInverted << endl;
            out << WhoseMove << endl;
            out << IsTakingOnAisleActivated << endl;
            out << IsTakingOnAisleUsed << endl;
            out << WhoHasMoved << endl;
            out << CurrentGameMode << endl;
            out << PlayerColor << endl;
            out << LevelOfDifficulty << endl;

            out << endl;
            for (i = 0; i < LENGTH; i++)
            {
                for (j = 0; j < LENGTH; j++)
                {
                    out << board[i][j] << " ";
                }
                out << endl;
            }

            out << endl;
            for (i = 0; i < 10; i++)
                out << EatenFigures[i] << " ";
            out << endl << endl;

            out << AllMovesInGame << endl;
        }
        else
        {
            out << 0 << "\r\n";
        }
        out << EOF;
    }
    else
        status = false;

    out.close();

    return status;
}

bool ReadDataFromFile(void)
{
    FILE * fp;
    int i, j;
    char is_there_saved_game;
    Vector2i black_king_pos, white_king_pos, pawn_on_aisle_coordinates;
    int chessboard_is_inverted, piece_is_choose, whose_move, is_taking_on_aisle_activated, is_taking_on_aisle_used, who_has_moved, current_game_mode, player_color;
    int level_of_difficulty;
    int arrangement_of_figures_on_board[LENGTH][LENGTH], eaten_figures[10];
    char all_moves_in_game[4096], * pt;
    int all_moves_length;
    bool status = true;

    if ((fp = fopen("saved data.txt", "rb+")) == NULL)
    {
        printf("Ошибка при открытии файла\n");
        SetGameMode(PlayerVersusPlayer);
        PvP_radioButton.SetChoosed(true);
        ChangeOptionsButtonsAvailability(false);
        status = false;
    }
    else
    {
        rewind(fp);

        fscanf(fp, "%c", &is_there_saved_game);
        if (is_there_saved_game == '1')
        {
            printf("Сохраненная игра присутствует\n");
            fscanf(fp, "%d %d", &black_king_pos.x, &black_king_pos.y);
            fscanf(fp, "%d %d", &white_king_pos.x, &white_king_pos.y);
            fscanf(fp, "%d %d", &pawn_on_aisle_coordinates.x, &pawn_on_aisle_coordinates.y);
            fscanf(fp, "%d", &chessboard_is_inverted);
            fscanf(fp, "%d", &whose_move);
            fscanf(fp, "%d", &is_taking_on_aisle_activated);
            fscanf(fp, "%d", &is_taking_on_aisle_used);
            fscanf(fp, "%d", &who_has_moved);
            fscanf(fp, "%d", &current_game_mode);
            fscanf(fp, "%d", &player_color);
            fscanf(fp, "%d", &level_of_difficulty);

            for (i = 0; i < LENGTH; i++)
                for (j = 0; j < LENGTH; j++)
                    fscanf(fp, "%d", &arrangement_of_figures_on_board[i][j]);

            for (i = 0; i < 10; i++)
                fscanf(fp, "%d", &eaten_figures[i]);

            fseek(fp, 5, SEEK_CUR);
            fgets(all_moves_in_game, 4096, fp);
            all_moves_length = strlen(all_moves_in_game);

            printf("Сохраненная игра: %c\n", is_there_saved_game);
            printf("Координаты черного короля: %d, %d\n", black_king_pos.x, black_king_pos.y);
            printf("Координаты белого короля: %d, %d\n", white_king_pos.x, white_king_pos.y);
            printf("Координаты пешки на проходе: %d, %d\n", pawn_on_aisle_coordinates.x, pawn_on_aisle_coordinates.y);
            printf("Доска инвертирована: %d\n", chessboard_is_inverted);
            printf("Чей ход: %d\n", whose_move);
            printf("Взятие на проходе активировано: %d\n",is_taking_on_aisle_activated );
            printf("Взятие на проходе использовано: %d\n", is_taking_on_aisle_used);
            printf("Кто ходил: %d\n", who_has_moved);
            printf("Режим игры: %d\n", current_game_mode);
            printf("Цвет фигур игрока: %d\n", player_color);
            printf("Уровень сложности: %d\n", level_of_difficulty);
            printf("Шахматная доска:\n");

            for (i = 0; i < LENGTH; i++)
            {
                for (j = 0; j < LENGTH; j++)
                    printf("%4d ", arrangement_of_figures_on_board[i][j]);
                putchar('\n');
            }
            printf("Съеденные фигуры:\n");
            for (i = 0; i < LENGTH; i++)
                printf("%2d", eaten_figures[i]);
            putchar('\n');

            printf("Все ходы в игре: \"%s\"", all_moves_in_game);
        }
        else
        {
            printf("Сохраненная игра отсутствует\n");
            status = false;
        }

        if (status)
        {
            IsThereSavedGame = true;
            blackKing = black_king_pos;
            whiteKing = white_king_pos;
            PawnOnAisleCoordinates = pawn_on_aisle_coordinates;
            ChessboardIsInverted = chessboard_is_inverted;
            WhoseMove = whose_move;
            IsTakingOnAisleActivated = is_taking_on_aisle_activated;
            IsTakingOnAisleUsed = is_taking_on_aisle_used;
            WhoHasMoved = who_has_moved;
            SetGameMode((GameModes) current_game_mode);
            if (CurrentGameMode == PlayerVersusEnvironment)
            {
                SetPiecesColorOfPlayer(player_color);
                SetLevelOfDifficulty(level_of_difficulty);
                switch (CurrentGameMode)
                {
                    case PlayerVersusEnvironment : PvE_radioButton.SetChoosed(true); PvE_radioButton.ChangeRadioGroupChoosed(); break;
                    case PlayerVersusPlayer : PvP_radioButton.SetChoosed(true); PvP_radioButton.ChangeRadioGroupChoosed(); break;
                }
                switch (PlayerColor)
                {
                    case BLACK : Black_radioButton.SetChoosed(true); Black_radioButton.ChangeRadioGroupChoosed(); break;
                    case WHITE : White_radioButton.SetChoosed(true); White_radioButton.ChangeRadioGroupChoosed(); break;
                }
                switch (LevelOfDifficulty)
                {
                    case 0 : EasyLvl_radioButton.SetChoosed(true); EasyLvl_radioButton.ChangeRadioGroupChoosed(); break;
                    case 1 : MediumLvl_radioButton.SetChoosed(true); MediumLvl_radioButton.ChangeRadioGroupChoosed(); break;
                    case 2 : DifficultLvl_radioButton.SetChoosed(true); DifficultLvl_radioButton.ChangeRadioGroupChoosed(); break;
                }
            }
            else
            {
                PvP_radioButton.SetChoosed(true);
                ChangeOptionsButtonsAvailability(false);
            }

            for (i = 0; i < LENGTH; i++)
                for (j = 0; j < LENGTH; j++)
                    board[i][j] = arrangement_of_figures_on_board[i][j];

            for (i = 0; i < LENGTH; i++)
                EatenFigures[i] = eaten_figures[i];

            for (i = 0; i < all_moves_length; i++)
            {
                if (all_moves_in_game[i] == '\n')
                    break;
                AllMovesInGame += all_moves_in_game[i];
            }
        }
        else
        {
            SetGameMode(PlayerVersusPlayer);
            PvP_radioButton.SetChoosed(true);
            ChangeOptionsButtonsAvailability(false);
        }
    }


    if (fclose(fp))
    {
        printf("Ошибка при закрытии файла\n");
        status = false;
    }

    return status;
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
