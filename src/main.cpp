#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string>
#include <filesystem>
// #include <windows.h>
#include "global constants.h"
#include "move functions.h"
#include "checks.h"
#include "secondary functions.h"
#include "drawing functions.h"
#include "coordinate processing functions.h"
#include "backlight functions.h"
#include "button class.h"
#include "radio button class.h"
#include "drawn object class.h"
#include "label class.h"
#include "handling functions.h"
#include "app-state.h"
#include "game-save-api/native-game-save-api.h"

#if defined(__EMSCRIPTEN__)
#include "get-next-move-api/fetch-get-next-move-api.h"
#else
#include "get-next-move-api/stockfish-online-get-next-move-api.h"
#endif // __EMSCRIPTEN__

using namespace std;
namespace fs = filesystem;
using namespace sf;

int main(int argc, char *argv[])
{
    fs::path appRootDir;
#if defined(__EMSCRIPTEN__)
    GetNextMoveApi* getNextMoveApi = new FetchGetNextMoveApi();
#else
    appRootDir /= argv[0];
    appRootDir = fs::absolute(appRootDir).parent_path();
    GetNextMoveApi* getNextMoveApi = new StockfishOnlineGetNextMoveApi();
#endif // __EMSCRIPTEN__

    AppState appState(appRootDir, new NativeGameSaveApi(), getNextMoveApi);
    auto& window = appState.window;

    CreationOfObjects(appState);

    SetDefaultOptions(appState);
    SetDefaultGameSettings(appState, true);

    auto savedGameState = appState.gameSaveApi->restore();
    if (get<0>(savedGameState))
    {
        appState.IsThereSavedGame = true;
        appState.setStoredGameState(get<1>(savedGameState));
        ChangeGameSettings(appState);
    }

    puts("Ініціалізація програми завершена.");

#ifdef __EMSCRIPTEN__
    appState.ExitFromApp_button.SetEnabled(false);
#endif // __EMSCRIPTEN__

    while (window.isOpen())
    {
        EventChecking(appState);
        HandleApp(appState);
        DrawApp(appState);
    }


    return 0;
}
