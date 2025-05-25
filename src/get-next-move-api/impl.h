#ifndef STOCKFISH_ONLINE_GET_NEXT_MOVE_API_H_INCLUDED
#define STOCKFISH_ONLINE_GET_NEXT_MOVE_API_H_INCLUDED

#include <string>
#include "interface.h"

using namespace std;

class GetNextMoveApiImpl: public GetNextMoveApi
{
private:
    bool currentProvider;
public:
    string get(const string& fen, int levelOfDifficulty) override;
    void toggleProvider() override;

    GetNextMoveApiImpl()
    :
        currentProvider(false)
    {}

    virtual ~GetNextMoveApiImpl() {}
};

#endif // STOCKFISH_ONLINE_GET_NEXT_MOVE_API_H_INCLUDED
