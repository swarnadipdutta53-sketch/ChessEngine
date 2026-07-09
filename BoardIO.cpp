#include "BoardIO.h"

bool parser(string inp,Coords &from,Coords& to){
        if(inp.length()!=5)return false;
        inp[0]=tolower(inp[0]);
        inp[3]=tolower(inp[3]);
        if(inp[2]!=' ')return false;
        if(inp[0]<'a'||inp[0]>'h')return false;
        if(inp[3]<'a'||inp[3]>'h')return false;
        if(inp[1]<'1'||inp[1]>'8')return false;
        if(inp[4]<'1'||inp[4]>'8')return false;

        from.y=inp[0]-'a';
        from.x='8'-inp[1];

        to.y=inp[3]-'a';
        to.x='8'-inp[4];


        return true;
}