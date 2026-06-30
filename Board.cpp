#include <iostream>
#include "Board.h"
#include "moveValidations.h"
using namespace std;
void Board::initialize(){
    pieces[0]={{0,0},'R','b'}; pieces[8]={{1,0},'P','b'};
    pieces[1]={{0,1},'N','b'}; pieces[9]={{1,1},'P','b'};
    pieces[2]={{0,2},'B','b'}; pieces[10]={{1,2},'P','b'};
    pieces[3]={{0,3},'Q','b'}; pieces[11]={{1,3},'P','b'};
    pieces[4]={{0,4},'K','b'}; pieces[12]={{1,4},'P','b'};
    pieces[5]={{0,5},'B','b'}; pieces[13]={{1,5},'P','b'};
    pieces[6]={{0,6},'N','b'}; pieces[14]={{1,6},'P','b'};
    pieces[7]={{0,7},'R','b'}; pieces[15]={{1,7},'P','b'};

    pieces[16]={{7,0},'r','w'}; pieces[24]={{6,0},'p','w'};
    pieces[17]={{7,1},'n','w'}; pieces[25]={{6,1},'p','w'};
    pieces[18]={{7,2},'b','w'}; pieces[26]={{6,2},'p','w'};
    pieces[19]={{7,3},'q','w'}; pieces[27]={{6,3},'p','w'};
    pieces[20]={{7,4},'k','w'}; pieces[28]={{6,4},'p','w'};
    pieces[21]={{7,5},'b','w'}; pieces[29]={{6,5},'p','w'};
    pieces[22]={{7,6},'n','w'}; pieces[30]={{6,6},'p','w'};
    pieces[23]={{7,7},'r','w'}; pieces[31]={{6,7},'p','w'};

    board[0][0]=&pieces[0]; board[7][0]=&pieces[16]; 
    board[0][1]=&pieces[1]; board[7][1]=&pieces[17]; 
    board[0][2]=&pieces[2]; board[7][2]=&pieces[18]; 
    board[0][3]=&pieces[3]; board[7][3]=&pieces[19]; 
    board[0][4]=&pieces[4]; board[7][4]=&pieces[20]; 
    board[0][5]=&pieces[5]; board[7][5]=&pieces[21]; 
    board[0][6]=&pieces[6]; board[7][6]=&pieces[22]; 
    board[0][7]=&pieces[7]; board[7][7]=&pieces[23]; 
    board[1][0]=&pieces[8]; board[6][0]=&pieces[24]; 
    board[1][1]=&pieces[9]; board[6][1]=&pieces[25]; 
    board[1][2]=&pieces[10]; board[6][2]=&pieces[26]; 
    board[1][3]=&pieces[11]; board[6][3]=&pieces[27]; 
    board[1][4]=&pieces[12]; board[6][4]=&pieces[28]; 
    board[1][5]=&pieces[13]; board[6][5]=&pieces[29]; 
    board[1][6]=&pieces[14]; board[6][6]=&pieces[30]; 
    board[1][7]=&pieces[15]; board[6][7]=&pieces[31]; 

    board[2][0]=nullptr; board[4][0]=nullptr; 
    board[2][1]=nullptr; board[4][1]=nullptr; 
    board[2][2]=nullptr; board[4][2]=nullptr; 
    board[2][3]=nullptr; board[4][3]=nullptr; 
    board[2][4]=nullptr; board[4][4]=nullptr; 
    board[2][5]=nullptr; board[4][5]=nullptr; 
    board[2][6]=nullptr; board[4][6]=nullptr; 
    board[2][7]=nullptr; board[4][7]=nullptr; 
    board[3][0]=nullptr; board[5][0]=nullptr; 
    board[3][1]=nullptr; board[5][1]=nullptr; 
    board[3][2]=nullptr; board[5][2]=nullptr; 
    board[3][3]=nullptr; board[5][3]=nullptr; 
    board[3][4]=nullptr; board[5][4]=nullptr; 
    board[3][5]=nullptr; board[5][5]=nullptr; 
    board[3][6]=nullptr; board[5][6]=nullptr; 
    board[3][7]=nullptr; board[5][7]=nullptr; 
}

void Board::print(){
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j]==nullptr){cout<<'.'<<' ';}
            else {cout<<board[i][j]->type<<' ';}
        }
        cout<<endl;
    }
    
}

bool Board::parser(string inp,cell &from,cell& to){
        if(inp.length()!=5)return false;
        inp[0]=tolower(inp[0]);
        inp[3]=tolower(inp[3]);
        if(inp[2]!=' ')return false;
        if(inp[0]<'a'||inp[0]>'h')return false;
        if(inp[3]<'a'||inp[3]>'h')return false;
        if(inp[1]<'1'||inp[1]>'8')return false;
        if(inp[4]<'1'||inp[4]>'8')return false;

        from.col=inp[0]-'a';
        from.row='8'-inp[1];

        to.col=inp[3]-'a';
        to.row='8'-inp[4];

        // cout<<from.col<<from.row<<"to"<<to.col<<to.row<<endl;
        return true;
}

void Board::movepiece(cell from,cell to){
    moves m;
    m.from=from;
    m.to=to;
    m.movedpiece=board[from.row][from.col];
    m.capturedpiece=nullptr;
    if(!isEmpty(to)){
        cout<<board[to.row][to.col]->type<<" of team "<<board[to.row][to.col]->team<<" has been captured!!\n";
        capturedpieces.push_back(board[to.row][to.col]);
        m.capturedpiece=board[to.row][to.col];
    }
    movehistory.push_back(m);

    board[to.row][to.col]=board[from.row][from.col];
    board[from.row][from.col]=nullptr;

    board[to.row][to.col]->coords={to.row,to.col};
}

bool Board::isEmpty(cell sq){
    if(board[sq.row][sq.col]==nullptr)return true;
    return false;
}

Pieces* Board::getpiece(int x,int y){
    return board[x][y];
}
// bool Board::isBlack(char c){
//     if (c!='.'&&isupper(c))return true;
//     return false;
// }

// bool Board::isWhite(char c){
//     if (c!='.'&&islower(c))return true;
//     return false;
// }

char Board::getTeam(cell sq){
    if(board[sq.row][sq.col]==nullptr)return 'E';
    return board[sq.row][sq.col]->team;  
}

// void Board::printcapt(){
//     for(Pieces* p:capturedpieces){cout<<p->team<<" "<<p->type<<endl;}
// }

int main(){
    Board b;
    b.initialize();
    b.print();

    cell from,to;
    bool p,whiteturn=true;
    string inp;
    while(true){
     
        getline(cin,inp);
        if(inp=="0")exit;
        // if (inp=="1")
        // {
        //     b.printcapt();
        // } 
        if(!b.parser(inp,from,to)){cout<<"Invalid input\n";}

        else if(whiteturn&&!b.isEmpty(from)&&b.getTeam(from)=='w'&&moveValidation(*(b.getpiece(from.row,from.col)),{to.row,to.col},b)){
            b.movepiece(from,to);
            whiteturn=!whiteturn;
        }

        else if(!whiteturn&&!b.isEmpty(from)&&b.getTeam(from)=='b'&&moveValidation(*(b.getpiece(from.row,from.col)),{to.row,to.col},b)){
            b.movepiece(from,to);
            whiteturn=!whiteturn;
        }
        else cout<<"Cannot move other colours piece\n";
        b.print();
        cout<<endl<<endl;


    }
}
   