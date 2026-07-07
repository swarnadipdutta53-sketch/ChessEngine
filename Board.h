#ifndef BOARD_H
#define BOARD_H

#include<string>
#include<vector>
using namespace std;
typedef struct Coords
{
    int x;
    int y;
}Coords;

typedef struct Pieces
{
    Coords coords;
    char type;
    char team; 
    bool hasMoved;
    bool alive;
}Pieces;

enum class MoveType
 {
     EN_PASSANT, // enpassant
     CASTLING, // castling
     GENERAL, // general valid
     PROMOTION, // not valid
};

typedef struct moves
{
        Coords from;
        Coords to;

        Pieces* movedpiece;
        Pieces* capturedpiece;
        bool capt;
        MoveType t;
}moves;



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
        bool parser(string,Coords&,Coords&);
        void movepiece(Coords,Coords,MoveType);
        char getTeam(Coords);
        
        bool isEmpty(Coords);
        Pieces* getpiece(int,int);
        string printcaptW();
        string printcaptB();
        bool undoMove();
        string getlastmove();
        Pieces* getlastmovedpiece();

        vector<moves> generateLegalMoves(Pieces*); 
        vector<moves> generateAllLegalMoves(char); 
        vector<moves> generatePseudoLegalMoves(Pieces*); 
        bool isattacked(Coords,char);
        bool canattack(Coords,Pieces*);
};

#endif