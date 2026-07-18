#include <iostream>
#include "Board.h"
using namespace std;
void Board::initialize(){
    pieces[0]={{0,0},'R','b',false,true}; pieces[8]={{1,0},'P','b',false,true};
    pieces[1]={{0,1},'N','b',false,true}; pieces[9]={{1,1},'P','b',false,true};
    pieces[2]={{0,2},'B','b',false,true}; pieces[10]={{1,2},'P','b',false,true};
    pieces[3]={{0,3},'Q','b',false,true}; pieces[11]={{1,3},'P','b',false,true};
    pieces[4]={{0,4},'K','b',false,true}; pieces[12]={{1,4},'P','b',false,true};
    pieces[5]={{0,5},'B','b',false,true}; pieces[13]={{1,5},'P','b',false,true};
    pieces[6]={{0,6},'N','b',false,true}; pieces[14]={{1,6},'P','b',false,true};
    pieces[7]={{0,7},'R','b',false,true}; pieces[15]={{1,7},'P','b',false,true};

    pieces[16]={{7,0},'r','w',false,true}; pieces[24]={{6,0},'p','w',false,true};
    pieces[17]={{7,1},'n','w',false,true}; pieces[25]={{6,1},'p','w',false,true};
    pieces[18]={{7,2},'b','w',false,true}; pieces[26]={{6,2},'p','w',false,true};
    pieces[19]={{7,3},'q','w',false,true}; pieces[27]={{6,3},'p','w',false,true};
    pieces[20]={{7,4},'k','w',false,true}; pieces[28]={{6,4},'p','w',false,true};
    pieces[21]={{7,5},'b','w',false,true}; pieces[29]={{6,5},'p','w',false,true};
    pieces[22]={{7,6},'n','w',false,true}; pieces[30]={{6,6},'p','w',false,true};
    pieces[23]={{7,7},'r','w',false,true}; pieces[31]={{6,7},'p','w',false,true};

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

    for(int i=0;i<16;i++){
        blackpieces.push_back(&pieces[i]);
    }
    for(int i=16;i<32;i++){
        whitepieces.push_back(&pieces[i]);
    }

    Whiteking=&pieces[20];
    Blackking=&pieces[4];

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

    CastlingRights=WK|WQ|BK|BQ;
    En_PassantTargetSquare={-1,-1};
}

void Board::overWrite(){
    
    for(int j=0;j<8;j++){if(j==0||j==3||j==4||j==7)continue; board[0][j]->alive=false;board[0][j]=nullptr;}
    for(int j=0;j<8;j++){board[1][j]->alive=false;board[1][j]=nullptr;}
    for(int j=0;j<8;j++){board[6][j]->alive=false;board[6][j]=nullptr;}
    for(int j=0;j<8;j++){if(j==0||j==3||j==4||j==7)continue; board[7][j]->alive=false;board[7][j]=nullptr;}
}

void Board::printBoard(){
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
        else if(i==4){cout <<"  Turn: "<<(whiteTurn ? "White" : "Black")<<endl;}
        else if(i==6){cout<<("  Last Move: "+getlastmove())<<endl;}
        else cout<<endl;
    }
    cout<<"  +-----------------+\n";
    cout<<"    a b c d e f g h \n";
}

