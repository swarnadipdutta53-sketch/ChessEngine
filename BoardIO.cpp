#include "BoardIO.h"
using namespace std;
bool parser(string inp, Coords &from, Coords &to)
{
    char ch;
    int tempOrds, scanX = 0, scanY = -1; // X scans source, Y scans destination
    from = {-1, -1}; to = {-1, -1};
    for(auto len = inp.begin(); len != inp.end(); ++len)
    {
        if(scanY == 0) scanX = -1; // stop source scanning, start destination scanning
        ch = tolower(*len);
        if(ch == ' ') continue;
        // coordinate encoding
        if(ch >= '1' && ch <= '8') tempOrds = '8' - ch;   
        else if(ch >= 'a' && ch <= 'h') tempOrds = ch - 'a';   
        else return false;
        if(scanX < 2 && scanX >= 0)
        {
            if(scanX == 0 && ch >= 'a' && ch <= 'h') from.y = tempOrds;
            else if(scanX == 1 && ch >= '1' && ch <= '8')
            {
                from.x = tempOrds;
                scanY = 0;
            }
            else return false;
            scanX++;
        }
        else if(scanY >= 0 && scanY < 2)
        {
            if(scanY == 0 && ch >= 'a' && ch <= 'h') to.y = tempOrds;
            else if(scanY == 1 && ch >= '1' && ch <= '8') to.x = tempOrds;
            else return false;
            scanY++;
        }
        else return false; // extra characters
    }
    if(from.x != -1 && from.y != -1 &&
       to.x != -1 && to.y != -1)
        return true;
    return false;
}   
