#include<iostream>
using namespace std;
class Board
{
private:
        char board[8][8];


public:
        void initialize();
        void print();
        void parser(string,int&,int&,int&,int&);
        void movepiece(int,int,int,int);
};
