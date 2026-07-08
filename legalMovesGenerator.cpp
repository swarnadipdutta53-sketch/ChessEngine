#include "Board.h"
#include <iostream>
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
    int dx;
    int dy, len = 0; // 0(forward) , 1 , -1
    moves p_moves[4];
    Coords currPos = {piece -> coords.x, piece -> coords.y};
    dx = (piece -> team != 'p') ? 1 : -1;
    if(!(piece -> hasMoved)) // double forward
    {
        dx *= 2;
        if(board[dx][0] != nullptr)
        {
            if(board[dx][0] -> team != board[currPos.x][currPos.y] -> team)
            {
                p_moves[len] = {{currPos.x, currPos.y}, {dx, 0}, piece, board[dx][0], MoveType::GENERAL};
                ret.push_back(p_moves[len++]);
            }
        }
    }
    if(board[dx][1])
    {

    }
}
vector<moves> Board::generatePseudoLegalMoves(Pieces* piece)
{
    vector<moves> pseudoMoveVec;
    switch(piece -> type)
    {
        // for pawn
        case 'p':
        case 'P':

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