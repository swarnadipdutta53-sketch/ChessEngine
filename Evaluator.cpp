#include "Evaluator.h"

const int Evaluator::PassedPawnBonus[8]={0,0,10,20,35,60,100,0};

const int Evaluator::PawnTable[8][8]={
   {  0,  0,  0,  0,  0,  0,  0,  0},
    { 50, 50, 50, 50, 50, 50, 50, 50},
    { 10, 10, 20, 30, 30, 20, 10, 10},
    {  5,  5, 10, 25, 25, 10,  5,  5},
    {  0,  0,  0, 20, 20,  0,  0,  0},
    {  5, -5,-10,  0,  0,-10, -5,  5},
    {  5, 10, 10,-20,-20, 10, 10,  5},
    {  0,  0,  0,  0,  0,  0,  0,  0},

};
const int Evaluator::KnightTable[8][8]={
    {-50,-40,-30,-30,-30,-30,-40,-50},
    {-40,-20,  0,  0,  0,  0,-20,-40},
    {-30,  0, 10, 15, 15, 10,  0,-30},
    {-30,  5, 15, 20, 20, 15,  5,-30},
    {-30,  0, 15, 20, 20, 15,  0,-30},
    {-30,  5, 10, 15, 15, 10,  5,-30},
    {-40,-20,  0,  5,  5,  0,-20,-40},
    {-50,-40,-30,-30,-30,-30,-40,-50},
};
const int Evaluator::BishopTable[8][8]={
    {-20,-10,-10,-10,-10,-10,-10,-20},
    { 10,  5,  0,  0,  0,  0,  5, 10},
    {-10, 10, 10, 10, 10, 10, 10,-10},
    {-10,  0, 10, 10, 10, 10,  0,-10},
    {-10,  5,  5, 10, 10,  5,  5,-10},
    {-10,  0,  5, 10, 10,  5,  0,-10},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-20,-10,-10,-10,-10, -10,-10,-20},
};
const int Evaluator::RookTable[8][8]={
    {  0,  0,  0,  5,  5,  0,  0,  0},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    {  5, 10, 10, 10, 10, 10, 10,  5},
    {  0,  0,  0,  0,  0,  0,  0,  0},
};
const int Evaluator::QueenTable[8][8]={
    {-20,-10,-10, -5, -5,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5,  5,  5,  5,  0,-10},
    { -5,  0,  5,  5,  5,  5,  0, -5},
    {  0,  0,  5,  5,  5,  5,  0, -5},
    {-10,  5,  5,  5,  5,  5,  0,-10},
    {-10,  0,  5,  0,  0,  0,  0,-10},
    {-20,-10,-10, -5, -5,-10,-10,-20},
};

const int Evaluator::MiddleGameKingTable[8][8] = {
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-20,-30,-30,-40,-40,-30,-30,-20},
    {-10,-20,-20,-20,-20,-20,-20,-10},
    { 20, 20,  0,  0,  0,  0, 20, 20},
    { 20, 30, 10,  0,  0, 10, 30, 20}
};

const int Evaluator::EndGameKingTable[8][8] = {
    {-50,-40,-30,-20,-20,-30,-40,-50},
    {-30,-20,-10,  0,  0,-10,-20,-30},
    {-30,-10, 20, 30, 30, 20,-10,-30},
    {-30,-10, 30, 40, 40, 30,-10,-30},
    {-30,-10, 30, 40, 40, 30,-10,-30},
    {-30,-10, 20, 30, 30, 20,-10,-30},
    {-30,-30,  0,  0,  0,  0,-30,-30},
    {-50,-30,-30,-30,-30,-30,-30,-50}
};

const Coords Evaluator::KnightDirections[8]={
    {-2,-1},{-2,1},{2,-1},{2,1},
    {-1,-2},{-1,2},{1,-2},{1,2},
};
const Coords Evaluator::BishopDirections[4]={
    {-1,-1},{-1,+1},{+1,-1},{+1,+1},
};
const Coords Evaluator::RookDirections[4]={
    {+0,-1},{-1,+0},{+0,+1},{+1,+0}
};
const Coords Evaluator::QueenDirections[8]={
    {+0,-1},{-1,+0},{+0,+1},{+1,+0},
    {-1,-1},{-1,+1},{+1,-1},{+1,+1},
};



