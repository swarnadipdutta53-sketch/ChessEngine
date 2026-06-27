#include "Coords.h"

Coords encoder(char* move)
{
    Coords out;
    int mapx[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    int mapy[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    int i = 0;
    while(move[i] != '\0')
    {
        
        if(i == 0)
            out.x = mapx[i+1];
        else if(i == 1)
            out.y = mapy[i+1];
        else if(i > 1 || ((i == 0)&&(mapx[i+1] != move[i])) || ((i == 0)&&(mapy[i+1] != move[i]))) // INVALID CHAR AND OVERFLOW
        {
            out.x = 0; 
            out.y = 0;
        }
    }
    return out;
}

char* decoder(Coords coords)
{
    int map[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    char out[3];
    out[0] = map[coords.x - 1];
    out[1] = map[coords.y - 1];
    out[2] = '\0';
    return out;
}