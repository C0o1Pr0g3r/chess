#include <nlohmann/json.hpp>
#include "stockfish-online-get-next-move-api.h"

using json = nlohmann::json;

#if defined(__EMSCRIPTEN__)
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
#else
    #include <cpr/cpr.h>
#endif // __EMSCRIPTEN__

const string URL = "https://stockfish.online/api/s/v2.php";

string StockfishOnlineGetNextMoveApi::get(const string& fen, int levelOfDifficulty)
{
    const string ERROR = "error";
    auto depth = to_string(levelOfDifficulty >= 0 && levelOfDifficulty <= 2 ? (levelOfDifficulty + 1) * 4 : 12);

    printf("Надсилаємо запит на %s для отримання найкращого ходу.\n", URL.c_str());
    puts("Параметри запиту:");
    printf("fen: \"%s\".\n", fen.c_str());
    printf("depth: \"%s\".\n", depth.c_str());

#if defined(__EMSCRIPTEN__)
    auto data = getBestMove(URL.c_str(), fen.c_str(), depth.c_str());
    string dataAsString = data;
    free(data);

    return dataAsString;
#else
    cpr::Response r = cpr::Post(cpr::Url{URL},
                                cpr::Parameters{{"fen", fen}, {"depth", depth}});

    if (r.status_code != 200){
        return ERROR;
    }
    else
    {
        auto data = json::parse(r.text);
        if (!(data.contains("success") && data["success"].is_boolean() && data["success"].template get<bool>())) return ERROR;
        if (!(data.contains("bestmove") && data["bestmove"].is_string())) return ERROR;
        auto bestmove = data["bestmove"].template get<string>();

        printf("Запит успішно виконано. Результат: \"%s\".\n", r.text.c_str());

        return bestmove.substr(9, 4);
    }
#endif // __EMSCRIPTEN__
}

