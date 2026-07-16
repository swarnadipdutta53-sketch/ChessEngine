#ifndef CHESSAI_H
#define CHESSAI_H
#include "Board.h"
#include "Evaluator.h"
#include "limits.h" 
#include <chrono>
class ChessAI
{
private:
        static long long nodes;
public: 
        static moves findBestMove(Board&,bool,int);
        static int minimax(Board&,bool,int);
        int quiscence(Board&, int, int);
        static void setnode();
        static void getnode();
};
#endif

