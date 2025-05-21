#ifndef SECONDARY_FUNCTIONS_H_INCLUDED
#define SECONDARY_FUNCTIONS_H_INCLUDED

#include "app-state.h"

#include <SFML/Graphics/Sprite.hpp>
#include "global constants.h"
#include "drawn object class.h"

using namespace std;
using namespace sf;

void OutputOfChessboardToConsole(AppState& appState);
void OutputPropertiesToConsole(AppState& appState);
void StateOfShahs(AppState& appState);
void OutputKingsCoordinates(AppState& appState);
void SetChessPiecesToTheirOriginalPosition(AppState& appState);
void ClearEatenFiguresArray(AppState& appState);
void FigureSelection(AppState& appState, int x, int y);
void WhichFigureIsSelected(AppState& appState, int x, int y, char * FigureType);
int WhichFigureHasMoved(AppState& appState, int x, int y);
int DetermineFigureColor(AppState& appState, int x, int y);
int DetermineFigureType(AppState& appState, int x, int y);
int DetermineFigure(AppState& appState, int x, int y);
void DetermineAnimatedSprite(AppState& appState, int Figure, DrawnObject ** ps);
int NumberOfFigures(AppState& appState, int FigureColor, int FigureType);
void TransformationColorDefinition(AppState& appState, int x, int y);
void CreationOfObjects(AppState& appState);
void CreateChessPieces(AppState& appState);
void CreateSmallChessPieces(AppState& appState);
void CreateBacklight(AppState& appState);
void CreateChessboards(AppState& appState);
void CreateScreensAndWindows(AppState& appState);
void CreateMainMenuScreen(AppState& appState);
void CreateChessGameScreen(AppState& appState);
void CreatePawnTransformationWindow(AppState& appState);
void CreateOptionsWindow(AppState& appState);
void CreateGameOverWindow(AppState& appState);
void CreateGameSaveWindow(AppState& appState);
void CreateGamePauseWindow(AppState& appState);
void ChangeButtonPropertiesByCoefficient(AppState& appState, Vector2f coeff);
void AdditionalActionsBeforeMovingFigure(AppState& appState, int ox, int oy, int nx, int ny);
void AdditionalActionsAfterMovingFigure(AppState& appState, int ox, int oy, int nx, int ny, bool IsMoveMade);

std::string RewriteChessNotation(AppState& appState);
void EnvironmentPawnTransformation(AppState& appState, std::string current_move, int x, int y);

int HasFigureBeenEaten(AppState& appState);
void AddFigureToEatenFigures(AppState& appState, int EatenFigure);

string toChessNote(AppState& appState, Vector2i numberPos);
Vector2i toCoord(AppState& appState, char a, char b);
string GetNextEnvironmentMove(AppState& appState, int * ox, int * oy, int * nx, int * ny);
void RecordChessMove(AppState& appState, std::string chess_note);

void FlipChessboard(AppState& appState);

void ChangeButtonsAvailability(AppState& appState, AppScreens screen, bool status);
void ChangeOptionsButtonsAvailability(AppState& appState, bool status);
void DeselectOptionsButtons(AppState& appState);

void SetDefaultGameSettings(AppState& appState, bool is_this_first_launch);
void SetGameMode(AppState& appState, GameModes gamemode);
void SetPiecesColorOfPlayer(AppState& appState, int pieces_color);
void SetLevelOfDifficulty(AppState& appState, int level_of_difficulty);

bool WriteDataToFile(AppState& appState);
bool ReadDataFromFile(AppState& appState);

char * s_gets(char * st, int n);

#endif // SECONDARY_FUNCTIONS_H_INCLUDED
