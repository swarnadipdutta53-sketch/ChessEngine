#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Board.h"
#include <array>


class Evaluator
{
private:
        inline static constexpr array<int,256> piecevalue = []{
        array<int,256> values{};

        values['p']=100; values['P']=-100;
        values['n']=320; values['N']=-320;
        values['b']=330; values['B']=-330;
        values['r']=500; values['R']=-500;
        values['q']=900; values['Q']=-900;
        values['k']=30000; values['K']=-30000;
        
        return values;
   }();
        static const int PawnTable[8][8];
        static const int KnightTable[8][8];
        static const int BishopTable[8][8];
        static const int RookTable[8][8];
        static const int QueenTable[8][8];
        static const int KingTable[8][8];


        static int evaluatePST(const Board&);
        static int evaluateMaterial(const Board&);
public:
        static int evaluate(const Board&);

};


#endif