#include <iostream>
#include "Board.h"
using namespace std;
void Board::initialize(){
    
    board[0][0]='R';
    board[0][1]='N';
    board[0][2]='B';
    board[0][3]='Q';
    board[0][4]='K';
    board[0][5]='B';
    board[0][6]='N';
    board[0][7]='R';
    for(int i=0;i<8;i++){ board[1][i]='P';}

    for (int i = 2; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j]='.';
        }
        
    }

    
    for(int i=0;i<8;i++){ board[6][i]='p';}
    board[7][0]='r';
    board[7][1]='n';
    board[7][2]='b';
    board[7][3]='q';
    board[7][4]='k';
    board[7][5]='b';
    board[7][6]='n';
    board[7][7]='r';
    
}

void Board::print(){
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cout<<board[i][j]<<' ';
        }
        cout<<endl;
    }
    
}

void Board::parser(string inp,int &fc,int &fr,int &tc,int &tr){
        fc=inp[0]-'a';
        fr='8'-inp[1];

        tc=inp[3]-'a';
        tr='8'-inp[4];

        cout<<fc<<fr<<"to"<<tc<<tr;
}

void Board::movepiece(int fc,int fr,int tc,int tr){
    board[tr][tc]=board[fr][fc];
    board[fr][fc]='.';
}
int main(){
    Board b;
    b.initialize();
    b.print();

    int fc,fr,tc,tr;
    string inp;
    getline(cin,inp);
    b.parser(inp,fc,fr,tc,tr);
    b.movepiece(fc,fr,tc,tr);
    b.print();
}