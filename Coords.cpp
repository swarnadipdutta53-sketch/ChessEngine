#include <stdio.h>
#include "Coords.h"

typedef struct Coords
{
    int x;
    int y;
}Coords;

Coords encoder(char* move)
{
    Coords out;
    int mapx[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    int mapy[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    int i = 0;
    while(move[i] != '\0')
    {
        
        if(i == 0)
            out.x = mapx[i];
        else if(i == 1)
            out.y = mapy[i];
        else if(i > 1 || ((i == 0)&&(mapx[i] != move[i])) || ((i == 0)&&(mapy[i] != move[i]))) // handling overflow in input stream
        {
            out.x = 0; 
            out.y = 0;
        }
    }
    return out;
}

char* decoder(Coords)
{
    int map[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    char* out;

}