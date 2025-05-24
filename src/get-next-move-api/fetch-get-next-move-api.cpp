#ifdef __EMSCRIPTEN__

#include <nlohmann/json.hpp>
#include "fetch-get-next-move-api.h"

using json = nlohmann::json;



#ifdef __EMSCRIPTEN__
#include <emscripten.h>

EM_ASYNC_JS(char*, getBestMove, (const char* url, const char* fen, const char* depth), {
    const ERROR = stringToNewUTF8("error");

    const query = new URLSearchParams();
    query.append("fen", UTF8ToString(fen));
    query.append("depth", UTF8ToString(depth));
    const response = await fetch([UTF8ToString(url), query.toString()].join("?"));
    if (!response.ok) return ERROR;

    const data = await response.json();
    if (!data.success) return ERROR;

    const bestmove = data.bestmove;
    if (typeof bestmove !== "string") return ERROR;

    console.log("Запит успішно виконано. Результат:", JSON.stringify(data));

    return stringToNewUTF8(bestmove.substring(9, 13));
});
#endif // __EMSCRIPTEN__

const string URL = "https://stockfish.online/api/s/v2.php";

string FetchGetNextMoveApi::get(const string& fen, int levelOfDifficulty)
{
    const string ERROR = "error";
    auto depth = to_string(levelOfDifficulty >= 0 && levelOfDifficulty <= 2 ? (levelOfDifficulty + 1) * 4 : 12);

    printf("Надсилаємо запит на %s для отримання найкращого ходу.\n", URL.c_str());
    puts("Параметри запиту:");
    printf("fen: \"%s\".\n", fen.c_str());
    printf("depth: \"%s\".\n", depth.c_str());

    auto data = getBestMove(URL.c_str(), fen.c_str(), depth.c_str());
    string dataAsString = data;
    free(data);

    return dataAsString;
}

#endif // __EMSCRIPTEN__
