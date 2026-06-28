#include "Coords.h"
#ifndef t_PIECES
#define t_PIECES
class Pieces
{
    private:
    Coords coords;
    char type;
    char team;

    public:
    char getType();
    char setType();
    char getTeam();
    Coords getCoords();
    Coords setCoords(Coords);
};
#endif