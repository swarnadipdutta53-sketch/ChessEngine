#include "ChessAI.h"

long long ChessAI::nodes=0;
unordered_map<uint64_t, TTentry> ChessAI::Ttable;
static int movescore(const moves& l){
    int score=0;

    switch(l.movetype){
        case MoveType::PawnDouble:
            return 0;
        case MoveType::EN_PASSANT:
            return 900;
        case MoveType::GENERAL:
            if(l.capturedpiece==nullptr)return 0;
            else{
                score = Evaluator::getPieceValue(l.capturedpiece->type)*10 - Evaluator::getPieceValue(l.movedpiece->type);
                return score;
            }

        case MoveType::CASTLING: 
                return 10;
        case MoveType::PROMOTION:
                if(l.promotiontype==PromotionType::QUEEN)return 10000;
                else if(l.promotiontype==PromotionType::ROOK)return 9000;
                else if(l.promotiontype==PromotionType::KNIGHT)return 8500;
                else return 8500;
    }
    return score;
}


int ChessAI::quiscence(Board& b, int alpha, int beta){
        int standPat=Evaluator::evaluate(b);
        return 0;
}
void ChessAI::setnode(){
    nodes=0;
}
void ChessAI::getnode(){
    cout<<"nodes scanned "<<nodes<<endl;
}




//Transposition table start
void ChessAI::store(uint64_t hash, TTentry& entry){
    Ttable[hash]=entry;
}

bool ChessAI::probe(uint64_t hash, TTentry& entry){
    auto it = Ttable.find(hash);
    if(it!=Ttable.end()){
        entry = it->second;
        return true;
    }
    else return false;
}

void ChessAI::clearTable(){
    Ttable.clear();
}



//Move ordering start
