#ifndef BACKLIGHT_FUNCTIONS_H_INCLUDED
#define BACKLIGHT_FUNCTIONS_H_INCLUDED

void DrawBacklight(int x, int y);
void SelectedFigureBacklight(int x, int y);
void BacklightOfPossibleMovements(int ox, int oy);
void BacklightOfPossiblePawnMovements(int OpponentColor, int ox, int oy);
void BacklightOfPossibleRookMovements(int OpponentColor, int ox, int oy);
void BacklightOfPossibleBishopMovements(int OpponentColor, int ox, int oy);
void BacklightOfPossibleQueenMovements(int OpponentColor, int ox, int oy);
void BacklightOfPossibleKnightMovements(int OpponentColor, int ox, int oy);
void BacklightOfPossibleKingMovements(int OpponentColor, int ox, int oy);
void BacklightOfKingUnderShah(int ox, int oy);

#endif // BACKLIGHT_FUNCTIONS_H_INCLUDED
