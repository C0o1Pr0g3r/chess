#ifndef MOVE_FUNCTIONS_H_INCLUDED
#define MOVE_FUNCTIONS_H_INCLUDED

bool FigureMovementPvP(int ox, int oy, int nx, int ny);
bool FigureMovementPvEPlayer(int ox, int oy, int nx, int ny);
bool FigureMovementPvEEnvironment(int ox, int oy, int nx, int ny);

bool moveFigure(int ox, int oy, int nx, int ny);
bool movePawn(int ox, int oy, int nx, int ny);
bool moveRook(int ox, int oy, int nx, int ny);
bool moveBishop(int ox, int oy, int nx, int ny);
bool moveKnight(int ox, int oy, int nx, int ny);
bool moveQueen(int ox, int oy, int nx, int ny);
bool moveKing(int ox, int oy, int nx, int ny);
void DoCastling(int okingx, int nkingx, int orookx, int nrookx, int kry);

#endif // MOVE_FUNCTIONS_H_INCLUDED
