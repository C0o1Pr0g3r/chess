
#include <fstream>
#include "interface.h"

json getJsonFromFile(ifstream& in)
{
    return json::parse(in);
}

json getJsonFromString(const string& value)
{
    return json::parse(value);
}

bool SavedGameState::fromJson(const json& j)
{
    SavedGameState gameState;

    if (!j.is_object())
    {
        fprintf(stderr, "Файл із даними гри містить неправильну структуру даних.\n");
        return false;
    }

    if (!j.contains("blackKing")) return false;
    if (!(j["blackKing"].contains("x") && j["blackKing"]["x"].is_number_integer())) return false;
    if (!(j["blackKing"].contains("y") && j["blackKing"]["y"].is_number_integer())) return false;
    gameState.blackKing.x = j["blackKing"]["x"].template get<int>();
    gameState.blackKing.y = j["blackKing"]["y"].template get<int>();

    if (!j.contains("whiteKing")) return false;
    if (!(j["whiteKing"].contains("x") && j["whiteKing"]["x"].is_number_integer())) return false;
    if (!(j["whiteKing"].contains("y") && j["whiteKing"]["y"].is_number_integer())) return false;
    gameState.whiteKing.x = j["whiteKing"]["x"].template get<int>();
    gameState.whiteKing.y = j["whiteKing"]["y"].template get<int>();

    if (!j.contains("PawnOnAisleCoordinates")) return false;
    if (!(j["PawnOnAisleCoordinates"].contains("x") && j["PawnOnAisleCoordinates"]["x"].is_number_integer())) return false;
    if (!(j["PawnOnAisleCoordinates"].contains("y") && j["PawnOnAisleCoordinates"]["y"].is_number_integer())) return false;
    gameState.PawnOnAisleCoordinates.x = j["PawnOnAisleCoordinates"]["x"].template get<int>();
    gameState.PawnOnAisleCoordinates.y = j["PawnOnAisleCoordinates"]["y"].template get<int>();

    if (!j.contains("enPassantTargetSquare")) return false;
    if (!(j["enPassantTargetSquare"].contains("x") && j["enPassantTargetSquare"]["x"].is_number_integer())) return false;
    if (!(j["enPassantTargetSquare"].contains("y") && j["enPassantTargetSquare"]["y"].is_number_integer())) return false;
    gameState.enPassantTargetSquare.x = j["enPassantTargetSquare"]["x"].template get<int>();
    gameState.enPassantTargetSquare.y = j["enPassantTargetSquare"]["y"].template get<int>();

    if (!(j.contains("ChessboardIsInverted") && j["ChessboardIsInverted"].is_boolean())) return false;
    gameState.ChessboardIsInverted = j["ChessboardIsInverted"].template get<bool>();

    if (!(j.contains("WhoseMove") && j["WhoseMove"].is_boolean())) return false;
    gameState.WhoseMove = j["WhoseMove"].template get<bool>();

    if (!(j.contains("IsTakingOnAisleActivated") && j["IsTakingOnAisleActivated"].is_boolean())) return false;
    gameState.IsTakingOnAisleActivated = j["IsTakingOnAisleActivated"].template get<bool>();

    if (!(j.contains("IsTakingOnAisleUsed") && j["IsTakingOnAisleUsed"].is_boolean())) return false;
    gameState.IsTakingOnAisleUsed = j["IsTakingOnAisleUsed"].template get<bool>();

    if (!(j.contains("WhoHasMoved") && j["WhoHasMoved"].is_boolean())) return false;
    gameState.WhoHasMoved = j["WhoHasMoved"].template get<bool>();


    if (!(j.contains("CurrentGameMode") && j["CurrentGameMode"].is_number_integer())) return false;
    gameState.CurrentGameMode = j["CurrentGameMode"].template get<GameModes>();

    if (!(j.contains("PlayerColor") && j["PlayerColor"].is_number_integer())) return false;
    gameState.PlayerColor = j["PlayerColor"].template get<int>();

    if (!(j.contains("LevelOfDifficulty") && j["LevelOfDifficulty"].is_number_integer())) return false;
    gameState.LevelOfDifficulty = j["LevelOfDifficulty"].template get<int>();

    if (!(j.contains("board") && j["board"].is_array())) return false;
    for (size_t i = 0; i < j["board"].size() && i < BOARD_SIZE; ++i)
    {
        if (!j["board"][i].is_array()) return false;
        for (size_t k = 0; k < j["board"][i].size() && k < BOARD_SIZE; ++k)
        {
            if (!j["board"][i][k].is_number_integer()) return false;
            gameState.board[i][k] = j["board"][i][k].template get<int>();
        }
    }

    if (!(j.contains("EatenFigures") && j["EatenFigures"].is_array())) return false;
    for (size_t i = 0; i < j["EatenFigures"].size() && i < NUMBER_OF_EATEN_FIGURES; ++i)
    {
        if (!j["EatenFigures"][i].is_number_integer()) return false;
        gameState.EatenFigures[i] = j["EatenFigures"][i].template get<int>();
    }

    vector<string> tempAllMovesInGame;
    if (!(j.contains("AllMovesInGame") && j["AllMovesInGame"].is_array())) return false;
    for (size_t i = 0; i < j["AllMovesInGame"].size(); ++i)
    {
        if (!j["AllMovesInGame"][i].is_string()) return false;

        tempAllMovesInGame.push_back(j["AllMovesInGame"][i].template get<string>());
    }
    gameState.AllMovesInGame = tempAllMovesInGame;

    this->blackKing = gameState.blackKing;
    this->whiteKing = gameState.whiteKing;
    this->PawnOnAisleCoordinates = gameState.PawnOnAisleCoordinates;
    this->enPassantTargetSquare = gameState.enPassantTargetSquare;
    this->ChessboardIsInverted = gameState.ChessboardIsInverted;
    this->WhoseMove = gameState.WhoseMove;
    this->IsTakingOnAisleActivated = gameState.IsTakingOnAisleActivated;
    this->IsTakingOnAisleUsed = gameState.IsTakingOnAisleUsed;
    this->WhoHasMoved = gameState.WhoHasMoved;
    this->CurrentGameMode = gameState.CurrentGameMode;
    this->PlayerColor = gameState.PlayerColor;
    this->LevelOfDifficulty = gameState.LevelOfDifficulty;

    for (int i = 0; i < BOARD_SIZE; ++i)
    {
        for (int j = 0; j < BOARD_SIZE; ++j){
            this->board[i][j] = gameState.board[i][j];
        }
    }

    for (int i = 0; i < NUMBER_OF_EATEN_FIGURES; ++i)
    {
        this->EatenFigures[i] = gameState.EatenFigures[i];
    }

    this->AllMovesInGame = gameState.AllMovesInGame;

    return true;
}

