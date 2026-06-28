#ifndef t_COORDS
#define t_COORDS

#include <stdio.h>
typedef struct Coords
{
    int x;
    int y;
}Coords;

Coords encoder(char*);
char* decoder(Coords);
#endif