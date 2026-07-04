#include <iostream>
#include "Board.h"
#include "moveValidations.h"
using namespace std;
void Board::initialize(){
    pieces[0]={{0,0},'R','b',false}; pieces[8]={{1,0},'P','b',false};
    pieces[1]={{0,1},'N','b',false}; pieces[9]={{1,1},'P','b',false};
    pieces[2]={{0,2},'B','b',false}; pieces[10]={{1,2},'P','b',false};
    pieces[3]={{0,3},'Q','b',false}; pieces[11]={{1,3},'P','b',false};
    pieces[4]={{0,4},'K','b',false}; pieces[12]={{1,4},'P','b',false};
    pieces[5]={{0,5},'B','b',false}; pieces[13]={{1,5},'P','b',false};
    pieces[6]={{0,6},'N','b',false}; pieces[14]={{1,6},'P','b',false};
    pieces[7]={{0,7},'R','b',false}; pieces[15]={{1,7},'P','b',false};

    pieces[16]={{7,0},'r','w',false}; pieces[24]={{6,0},'p','w',false};
    pieces[17]={{7,1},'n','w',false}; pieces[25]={{6,1},'p','w',false};
    pieces[18]={{7,2},'b','w',false}; pieces[26]={{6,2},'p','w',false};
    pieces[19]={{7,3},'q','w',false}; pieces[27]={{6,3},'p','w',false};
    pieces[20]={{7,4},'k','w',false}; pieces[28]={{6,4},'p','w',false};
    pieces[21]={{7,5},'b','w',false}; pieces[29]={{6,5},'p','w',false};
    pieces[22]={{7,6},'n','w',false}; pieces[30]={{6,6},'p','w',false};
    pieces[23]={{7,7},'r','w',false}; pieces[31]={{6,7},'p','w',false};

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
void Board::printBoard(bool t){
    cout<<"\n    a b c d e f g h \n";
    cout<<"  +-----------------+\n";
    for (int i = 0; i < 8; i++)
    {   cout<<8-i<<" | ";
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j]==nullptr){cout<<'.'<<' ';}
            else {cout<<board[i][j]->type<<' ';}
        }
        cout<<'|';
        if(i==0){cout<<("  White captured :"+printcaptW())<<endl;}
        else if(i==2){cout<<("  Black captured :"+printcaptB())<<endl;}
        else if(i==4){cout <<"  Turn: "<<(t ? "White" : "Black")<<endl;}
        else if(i==6){cout<<("  Last Move: "+getlastmove())<<endl;}
        else cout<<endl;
    }
    cout<<"  +-----------------+\n";
    cout<<"    a b c d e f g h \n";
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


        return true;
}

void Board::movepiece(cell from,cell to){
    moves m;
    m.from=from;
    m.to=to;
    m.movedpiece=board[from.row][from.col];
    m.capturedpiece=nullptr;
    m.capt=false;
    if(!isEmpty(to)){
        cout<<board[to.row][to.col]->type<<" of team "<<board[to.row][to.col]->team<<" has been captured!!\n";
        capturedpieces.push_back(board[to.row][to.col]);
        m.capturedpiece=board[to.row][to.col];
        m.capt=true;
    }
    movehistory.push_back(m);

    board[to.row][to.col]=board[from.row][from.col];
    board[from.row][from.col]=nullptr;

    board[to.row][to.col]->coords={to.row,to.col};
    board[to.row][to.col]->hasMoved=true;
}

bool Board::isEmpty(cell sq){
    if(board[sq.row][sq.col]==nullptr)return true;
    return false;
}

Pieces* Board::getpiece(int r,int c){
    return board[r][c];
}

Pieces* Board::getlastmovedpiece(){
    if(movehistory.empty())return nullptr;
    return movehistory.back().movedpiece;
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

bool Board::undoMove(){
    if(movehistory.empty())return false;
    else{
        int r,c;
        r=movehistory.back().from.row;
        c=movehistory.back().from.col;
        board[r][c]=board[movehistory.back().to.row][movehistory.back().to.col];
        board[r][c]->coords={r,c};
        board[r][c]->hasMoved=false;

        if(movehistory.back().capt){
        board[movehistory.back().to.row][movehistory.back().to.col]=capturedpieces.back();
        capturedpieces.pop_back();
       }
       else board[movehistory.back().to.row][movehistory.back().to.col]=nullptr;
       movehistory.pop_back();
       for(moves m:movehistory){if(m.movedpiece==board[r][c]) board[r][c]->hasMoved=true;}
    }
   return true;
}

string Board::getlastmove(){
    string s="";
    if(movehistory.empty())return "None";
    s+=char('a'+movehistory.back().from.col);
    s+=char('8'-movehistory.back().from.row);
    s+=" --> ";
    s+=char('a'+movehistory.back().to.col);
    s+=char('8'-movehistory.back().to.row);
    return s;
}

int main(){
    Board b;
    b.initialize();
    b.printBoard(true);
    
    cell from,to;
    bool p,whiteturn=true;
    string inp;
    while(true){
        getline(cin,inp);
        system("cls");
        if(inp=="0")exit(0);
        // if(inp=="1")b.printcapt();
        if(inp=="2"){
            if(b.undoMove())whiteturn=!whiteturn;
            else cout<<"No moves yet\n";
        }
        if(!b.parser(inp,from,to)){cout<<"Invalid input\n";}
        else if(b.isEmpty(from)){ cout << "No piece selected\n";}
        else if(whiteturn && b.getTeam(from) != 'w'){cout << "It's White's turn\n";}
        else if(!whiteturn && b.getTeam(from) != 'b'){cout << "It's Black's turn\n";}
        else if(!moveValidation(*(b.getpiece(from.row,from.col)),{to.row,to.col},b)){ cout << "That piece can't move like that\n";}
        else{
            b.movepiece(from,to);
            whiteturn=!whiteturn;
        }
        
        b.printBoard(whiteturn);

    }
}
