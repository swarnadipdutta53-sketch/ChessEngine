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

bool Board::parser(string inp,cell &from,cell& to){
        inp[0]=tolower(inp[0]);
        inp[3]=tolower(inp[3]);
        if(inp.length()!=5)return false;
        if(inp[2]!=' ')return false;
        if(inp[0]<'a'||inp[0]>'h')return false;
        if(inp[3]<'a'||inp[3]>'h')return false;
        if(inp[1]<'1'||inp[1]>'8')return false;
        if(inp[4]<'1'||inp[4]>'8')return false;

        from.col=inp[0]-'a';
        from.row='8'-inp[1];

        to.col=inp[3]-'a';
        to.row='8'-inp[4];

        cout<<from.col<<from.row<<"to"<<to.col<<to.row<<endl;
        return true;
}



void Board::movepiece(cell from,cell to){
    board[to.row][to.col]=board[from.row][from.col];
    board[from.row][from.col]='.';
}
int main(){
    Board b;
    b.initialize();
    b.print();

    cell from,to;
    bool p;
    string inp;
    getline(cin,inp);
    if(!b.parser(inp,from,to)){cout<<"Invalid input\n";}
    else b.movepiece(from,to);
    b.print();
}