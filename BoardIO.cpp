#include "BoardIO.h"
#include<iostream>
// bool parser(string inp,Coords &from,Coords& to){
//         if(inp.length()!=5)return false;
//         inp[0]=tolower(inp[0]);
//         inp[3]=tolower(inp[3]);
//         if(inp[2]!=' ')return false;
//         if(inp[0]<'a'||inp[0]>'h')return false;
//         if(inp[3]<'a'||inp[3]>'h')return false;
//         if(inp[1]<'1'||inp[1]>'8')return false;
//         if(inp[4]<'1'||inp[4]>'8')return false;

//         from.y=inp[0]-'a';
//         from.x='8'-inp[1];

//         to.y=inp[3]-'a';
//         to.x='8'-inp[4];


//         return true;
// }
bool parser(string inp,Coords &from,Coords& to){
        char ch;
        int tempOrds;
        int scanX = 0, scanY = -1; // X is coords from and Y is coords to
        from.x = -1;
        from.y = -1;
        to.x = -1;
        to.y = -1;
        for(auto len = inp.begin(); len != inp.end(); ++len)
        {
                if(scanY == 0)
                        scanX = -1; // scanning of Y starts , X stops
                // check part and encoding
                ch = *len;
                if(ch == ' ')
                        continue;
                if(ch >= '1' && ch <= '8')
                        tempOrds = ch - '1';
                else if(ch >= 'a' && ch <= 'h')
                        tempOrds = ch - 'a';
                else
                        return false;
                // assignation
                if(scanX < 2 && scanX >= 0) // when X scanning is active
                {
                        if(scanX == 0 && ch >= 'a' && ch <= 'h')
                                from.x = tempOrds;
                        else if(scanX == 1 && ch >= '1' && ch <= '8')
                        {
                                scanY = 0;
                                from.y = tempOrds;
                        }
                        else 
                                return false; // invalid
                        scanX++;
                }
                else if(scanY >= 0 && scanY < 2) // when Y scanning is active
                {
                        if(scanY == 0 && ch >= 'a' && ch <= 'h')
                                to.x = tempOrds;
                        else if(scanY == 1 && ch >= '1' && ch <= '8')
                                to.y = tempOrds;
                        else 
                                return false; // invalid
                        scanY++;
                }
                else
                        return false; // invalid as more than 2 inputs for Y
        }
        if(from.x != -1 && from.y != -1 &&
        to.x != -1 && to.y != -1)
                return true;
        return false;
}
