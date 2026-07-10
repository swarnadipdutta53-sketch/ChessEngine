#include "Evaluator.h"

const int Evaluator::PawnTable[8][8]={
    {0,0,0,0,0,0,0,0},
    {50,50,50,50,50,50,50,50},
    {10,10,20,30,30,20,10,10},
    {5,5,10,25,25,10,5,5},
    {0,0,0,20,20,0,0,0,},
    {5,-5,10,0,0,-10,-5,5},
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
const int Evaluator::PawnTable[8][8]={
    {0,0,0,0,0,0,0,0},
    {50,50,50,50,50,50,50,50},
    {10,10,20,30,30,20,10,10},
    {5,5,10,25,25,10,5,5},
    {0,0,0,20,20,0,0,0,},
    {5,-5,10,0,0,-10,-5,5},
    {5,10,10,-20,-20,10,10,5},
    {0,0,0,0,0,0,0,0},
};
const int Evaluator::PawnTable[8][8]={
    {0,0,0,0,0,0,0,0},
    {50,50,50,50,50,50,50,50},
    {10,10,20,30,30,20,10,10},
    {5,5,10,25,25,10,5,5},
    {0,0,0,20,20,0,0,0,},
    {5,-5,10,0,0,-10,-5,5},
    {5,10,10,-20,-20,10,10,5},
    {0,0,0,0,0,0,0,0},
};
const int Evaluator::PawnTable[8][8]={
    {0,0,0,0,0,0,0,0},
    {50,50,50,50,50,50,50,50},
    {10,10,20,30,30,20,10,10},
    {5,5,10,25,25,10,5,5},
    {0,0,0,20,20,0,0,0,},
    {5,-5,10,0,0,-10,-5,5},
    {5,10,10,-20,-20,10,10,5},
    {0,0,0,0,0,0,0,0},
};
const int Evaluator::PawnTable[8][8]={
    {0,0,0,0,0,0,0,0},
    {50,50,50,50,50,50,50,50},
    {10,10,20,30,30,20,10,10},
    {5,5,10,25,25,10,5,5},
    {0,0,0,20,20,0,0,0,},
    {5,-5,10,0,0,-10,-5,5},
    {5,10,10,-20,-20,10,10,5},
    {0,0,0,0,0,0,0,0},
};








int Evaluator::evaluateMaterial(const Board& b){
    int total=0;
    for(Pieces* p:b.getWhitePieces()){if(p->alive)total+=piecevalue[p->type];}
    for(Pieces* p:b.getBlackPieces()){if(p->alive)total+=piecevalue[p->type];}
    return total;
}

int Evaluator::evaluatePST(const Board& b){
    int total=0;
    for(Pieces* p:b.getWhitePieces()){
        if(p->alive){
            switch(p->type){
                case 'p': total+=PawnTable[p->coords.x][p->coords.y];break;
                case 'n': total+=PawnTable[p->coords.x][p->coords.y];break;
                case 'b': total+=PawnTable[p->coords.x][p->coords.y];break;
                case 'r': total+=PawnTable[p->coords.x][p->coords.y];break;
                case 'q': total+=PawnTable[p->coords.x][p->coords.y];break;
                case 'k': total+=PawnTable[p->coords.x][p->coords.y];break;
            }
        }
    }

    for(Pieces* p:b.getBlackPieces()){
        if(p->alive){
            switch(p->type){
                case 'P': total-=PawnTable[p->coords.x][p->coords.y];break;
                case 'n': total+=PawnTable[p->coords.x][p->coords.y];break;
                case 'b': total+=PawnTable[p->coords.x][p->coords.y];break;
                case 'r': total+=PawnTable[p->coords.x][p->coords.y];break;
                case 'q': total+=PawnTable[p->coords.x][p->coords.y];break;
                case 'k': total+=PawnTable[p->coords.x][p->coords.y];break;
            }
        }
    }
}

int Evaluator::evaluate(const Board& b){
    return evaluateMaterial(b);

} 