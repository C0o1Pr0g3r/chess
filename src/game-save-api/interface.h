#ifndef GAME_SAVE_API_INTERFACE_H_INCLUDED
#define GAME_SAVE_API_INTERFACE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include "../global constants.h"

using namespace sf;
using namespace std;
using json = nlohmann::json;

json getJsonFromFile(ifstream& in);
json getJsonFromString(const string& value);

struct SavedGameState
{
    Vector2i blackKing;
    Vector2i whiteKing;
    Vector2i PawnOnAisleCoordinates;
    bool ChessboardIsInverted;
    bool WhoseMove;
    bool IsTakingOnAisleActivated;
    bool IsTakingOnAisleUsed;
    GameModes CurrentGameMode;
    int PlayerColor;
    int LevelOfDifficulty;
    int board[BOARD_SIZE][BOARD_SIZE];
    int EatenFigures[NUMBER_OF_EATEN_FIGURES];
    vector<string> AllMovesInGame;

    bool fromJson(const json& j);
    json toJson() const;
};


class GameSaveApi
{
public:
    virtual bool save(const SavedGameState& gameState) = 0;
    virtual tuple<bool, SavedGameState> restore() = 0;

    virtual ~GameSaveApi() {}
};

#endif // GAME_SAVE_API_INTERFACE_H_INCLUDED