void Board::makeMove(moves l){
    l.PrevCastlingRights=CastlingRights;
    l.PrevEn_Square=En_PassantTargetSquare;

    En_PassantTargetSquare={-1,-1};
    int fr=l.from.x,fc=l.from.y,tr=l.to.x,tc=l.to.y,ar,ac;
    char ps=board[fr][fc]->type;

    if(ps=='K'||ps=='k'){CastlingRights &= (ps=='k'? ~(WK|WQ):~(BK|BQ));}
    if(ps=='r'||ps=='R'){
        if(fr==0&&fc==7){CastlingRights &= ~BK;}
        else if(fr==7&&fc==7){CastlingRights &= ~WK;}
        else if(fr==0&&fc==0){CastlingRights &= ~BQ;}
        else if(fr==7&&fc==0){CastlingRights &= ~WQ;}
    }
    if(!(l.capturedpiece==nullptr)&&(l.capturedpiece->type=='r'||'R')&&(!l.capturedpiece->hasMoved)){
        int u=l.capturedpiece->coords.x;
        int v=l.capturedpiece->coords.y;
        if(u==0&&v==7){CastlingRights &= ~BK;}
        else if(u==7&&v==7){CastlingRights &= ~WK;}
        else if(u==0&&v==0){CastlingRights &= ~BQ;}
        else if(u==7&&v==0){CastlingRights &= ~WQ;}
    }

    board[tr][tc]=board[fr][fc];
    board[fr][fc]=nullptr;
    board[tr][tc]->coords={tr,tc};
    board[tr][tc]->hasMoved++;
    string s;

    switch(l.movetype)
    {
    case MoveType::GENERAL:
        if(l.capturedpiece!=nullptr){
            l.capturedpiece->alive=false;
            capturedpieces.push_back(l.capturedpiece);
        }
        break;
    
    case MoveType::EN_PASSANT:
        if(l.movedpiece->team=='w'){board[tr+1][tc]=nullptr;}
        else {board[tr-1][tc]=nullptr;}
        l.capturedpiece->alive=false;
        capturedpieces.push_back(l.capturedpiece);
        break;


    case MoveType::CASTLING:
        ar=l.auxiliarypiece->coords.x,ac=l.auxiliarypiece->coords.y;
        if(tc==6){board[fr][fc+1]=l.auxiliarypiece; l.auxiliarypiece->hasMoved++; board[ar][ac]=nullptr; l.auxiliarypiece->coords={fr,fc+1};}
        else{board[fr][fc-1]=l.auxiliarypiece; l.auxiliarypiece->hasMoved++; board[ar][ac]=nullptr; l.auxiliarypiece->coords={fr,fc-1};}
        break;

    case MoveType::PROMOTION:
        if(l.capturedpiece!=nullptr){
            l.capturedpiece->alive=false;
            capturedpieces.push_back(l.capturedpiece);
        }

        switch(l.promotiontype){

            case PromotionType::QUEEN:

                l.movedpiece->type = (l.movedpiece->team=='w') ? 'q' : 'Q';
                break;

            case PromotionType::ROOK:

                l.movedpiece->type = (l.movedpiece->team=='w') ? 'r' : 'R';
                break;

            case PromotionType::BISHOP:
                l.movedpiece->type = (l.movedpiece->team=='w') ? 'q' : 'Q';
                break;

            case PromotionType::KNIGHT:
                l.movedpiece->type = (l.movedpiece->team=='w') ? 'q' : 'Q';
                break;

            default:
                cout << "Promotion type not set!\n";
        }
        break;

    case MoveType::PawnDouble:
        En_PassantTargetSquare={(ps=='p'?fr-1:fr+1),fc};
        break;
        
    default: cout<<"Code should not reach here\n";
        break;
    }
   
    movehistory.push_back(l);
}

long long Board::perft(int depth, char team)
{
    if (depth == 0)
        return 1;

    long long nodes = 0;

    auto legalMoves = generateAllLegalMoves(team);

    char nextTeam = (team == 'w') ? 'b' : 'w';

    for (const moves &m : legalMoves)
    {
        makeMove(m);

        nodes += perft(depth - 1, nextTeam);

        undoMove();
    }

    return nodes;
}

bool Board::undoMove(){
    if(movehistory.empty())return false;
    else{
        moves m=movehistory.back();
        int fr=m.from.x,fc=m.from.y;
        int tr=m.to.x,tc=m.to.y;
        board[fr][fc]=board[tr][tc];
        board[fr][fc]->hasMoved--;
        board[fr][fc]->coords={fr,fc};
        board[tr][tc]=nullptr;

        if(m.capturedpiece!=nullptr){
            capturedpieces.back()->alive=true;
            board[capturedpieces.back()->coords.x][capturedpieces.back()->coords.y]=capturedpieces.back();
            capturedpieces.pop_back();
        }
        
        if(m.movetype==MoveType::PROMOTION){board[fr][fc]->type=((board[fr][fc]->team=='w')? 'p':'P');}
        
        if(m.movetype==MoveType::CASTLING){
            
            if(tc==6){
                board[tr][tc+1]=board[fr][fc+1]; board[tr][tc+1]->hasMoved--; 
                board[tr][tc+1]->coords={tr,tc+1}; board[fr][fc+1]=nullptr;
            }
            else{
                board[tr][tc-2]=board[fr][fc-1]; board[tr][tc-2]->hasMoved--; 
                board[tr][tc-2]->coords={tr,tc-2}; board[fr][fc-1]=nullptr;
            }
        }
        CastlingRights=m.PrevCastlingRights;
        En_PassantTargetSquare=m.PrevEn_Square;
        movehistory.pop_back();
    }
   return true;
}
