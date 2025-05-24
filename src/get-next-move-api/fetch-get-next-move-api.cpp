#ifdef __EMSCRIPTEN__

#include <nlohmann/json.hpp>
#include "fetch-get-next-move-api.h"

using json = nlohmann::json;

const string URL = "https://stockfish.online/api/s/v2.php";

string FetchGetNextMoveApi::get(const string& fen, int levelOfDifficulty)
{
    const string ERROR = "error";
    auto depth = to_string(levelOfDifficulty >= 0 && levelOfDifficulty <= 2 ? (levelOfDifficulty + 1) * 4 : 12);

    printf("Надсилаємо запит на %s для отримання найкращого ходу.\n", URL.c_str());
    puts("Параметри запиту:");
    printf("fen: \"%s\".\n", fen.c_str());
    printf("depth: \"%s\".\n", depth.c_str());

    return ERROR;
}

#endif // __EMSCRIPTEN__
