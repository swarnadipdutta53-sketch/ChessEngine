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
    int hasMoved;
    bool alive;
}Pieces;

enum class MoveType
 {
     EN_PASSANT, // enpassant
     CASTLING, // castling
     GENERAL, // general valid
     PROMOTION, // not valid
};

enum class PromotionType{
     QUEEN,
     ROOK,
     KNIGHT,
     BISHOP,
     NONE,
};

typedef struct moves
{
        Coords from;
        Coords to;
        
        Pieces* movedpiece;
        Pieces* capturedpiece=nullptr;
        MoveType movetype=MoveType::GENERAL;

        Pieces* auxiliarypiece=nullptr;
        PromotionType promotiontype=PromotionType::NONE;
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
        void printBoard(bool);  //all defined in Board.cpp
        void makeMove(moves);
        bool undoMove();
        
        
        bool isEmpty(Coords);
        Pieces* getpiece(int,int);
        Pieces* getlastmovedpiece();
        Pieces* getking(char);                 //all defined in Helper.cpp
        char getTeam(Coords);
        string printcaptW();
        string printcaptB();
        string getlastmove();
        const vector<Pieces*>& getWhitePieces() const;
        const vector<Pieces*>& getBlackPieces() const;

        
        vector<moves> generatePseudoLegalMovesKing(Pieces*);
        vector<moves> generatePseudoLegalMovesKnight(Pieces*);
        vector<moves> generatePseudoLegalMovesRook(Pieces*);
        vector<moves> generatePseudoLegalMovesPawn(Pieces*);
        vector<moves> generatePseudoLegalMovesBishop(Pieces*);
        vector<moves> generateLegalMoves(Pieces*); 
        vector<moves> generateAllLegalMoves(char); 
        vector<moves> generatePseudoLegalMoves(Pieces*); 
        bool isattacked(Coords,char);
        bool canattack(Coords,Pieces*);
        
};
#endif;