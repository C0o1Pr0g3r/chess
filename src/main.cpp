#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string>
#include <filesystem>
#include <thread>
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
#include "get-next-move-api/impl.h"

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
    #include <emscripten/html5.h>
#endif // __EMSCRIPTEN__

using namespace std;
namespace fs = filesystem;
using namespace sf;

void one_iter(void* userData) {
    auto appState = reinterpret_cast<AppState*>(userData);

    EventChecking(*appState);
    HandleApp(*appState);
    DrawApp(*appState);
}

int main(int argc, char *argv[])
{
    fs::path appRootDir;
#ifndef __EMSCRIPTEN__
    appRootDir /= argv[0];
    appRootDir = fs::absolute(appRootDir).parent_path();
#endif // __EMSCRIPTEN__

    GetNextMoveApi* getNextMoveApi = new GetNextMoveApiImpl();
    AppState appState(appRootDir, new NativeGameSaveApi(), getNextMoveApi);
    auto& window = appState.window;

    CreationOfObjects(appState);

    SetDefaultOptions(appState);
    SetDefaultGameSettings(appState, true);

    auto savedGameState = appState.gameSaveApi->restore(appState.appRootDir);
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

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(one_iter, &appState, 0, true);
#else
    const auto MILLISECONDS_PER_SECOND = 1000.0;
    const auto MAX_FPS = 60;
    Clock clock;

    while (window.isOpen())
    {
        one_iter(&appState);
        auto elapsedTime = clock.getElapsedTime();
        auto sleepTime = MILLISECONDS_PER_SECOND / MAX_FPS - elapsedTime.asMilliseconds();
        if (sleepTime > 0)
        {
            this_thread::sleep_for(std::chrono::duration<double, std::milli>(sleepTime));
        }
        clock.restart();
  }
#endif

    return 0;
}
