#include "Board.h"
#include "Evaluator.h"
#include "limits.h" 
class ChessAI
{
private:
    
public: 
        moves findBestMove(Board&,bool,int);
        int minimax(Board&,bool,int);
        int quiscence(Board&, int, int);
        
};


