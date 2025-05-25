#include <nlohmann/json.hpp>
#include "impl.h"

using json = nlohmann::json;

#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
EM_ASYNC_JS(char*, getBestMoveWithStockfishOnline, (const char* url, const char* fen, const char* depth), {
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

EM_ASYNC_JS(char*, getBestMoveWithChessApi, (const char* url, const char* fen, int depth), {
    const ERROR = stringToNewUTF8("error");

    const response = await fetch(UTF8ToString(url), {
        method: "POST",
        headers: {
            "Content-Type": "application/json"
        },
        body: JSON.stringify({
            fen: UTF8ToString(fen),
            depth
        })
    });
    if (!response.ok) return ERROR;

    const data = await response.json();

    const move = data.move;
    if (typeof move !== "string") return ERROR;

    console.log("Запит успішно виконано. Результат:", JSON.stringify(data));

    return stringToNewUTF8(move);
});
#else
    #include <cpr/cpr.h>
#endif // __EMSCRIPTEN__

const string STOCKFISH_ONLINE_URL = "https://stockfish.online/api/s/v2.php";
const string CHESS_API_URL = "https://chess-api.com/v1";

const string ERROR = "error";


string getWithStockfishOnline(const string& fen, const string& depth)
{
#if defined(__EMSCRIPTEN__)
    auto data = getBestMoveWithStockfishOnline(STOCKFISH_ONLINE_URL.c_str(), fen.c_str(), depth.c_str());
    string dataAsString = data;
    free(data);

    return dataAsString;
#else
    cpr::Response r = cpr::Get(cpr::Url{STOCKFISH_ONLINE_URL},
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

string getWithChessApi(const string& fen, int depth)
{
#if defined(__EMSCRIPTEN__)
    auto data = getBestMoveWithChessApi(CHESS_API_URL.c_str(), fen.c_str(), depth);
    string dataAsString = data;
    free(data);

    return dataAsString;
#else
    json j = {
        {"fen", fen},
        {"depth", depth},
    };
    cpr::Response r = cpr::Post(cpr::Url{CHESS_API_URL},
                                cpr::Header{{"Content-Type", "application/json"}},
                                cpr::Body{j.dump()});

    if (r.status_code != 200) {
        return ERROR;
    }
    else
    {
        auto data = json::parse(r.text);
        if (!(data.contains("move") && data["move"].is_string())) return ERROR;
        auto move = data["move"].template get<string>();

        printf("Запит успішно виконано. Результат: \"%s\".\n", r.text.c_str());

        return move;
    }
#endif // __EMSCRIPTEN__
}

string GetNextMoveApiImpl::get(const string& fen, int levelOfDifficulty)
{
    auto depth = levelOfDifficulty >= 0 && levelOfDifficulty <= 2 ? (levelOfDifficulty + 1) * 4 : 12;

    auto URL = this->currentProvider ? CHESS_API_URL : STOCKFISH_ONLINE_URL;

    printf("Надсилаємо запит на %s для отримання найкращого ходу.\n", URL.c_str());
    puts("Параметри запиту:");
    printf("fen: \"%s\".\n", fen.c_str());
    printf("depth: \"%d\".\n", depth);

    return this->currentProvider ? getWithChessApi(fen, depth) : getWithStockfishOnline(fen, to_string(depth).c_str());
}

void GetNextMoveApiImpl::toggleProvider()
{
    this->currentProvider = !this->currentProvider;
}
