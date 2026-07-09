#include "Board.h"
#include <iostream>
#define CHECKTEAM(x1,y1,x2,y2) ((board[x1][y1] -> team) == (board[x2][y2] -> team)) // only used for (x1, y1)  != (x2, y2)
#define CHECKPIECETYPE(x1,y1,t) ((board[x1][y1] -> type) == t)
#define CHECKPAWN(x1,y1) (CHECKPIECETYPE(x1,y1, 'P') || CHECKPIECETYPE(x1, y1, 'p'))
#define CHECKBOUND(x,y) ((x >= 0)  && (x < 8) && (y >= 0) && (y < 8))
#define CHECKPROMOTION(x) ((x==7) || (x==0))
/*
typedef struct moves
{
        square from;
        square to;

        Pieces* movedpiece;
        Pieces* capturedpiece;

        MoveType t;
}moves;
*/
/*
generateLegal() -> generatePseudoLegal() -> for each move checkIsAttacked() -> checkCanAttacked() for each opponent piece() -> if no then push move, if no dont push
*/
vector<moves> Board::generatePseudoLegalMovesRook(Pieces* piece)
{
    return{};
}
vector<moves> Board::generatePseudoLegalMovesPawn(Pieces* piece)
{
    vector<moves> ret;
    Coords currPos = {piece -> coords.x, piece -> coords.y};
    bool adjacent[2] = {false,false};
    int dx = (piece -> type == 'p') ? -1 : 1;   // dy = 0(forward) , 1 , -1
    // en-passant
    // checking if adjacent pawn is enabling enpassant, if yes then assigning it to the adjacent
    int i = 0;
    for(int dy : {-1,1}) // checking adjascency
    {
        if(CHECKBOUND(currPos.x, currPos.y+dy))
        {
            if(board[currPos.x][currPos.y+dy] != nullptr)
            {
                if(CHECKPAWN(currPos.x, currPos.y+dy) && !CHECKTEAM(currPos.x, currPos.y, currPos.x, currPos.y + dy)
                                                    && getlastmovedpiece() == board[currPos.x][currPos.y+dy] && (abs(movehistory.back().to.x - movehistory.back().from.x) == 2))
                    adjacent[i] = true;
            }
        }
        i++;
    }
    if(adjacent[0]) // left side enpassant
        ret.push_back({{currPos.x, currPos.y}, {dx+currPos.x,currPos.y -1}, piece, board[currPos.x][currPos.y-1], MoveType::EN_PASSANT});
    if(adjacent[1]) // right side enpassant
        ret.push_back({{currPos.x, currPos.y}, {dx+currPos.x,currPos.y +1}, piece, board[currPos.x][currPos.y+1], MoveType::EN_PASSANT});

    if(CHECKBOUND(currPos.x + 2*dx, currPos.y) && CHECKBOUND(currPos.x + dx, currPos.y)) // double forward
    {
        if(!(piece -> hasMoved) && board[currPos.x + dx*2][currPos.y+0] == nullptr && board[currPos.x + dx][currPos.y] == nullptr) 
            ret.push_back({{currPos.x, currPos.y}, {2*dx+currPos.x, currPos.y+0}, piece, board[currPos.x + dx*2][currPos.y], MoveType::GENERAL});
    }
    
    if(CHECKBOUND(currPos.x + dx, currPos.y)) // single forward
    {
        if(board[dx+currPos.x][currPos.y] == nullptr) 
        {
             //promotion hanlde
            if(CHECKPROMOTION(currPos.x + dx))
                ret.push_back({{currPos.x, currPos.y}, {currPos.x + dx, currPos.y}, piece, board[currPos.x + dx][currPos.y], MoveType::PROMOTION});
            else
                ret.push_back({{currPos.x, currPos.y}, {dx+currPos.x, currPos.y}, piece, board[currPos.x + dx][currPos.y], MoveType::GENERAL});
        }
    }

    for(int dy : {-1,1})
    {
        if(CHECKBOUND(currPos.x + dx, currPos.y+dy))
        {
            if(board[dx+currPos.x][currPos.y+dy] != nullptr) // left diagonal capture (w.r.t white)
            {
                if(!CHECKTEAM(dx+currPos.x,currPos.y+dy,currPos.x,currPos.y))
                {
                    if(CHECKPROMOTION(currPos.x + dx)) //promotion handle
                        ret.push_back({{currPos.x, currPos.y}, {currPos.x + dx, currPos.y +dy}, piece, board[currPos.x + dx][currPos.y+dy], MoveType::PROMOTION});
                    else
                        ret.push_back({{currPos.x, currPos.y}, {dx+currPos.x,currPos.y +dy}, piece, board[currPos.x+dx][currPos.y+dy], MoveType::GENERAL});
                    
                }
            }
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

        // for rook
        case 'r':
        case 'R':

        //for bishop
        case 'b':
        case 'B':

        // for Queen
        case 'q':
        case 'Q':

        // for knight
        case 'n':
        case 'N':
        // for king
        case 'k':
        case 'K':
        default:
        cout << "Invalid Piece Selection Error From LegalMovesGenerator: 1.0";
    }
    return pseudoMoveVec;
}