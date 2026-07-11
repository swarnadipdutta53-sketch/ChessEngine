#include "Evaluator.h"

const int Evaluator::PawnTable[8][8]={
    {  0,  0,  0,  0,  0,  0,  0,  0},
    { 50, 50, 50, 50, 50, 50, 50, 50},
    { 10, 10, 20, 30, 30, 20, 10, 10},
    { 5, 5,10,25,25,10, 5, 5},
    { 0, 0, 0,20,20, 0, 0, 0},
    { 5,-5,-10, 0, 0,-10,-5,  5},
    {5,10,10,-20,-20,10,10,5},
    {0,0,0,0,0,0,0,0},
};
const int Evaluator::KnightTable[8][8]={
    {-50,-40,-30,-30,-30,-30,-40,-50},
    {-40,-20,0,0,0,0,-20,-40},
    {-30,0,10,15,15,10,0,-30},
    {-30,5,15,20,20,15,5,-30},
    {-30,0,15,20,20,15,0,-30},
    {-30,5,10,15,15,10,5,-30},
    {-40,-20,0,5,5,0,-20,-40},
    {-50,-40,-30,-30,-30,-30,-40,-50},
};
const int Evaluator::BishopTable[8][8]={
    {-20,-10,-10,-10,-10,-10,-10,-20},
    {10,5,0,0,0,0,5,10},
    {-10,10,10,10,10,10,10,-10},
    {-10,0,10,10,10,10,0,-10},
    {-10,5,5,10,10,5,5,-10},
    {-10,0,5,10,10,5,0,-10},
    {-10,0,0,0,0,0,0,-10},
    {-20,-10,-10,-10,-10,10,-10,-20},
};
const int Evaluator::RookTable[8][8]={
    {0,0,0,5,5,0,0,0},
    {-5,0,0,0,0,0,0,-5},
    {-5,0,0,0,0,0,0,-5},
    {-5,0,0,0,0,0,0,-5},
    {-5,0,0,0,0,0,0,-5},
    {-5,0,0,0,0,0,0,-5},
    {5,10,10,10,10,10,10,5},
    {0,0,0,0,0,0,0,0},
};
const int Evaluator::QueenTable[8][8]={
    {-20,-10,-10,-5,-5,-10,-10,-20},
    {-10,0,0,0,0,0,0,-10},
    {-10,0,5,5,5,5,0,-10},
    {-5,0,5,5,5,5,0,-5},
    {0,0,5,5,5,5,0,-5},
    {-10,5,5,5,5,5,0,-10},
    {-10,0,5,0,0,0,0,-10},
    {-20,-10,-10,-5,-5,-10,-10,-20},
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

int Evaluator::evaluate(const Board& b){
    int phase=calcPhase(b);
    return evaluateMaterial(b)+evaluatePST(b,phase);

} 