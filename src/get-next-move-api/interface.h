#ifndef GET_NEXT_MOVE_API_INTERFACE_H_INCLUDED
#define GET_NEXT_MOVE_API_INTERFACE_H_INCLUDED

#include <string>

using namespace std;

class GetNextMoveApi
{
public:
    virtual string get(const string& fen, int levelOfDifficulty) = 0;
    virtual void toggleProvider() = 0;

    virtual ~GetNextMoveApi() {}
};

#endif // GET_NEXT_MOVE_API_INTERFACE_H_INCLUDED
