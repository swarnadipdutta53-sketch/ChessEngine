#include "ChessAI.h"

long long ChessAI::nodes=0;
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