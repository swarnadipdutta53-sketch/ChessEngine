#ifndef CHESSAI_H
#define CHESSAI_H
#include "Board.h"
#include "Evaluator.h"
#include "limits.h" 
class ChessAI
{
private:

public: 
        static moves findBestMove(Board&,bool,int);
        static int minimax(Board&,bool,int);
        int quiscence(Board&, int, int);
        
};
#endif

