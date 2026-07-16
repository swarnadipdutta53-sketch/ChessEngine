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
        inline static constexpr int MAX_PHASE=24;
        inline static constexpr int ENDGAME_THRESHOLD=24;

        static const int PassedPawnBonus[8];
        static const int PawnTable[8][8];
        static const int KnightTable[8][8];
        static const int BishopTable[8][8];
        static const int RookTable[8][8];
        static const int QueenTable[8][8];
        static const int MiddleGameKingTable[8][8];
        static const int EndGameKingTable[8][8];
        static const Coords KnightDirections[8];
        static const Coords BishopDirections[4];
        static const Coords RookDirections[4];
        static const Coords QueenDirections[8];

        static int calcPhase(const Board&);
        static int evaluatePST(const Board&,int);
        static int evaluateMaterial(const Board&);
        static int evaluatePawnStructure(const Board&);
        static bool scanfront(vector<Coords>&,int,int,char);
        static int evaluateMobility(const Board&);
        static int countPseudoMobility(const Board& b, Pieces* p);
        static int countKnightMobility(const Board&, Pieces*);
        static int countBishopMobility(const Board&, Pieces*);
        static int countRookMobility(const Board&, Pieces*);
        static int countQueenMobility(const Board&, Pieces*);
        
public:
        static int evaluate(const Board&);
      
};


#endif