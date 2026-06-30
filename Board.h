#ifndef BOARD_H
#define BOARD_H

#include<string>
#include "pieces.h"
#include<vector>
using namespace std;
typedef struct cell
{
        int col;
        int row;
}cell;

typedef struct moves
{
        cell from;
        cell to;

        Pieces* movedpiece;
        Pieces* capturedpiece;
}moves;

class Board
{
private:
        Pieces pieces[32];
        Pieces* board[8][8];

        vector<Pieces*> capturedpieces;
        vector<moves> movehistory;

public:
        
        void initialize();
        void print();
        bool parser(string,cell&,cell&);
        void movepiece(cell,cell);
        char getTeam(cell);
        
        bool isEmpty(cell);
        Pieces* getpiece(int,int);
        void printcapt();
        // bool isWhite(char);
        // bool isBlack(char);
};

#endif