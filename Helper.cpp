#include "Board.h"

//Contains all helper and getter functions

bool Board::isEmpty(Coords sq) const{
    if(board[sq.x][sq.y]==nullptr)return true;
    return false;
}

Pieces* Board::getpiece(int r, int c)const{
    return board[r][c];
}

Pieces* Board::getlastmovedpiece() const{
    if(movehistory.empty())return nullptr;
    return movehistory.back().movedpiece;
}

Pieces* Board::getking(char t){
    if(t=='w')return Whiteking;
    return Blackking;
}

char Board::getTeam(Coords sq) const{
    if(board[sq.x][sq.y]==nullptr)return 'E';
    return board[sq.x][sq.y]->team;
}

string Board::printcaptW(){
    string s=" ";
    for(Pieces* p:capturedpieces){
        if(p->team=='w'){
            s+=p->type;
            s+=' ';
        }
    }
     if(s==" ")return "None";
     return s;
}

string Board::printcaptB(){
    string s=" ";
    for(Pieces* p:capturedpieces){
        if(p->team=='b'){
            s+=p->type;
            s+=' ';
        }
    }
    if(s==" ")return "None";
    return s;
}

string Board::getlastmove(){
    string s="";
    if(movehistory.empty())return "None";
    s+=char('a'+movehistory.back().from.y);
    s+=char('8'-movehistory.back().from.x);
    s+=" --> ";
    s+=char('a'+movehistory.back().to.y);
    s+=char('8'-movehistory.back().to.x);
    return s;
}

const vector<Pieces*>& Board::getWhitePieces() const{
    return whitepieces;
}
const vector<Pieces*>& Board::getBlackPieces() const{
    return blackpieces;
}
bool Board::getTurn(){
    return whiteTurn;
}
bool Board::setTurn(char a){
    if(a=='w')whiteTurn=true;
    else if(a=='b')whiteTurn=false;
    else return false;
    return true;
}
void Board::FlipTurn(){
    whiteTurn=!whiteTurn;
}