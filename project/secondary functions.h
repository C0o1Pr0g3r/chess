#ifndef SECONDARY_FUNCTIONS_H_INCLUDED
#define SECONDARY_FUNCTIONS_H_INCLUDED

#include <SFML/Graphics/Sprite.hpp>
#include "global constants.h"
#include "drawn object class.h"

using namespace std;
using namespace sf;

void OutputOfChessboardToConsole(void);
void OutputPropertiesToConsole(void);
void StateOfShahs(void);
void OutputKingsCoordinates(void);
void SetChessPiecesToTheirOriginalPosition(void);
void ClearEatenFiguresArray(void);
void FigureSelection(int x, int y);
void WhichFigureIsSelected(int x, int y, char * FigureType);
int WhichFigureHasMoved(int x, int y);
int DetermineFigureColor(int x, int y);
int DetermineFigureType(int x, int y);
int DetermineFigure(int x, int y);
void DetermineAnimatedSprite(int Figure, DrawnObject ** ps);
int NumberOfFigures(int FigureColor, int FigureType);
void TransformationColorDefinition(int x, int y);
void CreationOfObjects(void);
void CreateChessPieces(void);
void CreateSmallChessPieces(void);
void CreateBacklight(void);
void CreateChessboards(void);
void CreateScreensAndWindows(void);
void CreateMainMenuScreen(void);
void CreateChessGameScreen(void);
void CreatePawnTransformationWindow(void);
void CreateOptionsWindow(void);
void CreateGameOverWindow(void);
void CreateGameSaveWindow(void);
void CreateGamePauseWindow(void);
void ChangeButtonPropertiesByCoefficient(Vector2f coeff);
void AdditionalActionsBeforeMovingFigure(int ox, int oy, int nx, int ny);
void AdditionalActionsAfterMovingFigure(int ox, int oy, int nx, int ny, bool IsMoveMade);

std::string RewriteChessNotation(void);
void EnvironmentPawnTransformation(std::string current_move, int x, int y);

int HasFigureBeenEaten(void);
void AddFigureToEatenFigures(int EatenFigure);

string toChessNote(Vector2i numberPos);
Vector2i toCoord(char a, char b);
string GetNextEnvironmentMove(int * ox, int * oy, int * nx, int * ny);
void RecordChessMove(std::string chess_note);

void FlipChessboard(void);

void ChangeButtonsAvailability(AppScreens screen, bool status);
void ChangeOptionsButtonsAvailability(bool status);
void DeselectOptionsButtons(void);

void SetDefaultGameSettings(bool is_this_first_launch);
void SetGameMode(GameModes gamemode);
void SetPiecesColorOfPlayer(int pieces_color);
void SetLevelOfDifficulty(int level_of_difficulty);

bool WriteDataToFile(void);
bool ReadDataFromFile(void);

char * s_gets(char * st, int n);

#endif // SECONDARY_FUNCTIONS_H_INCLUDED