int Evaluator::calcPhase(const Board& b){
    int phase=0;
    for(Pieces* p:b.getWhitePieces()){
        if(p->alive){
            switch(p->type){
                case 'p': phase+=0; break;
                case 'n': phase+=1; break;
                case 'b': phase+=1; break;
                case 'r': phase+=2; break;
                case 'q': phase+=4; break;
                case 'k': phase+=0;break;
            }
        }
    }
    for(Pieces* p:b.getBlackPieces()){
        if(p->alive){
            switch(p->type){
                case 'P': phase+=0; break;
                case 'N': phase+=1; break;
                case 'B': phase+=1; break;
                case 'R': phase+=2; break;
                case 'Q': phase+=4; break;
                case 'K': phase+=0;break;
            }
        }
    }
    return phase;
}


int Evaluator::evaluateMaterial(const Board& b){
    int total=0,whitebishops=0,blackbishops=0;
    for(Pieces* p:b.getWhitePieces()){if(p->alive){total+=piecevalue[p->type]; if(p->type=='b')whitebishops++;}}
    for(Pieces* p:b.getBlackPieces()){if(p->alive){total+=piecevalue[p->type]; if(p->type=='B')blackbishops++;}}
    if(whitebishops==2)total+=40; if(blackbishops==2)total-=40;
    return total;
}

int Evaluator::evaluatePST(const Board& b,int phase){
    int total=0,temp1,temp2;
    for(Pieces* p:b.getWhitePieces()){
        if(p->alive){
            switch(p->type){
                case 'p': total+=PawnTable[p->coords.x][p->coords.y];break;
                case 'n': total+=KnightTable[p->coords.x][p->coords.y];break;
                case 'b': total+=BishopTable[p->coords.x][p->coords.y];break;
                case 'r': total+=RookTable[p->coords.x][p->coords.y];break;
                case 'q': total+=QueenTable[p->coords.x][p->coords.y];break;
                case 'k': 
                        temp1=(MiddleGameKingTable[p->coords.x][p->coords.y])*phase;
                        temp2=(EndGameKingTable[p->coords.x][p->coords.y])*(MAX_PHASE-phase);
                        total+=(temp1+temp2)/MAX_PHASE; break;
            }
        }
    }

    for(Pieces* p:b.getBlackPieces()){
        if(p->alive){
            switch(p->type){
                case 'P': total-=PawnTable[7-p->coords.x][p->coords.y];break;
                case 'N': total-=KnightTable[7-p->coords.x][p->coords.y];break;
                case 'B': total-=BishopTable[7-p->coords.x][p->coords.y];break; //7-x mirrors the PST for black pieces
                case 'R': total-=RookTable[7-p->coords.x][p->coords.y];break;
                case 'Q': total-=QueenTable[7-p->coords.x][p->coords.y];break;
                case 'K': 
                        temp1=(MiddleGameKingTable[7-p->coords.x][p->coords.y])*phase;
                        temp2=(EndGameKingTable[7-p->coords.x][p->coords.y])*(MAX_PHASE-phase);
                        total-=(temp1+temp2)/MAX_PHASE; break;
            }
        }
    }
    return total;
}

bool Evaluator::scanfront(vector<Coords>&index,int row,int col,char team){
        if(team=='w'){
            for(auto l:index){
                if(l.y==col&&l.x<=row)return false;
            }
            return true;
        }
        else{
            for(auto l:index){
                if(l.y==col&&l.x>=row)return false;
            }
            return true;
        }
}

int Evaluator::evaluatePawnStructure(const Board& b){
    //doubled pawns and isolated pawns

    vector<Coords> wp,bp;
    int total=0,cntW[8]={},cntB[8]={},prev,next;
    for(Pieces* p:b.getWhitePieces()){
            if(p->alive&&p->type=='p'){cntW[p->coords.y]++; wp.push_back({p->coords.x,p->coords.y});}
    }
    
    for(Pieces* p:b.getBlackPieces()){
            if(p->alive&&p->type=='P'){cntB[p->coords.y]++; bp.push_back({p->coords.x,p->coords.y});}
    }

    for(int i=0;i<8;i++){
        if(cntW[i]>1)total-=20*(cntW[i]-1);
        if(cntW[i]>0){
            prev=i-1; next=i+1;
            if((prev<0||cntW[prev]==0)&&(next>7||cntW[next]==0))total-=20*cntW[i];
        }
        if(cntB[i]>1)total+=20*(cntB[i]-1);
        if(cntB[i]>0){
            prev=i-1; next=i+1;
            if((prev<0||cntB[prev]==0)&&(next>7||cntB[next]==0))total+=20*cntB[i];
        }
    }

    //Passed Pawns 
    for(Coords coords:wp){
        bool p=true,c=true,n=true;
        if(coords.y-1>=0)p=scanfront(bp,coords.x,coords.y-1,'w');
        if(coords.y+1<8)n=scanfront(bp,coords.x,coords.y+1,'w');
        c=scanfront(bp,coords.x,coords.y,'w');

        if(p&&c&&n){total+=PassedPawnBonus[7-coords.x];}
    }
    for(Coords coords:bp){
        bool p=true,c=true,n=true;
        if(coords.y-1>=0)p=scanfront(wp,coords.x,coords.y-1,'b');
        if(coords.y+1<8)n=scanfront(wp,coords.x,coords.y+1,'b');
        c=scanfront(wp,coords.x,coords.y,'b');

        if(p&&c&&n){total-=PassedPawnBonus[coords.x];}
    }
    
    return total;
}

