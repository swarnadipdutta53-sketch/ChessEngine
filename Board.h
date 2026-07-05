#ifndef BOARD_H
#define BOARD_H

#include<string>
#include "Coords.h"
#include<vector>
using namespace std;
typedef struct square
{
        int row;
        int col;
}square;

typedef struct Pieces
{
    Coords coords;
    char type;
    char team; 
    bool hasMoved;
    bool alive;
}Pieces;

typedef struct moves
{
        square from;
        square to;

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
        Pieces* Whiteking;
        Pieces* Blackking;

        vector<Pieces*> capturedpieces;
        vector<moves> movehistory;
        vector<Pieces*> whitepieces;
        vector<Pieces*> blackpieces;

public:
        
        void initialize();
        void printBoard(bool);
        bool parser(string,square&,square&);
        void movepiece(square,square,ReturnType);
        char getTeam(square);
        
        bool isEmpty(square);
        Pieces* getpiece(int,int);
        string printcaptW();
        string printcaptB();
        bool undoMove();
        string getlastmove();
        Pieces* getlastmovedpiece();

        vector<moves> generateLegalMoves(Pieces*); 
        vector<moves> generateAllLegalMoves(char); 
        vector<moves> generatePseudoLegalMoves(Pieces*); 
        bool isattacked(square,char);
        bool canattack(square,Pieces*);
};

#endif