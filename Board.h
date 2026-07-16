#ifndef BOARD_H
#define BOARD_H
#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<cctype>
#include "limits.h" 
#include <chrono>
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
     PROMOTION, // promotion
     INVALID // not valid
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

        bool whiteTurn=true;

public:
        
        void initialize();
        void printBoard();  //all defined in Board.cpp
        void makeMove(moves);
        bool undoMove();
        bool getTurn();
        bool setTurn(char);
        void FlipTurn();
        
        bool isEmpty(Coords);
        Pieces* getpiece(int,int);
        Pieces* getlastmovedpiece() const;
        Pieces* getking(char);                 //all defined in Helper.cpp
        char getTeam(Coords);
        string printcaptW();
        string printcaptB();
        string getlastmove();
        const vector<Pieces*>& getWhitePieces() const;
        const vector<Pieces*>& getBlackPieces() const;

        // move generation (pseudolegal + legal)
        vector<moves> generatePseudoLegalMovesKing(Pieces*) const;
        vector<moves> generatePseudoLegalMovesKnight(Pieces*) const;
        vector<moves> generatePseudoLegalMovesRook(Pieces*) const;
        vector<moves> generatePseudoLegalMovesPawn(Pieces*) const;
        vector<moves> generatePseudoLegalMovesBishop(Pieces*) const;
        vector<moves> generateLegalMoves(Pieces*); 
        vector<moves> generateAllLegalMoves(char); 
        vector<moves> generatePseudoLegalMoves(Pieces*) const; 
        vector<moves> generateAllPseudoLegalMoves(char) const;
        bool isAttacked(Pieces*);
        bool canAttack(Coords,Pieces*);
        bool isCellAttacked(Coords, char);
        
        long long perft(int depth, char team);

        void overWrite();


        bool loadFEN(const string&);
        void clearBoard();
        bool loadPieces(string);



};
// move validations (only pseudolegal)
MoveType moveValidation(Pieces, Coords, Board&);
MoveType moveValidationRook(int, int, Coords, Board&);
MoveType moveValidationBishop(int, int, Coords, Board&);
MoveType moveValidationKnight(int, int, Coords, Board&, Pieces);
MoveType moveValidationKing(int, int, Coords, Board&);
#endif