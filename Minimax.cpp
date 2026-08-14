#include "ChessAI.h"
#define t_MAXDEPTH 4
#define t_CHECKVAL 10000000
moves ChessAI::findBestMove(Board &board, bool whiteturn, int depth)
{   
    nodes=0;
    auto start = chrono::high_resolution_clock::now();

    moves bestMove;
    
    char turnOf = (whiteturn) ?  'w' : 'b';
    int bestScore = (whiteturn) ? INT_MIN : INT_MAX;
    vector<moves> mv = board.generateAllLegalMoves(turnOf);
    for(moves idx : mv)
    {
        board.makeMove(idx);
        int score = minimax(board, !whiteturn, depth+1);
        board.undoMove();
        if((score > bestScore && whiteturn) || (score < bestScore && !whiteturn))
        {
            bestScore = score;
            bestMove = idx;
        }
    }

    auto end = chrono::high_resolution_clock::now();

    double seconds = std::chrono::duration<double>(end - start).count();

    cout << "Search time : " << seconds << " s\n";
    cout << "Nodes       : " << nodes << '\n';
    cout << "NPS         : "
         << static_cast<long long>(nodes / seconds)
         << '\n';

    return bestMove;
}

int ChessAI::minimax(Board &board, bool whiteturn, int depth) //initialize depth as 0
{
    nodes++;
    if(depth == t_MAXDEPTH)
        return Evaluator::evaluate(board);
    char turnOf = (whiteturn) ?  'w' : 'b';
    int score;
    int maxEval = INT_MIN, minEval = INT_MAX;
    vector<moves> mv = board.generateAllLegalMoves(turnOf);
    if(mv.empty())
    {
        if(board.isAttacked(board.getking(turnOf))) //checkmate case
        {
            if(whiteturn)
                return -t_CHECKVAL+depth;
            else
                return t_CHECKVAL-depth;
        }
        else // stalemate case
            return 0;
    }
    for(moves idx : mv)
    {
        board.makeMove(idx);
        score = minimax(board, !whiteturn, depth+1);
        board.undoMove();
        if (whiteturn)
        {
            if(score > maxEval)
                maxEval = score;
        }
        else
        {
            if(score < minEval)
                minEval = score;
        }
    }
    if(whiteturn)
        return maxEval;
    else 
        return minEval;
}