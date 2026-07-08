#include "Board.h"
#include <iostream>
#define CHECKTEAM(x1,y1,x2,y2) board[x1][y1] -> team == board[x2][y2] -> team // only used for (x1, y1)  != (x2, y2)
#define CHECKPIECETYPE(x1,y1,t) board[x1][y1] -> type == t
#define CHECKPAWN(x1,y1) (CHECKPIECETYPE(x1,y1, 'P') || CHECKPIECETYPE(x1, y1, 'p'))
/*
typedef struct moves
{
        square from;
        square to;

        Pieces* movedpiece;
        Pieces* capturedpiece;
        bool capt;
        MoveType t;
}moves;
*/
/*
generateLegal() -> generatePseudoLegal() -> for each move checkIsAttacked() -> checkCanAttacked() for each opponent piece() -> if no then push move, if no dont push
*/
vector<moves> Board::generatePseudoLegalMovesRook(Pieces* piece)
{

}
vector<moves> Board::generatePseudoLegalMovesPawn(Pieces* piece)
{
    vector<moves> ret;
    Pieces* adjascent1 = nullptr, *adjascent2 = nullptr;
    int dx;
    int len = 0; // dy = 0(forward) , 1 , -1
    moves p_moves[4];
    Coords currPos = {piece -> coords.x, piece -> coords.y};
    dx = (piece -> team != 'p') ? -1 : 1;
    // checking if adjacent pawn is enabling enpassant, if yes then assigning it to the adjascent
    if(board[currPos.x][currPos.y-1] != nullptr) // left side
    {
        if(CHECKPAWN(currPos.x, currPos.y-1) && !CHECKTEAM(currPos.x, currPos.y, currPos.x, currPos.y - 1)
                                             && getlastmovedpiece() == board[currPos.x][currPos.y-1] && getlastmovedpiece()->hasMoved == 1)
            adjascent1 = board[currPos.x][currPos.y - 1];
    }
    if(board[currPos.x][currPos.y+1] != nullptr) // right side
    {
        if(CHECKPAWN(currPos.x, currPos.y+1) && !CHECKTEAM(currPos.x, currPos.y, currPos.x, currPos.y + 1)
                                             && getlastmovedpiece() == board[currPos.x][currPos.y+1] && getlastmovedpiece()->hasMoved == 1)
            adjascent2 = board[currPos.x][currPos.y + 1];
    }
    if(!(piece -> hasMoved) && board[currPos.x + dx*2][currPos.y+0] == nullptr && board[currPos.x + dx][currPos.y] == 0) // double forward
    {
        p_moves[len] = {{currPos.x, currPos.y}, {2*dx+currPos.x, currPos.y+0}, piece, nullptr, MoveType::GENERAL};
        ret.push_back(p_moves[len++]);
    }
    if(board[dx+currPos.x][currPos.y+0] == nullptr) // single forward
    {
        p_moves[len] = {{currPos.x, currPos.y}, {dx+currPos.x, currPos.y+0}, piece, nullptr, MoveType::GENERAL};
        ret.push_back(p_moves[len++]);
    }
    if(board[dx+currPos.x][currPos.y-1] != nullptr) // left diagonal capture (w.r.t white)
    {
        if(!CHECKTEAM(dx+currPos.x,currPos.y-1,currPos.x,currPos.y))
        {
            if(adjascent1 != nullptr)
                p_moves[len] = {{currPos.x, currPos.y}, {dx+currPos.x,currPos.y -1}, piece, board[dx+currPos.x][currPos.y-1], MoveType::EN_PASSANT};
            else
                p_moves[len] = {{currPos.x, currPos.y}, {dx+currPos.x,currPos.y -1}, piece, board[currPos.x][currPos.y-1], MoveType::GENERAL};
            ret.push_back(p_moves[len++]);
        }
    }
    if(board[dx+currPos.x][currPos.y+1] != nullptr) // right diagonal capture (same)
    {
        if(!CHECKTEAM(dx+currPos.x,currPos.y+1,currPos.x,currPos.y))
        {
            if(adjascent2 != nullptr)
                p_moves[len] = {{currPos.x, currPos.y}, {dx+currPos.x,currPos.y +1}, piece, board[dx+currPos.x][currPos.y+1], MoveType::EN_PASSANT};
            else
                p_moves[len] = {{currPos.x, currPos.y}, {dx+currPos.x,currPos.y +1}, piece, board[currPos.x][currPos.y+1], MoveType::GENERAL};
            ret.push_back(p_moves[len++]);
        }
    }
    return ret;
}
vector<moves> Board::generatePseudoLegalMoves(Pieces* piece)
{
    vector<moves> pseudoMoveVec;
    switch(piece -> type)
    {
        // for pawn
        case 'p':
        case 'P':
        return generatePseudoLegalMovesPawn(piece);
        break;
        // for rook
        case 'r':
        case 'R':

        break;
        //for bishop
        case 'b':
        case 'B':
        break;
        // for Queen
        case 'q':
        case 'Q':
        break;
        // for knight
        case 'n':
        case 'N':
        // for king
        case 'k':
        case 'K':
        default:
        cout << "Invalid Piece Selection Error From LegalMovesGenerator: 1.0";
        break;
    }
    return pseudoMoveVec;
}