#include <fstream>
#include <nlohmann/json.hpp>
#include "native-game-save-api.h"

using json = nlohmann::json;

auto FILE_PATH = "save.json";

bool NativeGameSaveApi::save(const SavedGameState& gameState)
{
    auto& blackKing = gameState.blackKing;
    auto& whiteKing = gameState.whiteKing;
    auto& PawnOnAisleCoordinates = gameState.PawnOnAisleCoordinates;
    auto& ChessboardIsInverted = gameState.ChessboardIsInverted;
    auto& WhoseMove = gameState.WhoseMove;
    auto& IsTakingOnAisleActivated = gameState.IsTakingOnAisleActivated;
    auto& IsTakingOnAisleUsed = gameState.IsTakingOnAisleUsed;
    auto& CurrentGameMode = gameState.CurrentGameMode;
    auto& PlayerColor = gameState.PlayerColor;
    auto& LevelOfDifficulty = gameState.LevelOfDifficulty;
    auto& board = gameState.board;
    auto& EatenFigures = gameState.EatenFigures;
    auto& AllMovesInGame = gameState.AllMovesInGame;

    ofstream out(FILE_PATH);

    if (out.is_open())
    {
        out << gameState.toJson().dump() << endl;
        out.close();

        return true;
    }
    else
    {
        fprintf(stderr, "Не вдалося відкрити файл для збереження даних гри.\n");
    }

    return false;
}

tuple<bool, SavedGameState> NativeGameSaveApi::restore()
{
    SavedGameState gameState;
    auto noGameState = make_tuple(false, gameState);

    ifstream in(FILE_PATH);

    if (!in.is_open())
    {
        fprintf(stderr, "Не вдалося відкрити файл, у якому збережено налаштування та стан гри.\n");
        return noGameState;
    }

    auto doesGameStateExist = gameState.fromJson(getJsonFromFile(in));
    in.close();

    if (!doesGameStateExist)
    {
        puts("У файлі збереження відсутні дані про збережену гру.");
        return noGameState;
    }
    else
    {
        puts("Файл збереження містить дані про збережену гру.");
        printf("Збережена гра: %d.\n", doesGameStateExist);
        printf("Координати чорного короля: (%d; %d).\n", gameState.blackKing.x, gameState.blackKing.y);
        printf("Координати білого короля: (%d; %d).\n", gameState.whiteKing.x, gameState.whiteKing.y);
        printf("Координати пішака на проході: (%d; %d).\n", gameState.PawnOnAisleCoordinates.x, gameState.PawnOnAisleCoordinates.y);
        printf("Дошку перевернуто: %d.\n", gameState.ChessboardIsInverted);
        printf("Чия черга робити хід: %d.\n", gameState.WhoseMove);
        printf("Взяття на проході активоване: %d.\n",gameState.IsTakingOnAisleActivated );
        printf("Взяття на проході використане: %d.\n", gameState.IsTakingOnAisleUsed);
        printf("Режим гри: %d.\n", gameState.CurrentGameMode);
        printf("Колір фігур гравця: %d.\n", gameState.PlayerColor);
        printf("Рівень складності: %d.\n", gameState.LevelOfDifficulty);
        puts("Шахова дошка:");

        for (int i = 0; i < LENGTH; i++)
        {
            for (int j = 0; j < LENGTH; j++)
                printf("%4d ", gameState.board[i][j]);
            putchar('\n');
        }

        puts("З'їдені фігури:");
        for (int i = 0; i < LENGTH; i++)
            printf("%2d", gameState.EatenFigures[i]);
        putchar('\n');

        string moves = "";
        for (size_t i = 0; i < gameState.AllMovesInGame.size(); ++i)
        {
            moves.append(gameState.AllMovesInGame[i]);
            if (i < gameState.AllMovesInGame.size() - 1)
            {
                moves.append(" ");
            }
        }
        printf("Всі ходи у грі: \"%s\".\n", moves.c_str());
    }

    return make_tuple(true, gameState);
}
