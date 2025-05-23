#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "stockfish-online-get-next-move-api.h"

using json = nlohmann::json;

const string URL = "https://stockfish.online/api/s/v2.php";

string StockfishOnlineGetNextMoveApi::get(const string& fen, int levelOfDifficulty)
{
    const string ERROR = "error";
    auto depth = to_string(levelOfDifficulty >= 0 && levelOfDifficulty <= 2 ? (levelOfDifficulty + 1) * 4 : 12);

    printf("Надсилаємо запит на %s для отримання найкращого ходу.\n", URL.c_str());
    puts("Параметри запиту:");
    printf("fen: \"%s\".\n", fen.c_str());
    printf("depth: \"%s\".\n", depth.c_str());

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
}
