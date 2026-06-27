#include<string>
using namespace std;
typedef struct cell
{
        int col;
        int row;
}cell;

class Board
{
private:
        char board[8][8];


public:
        void initialize();
        void print();
        bool parser(string,cell&,cell&);
        void movepiece(cell,cell);
        
        
        bool isEmpty(cell);
        bool isWhite(char);
        bool isBlack(char);
};
