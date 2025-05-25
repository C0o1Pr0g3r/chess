#ifndef GAME_SAVE_API_INTERFACE_H_INCLUDED
#define GAME_SAVE_API_INTERFACE_H_INCLUDED

#include <filesystem>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include "../global constants.h"

using namespace sf;
using namespace std;
namespace fs = filesystem;
using json = nlohmann::json;

json getJsonFromFile(ifstream& in);
json getJsonFromString(const string& value);

struct SavedGameState
{
    Vector2i blackKing;
    Vector2i whiteKing;
    Vector2i PawnOnAisleCoordinates;
    Vector2i enPassantTargetSquare;
    bool ChessboardIsInverted;
    bool WhoseMove;
    bool IsTakingOnAisleActivated;
    bool IsTakingOnAisleUsed;
    bool WhoHasMoved;
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
    virtual bool save(const fs::path& appRootDir, const SavedGameState& gameState) = 0;
    virtual tuple<bool, SavedGameState> restore(const fs::path& appRootDir) = 0;

    virtual ~GameSaveApi() {}
};

#endif // GAME_SAVE_API_INTERFACE_H_INCLUDED
