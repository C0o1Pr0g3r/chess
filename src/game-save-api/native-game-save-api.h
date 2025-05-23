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

    bool save(const SavedGameState& gameState) override;
    tuple<bool, SavedGameState> restore() override;

    virtual ~NativeGameSaveApi() {}
};

#endif // NATIVE_GAME_SAVE_API_H_INCLUDED
