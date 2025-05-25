#ifndef NATIVE_GAME_SAVE_API_H_INCLUDED
#define NATIVE_GAME_SAVE_API_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "../global constants.h"
#include "interface.h"

using namespace sf;
using namespace std;

class NativeGameSaveApi: public GameSaveApi
{
public:
    NativeGameSaveApi() {}

    bool save(const fs::path& appRootDir, const SavedGameState& gameState) override;
    tuple<bool, SavedGameState> restore(const fs::path& appRootDir) override;

    virtual ~NativeGameSaveApi() {}
};

#endif // NATIVE_GAME_SAVE_API_H_INCLUDED
