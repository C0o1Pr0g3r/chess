#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string>
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
#include "connector.hpp"
#include "app-state.h"
#include "game-save-api/native-game-save-api.h"
#include "get-next-move-api/stockfish-online-get-next-move-api.h"

using namespace std;
using namespace sf;

int main()
{
    AppState appState(new NativeGameSaveApi(), new StockfishOnlineGetNextMoveApi());
    auto& window = appState.window;

    CreationOfObjects(appState);

    char chessEngine[29] = "stockfish_20011801_32bit.exe";
    ConnectToEngine(chessEngine);

    SetDefaultGameSettings(appState, true);

    auto savedGameState = appState.gameSaveApi->restore();
    if (get<0>(savedGameState))
    {
        appState.IsThereSavedGame = true;
        appState.WhoHasMoved = !appState.WhoseMove;
        appState.setStoredGameState(get<1>(savedGameState));
        ChangeGameSettings(appState);
    }

    puts("Ініціалізація програми завершена.");

    while (window.isOpen())
    {
        EventChecking(appState);
        HandleApp(appState);
        DrawApp(appState);
    }

    CloseConnection();

    return 0;
}
