#include<string>
#include "pieces.h"
using namespace std;
typedef struct cell
{
        int col;
        int row;
}cell;

class Board
{
private:
        Pieces pieces[32];
        Pieces* board[8][8];
public:
        
        void initialize();
        void print();
        bool parser(string,cell&,cell&);
        void movepiece(cell,cell);
        char getTeam(cell);
        
        bool isEmpty(cell);
        Pieces* getpiece(int,int);
        // bool isWhite(char);
        // bool isBlack(char);
};