json SavedGameState::toJson() const
{
    json j = {
        {
            {
                "blackKing", {
                    {"x", blackKing.x},
                    {"y", blackKing.y},
                }
            },
            {
                "whiteKing", {
                    {"x", whiteKing.x},
                    {"y", whiteKing.y},
                }
            },
            {
                "PawnOnAisleCoordinates", {
                    {"x", PawnOnAisleCoordinates.x},
                    {"y", PawnOnAisleCoordinates.y},
                }
            },
            {
                "enPassantTargetSquare", {
                    {"x", enPassantTargetSquare.x},
                    {"y", enPassantTargetSquare.y},
                }
            },
            {"ChessboardIsInverted", ChessboardIsInverted},
            {"WhoseMove", WhoseMove},
            {"IsTakingOnAisleActivated", IsTakingOnAisleActivated},
            {"IsTakingOnAisleUsed", IsTakingOnAisleUsed},
            {"WhoHasMoved", WhoHasMoved},
            {"CurrentGameMode", CurrentGameMode},
            {"PlayerColor", PlayerColor},
            {"LevelOfDifficulty", LevelOfDifficulty},
            {"board", board},
            {"EatenFigures", EatenFigures},
            {"AllMovesInGame", AllMovesInGame},
        }
    };

    return j[0];
}
