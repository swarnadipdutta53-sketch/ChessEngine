#ifndef CHESSAI_H
#define CHESSAI_H
#include "Board.h"
#include "Evaluator.h"
#include <unordered_map>

enum class FlagType{
        EXACT,
        UPPERBOUND,
        LOWERBOUND,
};

struct TTmove{
        Coords from;
        Coords to;
        PromotionType promotype;
};


struct TTentry{
        int depth;
        int score;
        TTmove bestmove;
        FlagType flag;
};

class ChessAI
{
private:
        static long long nodes;
        static unordered_map <uint64_t, TTentry> Ttable;
public:
        static moves findBestMove(Board&,bool,int);
        static int minimax(Board&,bool,int);
        int quiscence(Board&, int, int);
        static void setnode();
        static void getnode();

        static void store(uint64_t, TTentry&);
        static bool probe(uint64_t, TTentry&); //Transposition table
        static void clearTable();


        static void ordermoves(vector<moves>& m);
};


#endif

