#ifndef BOARD_H
#define BOARD_H

#include<string>
#include "pieces.h"
#include<vector>
using namespace std;
typedef struct cell
{
        int row;
        int col;
}cell;

typedef struct moves
{
        cell from;
        cell to;

        Pieces* movedpiece;
        Pieces* capturedpiece;
        bool capt;
}moves;

enum class ReturnType
{
     en_valid, // enpassant
     cas_valid, // castling
     gen_valid, // general valid
     prom_valid,
     invalid // not valid
};

class Board
{
private:
        Pieces pieces[32];
        Pieces* board[8][8];

        vector<Pieces*> capturedpieces;
        vector<moves> movehistory;

public:
        
        void initialize();
        void printBoard(bool);
        bool parser(string,cell&,cell&);
        void movepiece(cell,cell,ReturnType);
        char getTeam(cell);
        
        bool isEmpty(cell);
        Pieces* getpiece(int,int);
        string printcaptW();
        string printcaptB();
        bool undoMove();
        string getlastmove();
        Pieces* getlastmovedpiece();
        // bool isWhite(char);
        // bool isBlack(char);
};

#endif