#ifdef __EMSCRIPTEN__

#ifndef STOCKFISH_ONLINE_GET_NEXT_MOVE_API_H_INCLUDED
#define STOCKFISH_ONLINE_GET_NEXT_MOVE_API_H_INCLUDED

#include <string>
#include "interface.h"

using namespace std;

class FetchGetNextMoveApi: public GetNextMoveApi
{
public:
    string get(const string& fen, int levelOfDifficulty) override;

    virtual ~FetchGetNextMoveApi() {}
};

#endif // STOCKFISH_ONLINE_GET_NEXT_MOVE_API_H_INCLUDED

#endif // __EMSCRIPTEN__