int Evaluator::evaluateMobility(const Board& b){
    int total=0;
    for(Pieces* p:b.getWhitePieces()){
        if(!p->alive)continue;

        int count= countPseudoMobility(b,p);

        switch(p->type){
            case 'n': total+=4*count; break;
            case 'b': total+=4*count; break;
            case 'r': total+=2*count; break;
            case 'q': total+=1*count; break;
            default : break;
        }
    }

    for(Pieces* p:b.getBlackPieces()){
        if(!p->alive)continue;

        int count= countPseudoMobility(b,p);

        switch(p->type){
            case 'N': total-=4*count; break;
            case 'B': total-=4*count; break;
            case 'R': total-=2*count; break;
            case 'Q': total-=1*count; break;
            default : break;
        }
    }

    return total;
}

int Evaluator::countKnightMobility(const Board& b, Pieces* piece){
    int count = 0;

    for(const Coords& dir : KnightDirections){
        int x = piece->coords.x + dir.x ;
        int y = piece->coords.y + dir.y;

        if(x >=0 && x <8 && y >=0 && y <8){
            Pieces* target = b.getpiece(x,y);

            if(target == nullptr || target->team != piece->team)count++;
        }
    }

    return count;
}

int Evaluator::countBishopMobility(const Board& b, Pieces* p){
    int count=0;


    for(const Coords& dir:BishopDirections){
        int x=p->coords.x+dir.x;
        int y=p->coords.y+dir.y;
        while(x>=0&&x<=7&&y>=0&&y<=7){
            Pieces* l=b.getpiece(x,y);
            if(l!=nullptr){
                if(p->team!=l->team){count++;}
                break;
            }
            count++;
            x+=dir.x;
            y+=dir.y;
        }
    }
    return count;
}
int Evaluator::countRookMobility(const Board& b, Pieces* p){
    int count=0;

    for(const Coords& dir:RookDirections){
        int x=p->coords.x+dir.x;
        int y=p->coords.y+dir.y;
        while(x>=0&&x<=7&&y>=0&&y<=7){
            Pieces* l=b.getpiece(x,y);
            if(l!=nullptr){
                if(p->team!=l->team){count++;}
                break;
            }
            count++;
            x+=dir.x;
            y+=dir.y;
        }
    }
    return count;
}
int Evaluator::countQueenMobility(const Board& b, Pieces* p){
    int count=0;

    for(const Coords& dir:QueenDirections){
        int x=p->coords.x+dir.x;
        int y=p->coords.y+dir.y;
        while(x>=0&&x<=7&&y>=0&&y<=7){
            Pieces* l=b.getpiece(x,y);
            if(l!=nullptr){
                if(p->team!=l->team){count++;}
                break;
            }
            count++;
            x+=dir.x;
            y+=dir.y;
        }
    }
    return count;
}

int Evaluator::countPseudoMobility(const Board& b, Pieces* p)
{
    switch(p->type)
    {
        case 'N':
        case 'n':
             return countKnightMobility(b,p);

        case 'B':
        case 'b':
             return countBishopMobility(b,p);

        case 'R':
        case 'r':
             return countRookMobility(b,p);

        case 'Q':
        case 'q':
             return countQueenMobility(b,p);

        default:
            return 0;
    }
}

int Evaluator::evaluate(const Board& b){
    int phase=calcPhase(b);
    return evaluateMaterial(b)+evaluatePST(b,phase)+evaluatePawnStructure(b)+evaluateMobility(b);

} 