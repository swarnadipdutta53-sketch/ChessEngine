//TODO: THREAT CHECKS
#include "Board.h"
#include "stdiodef.h"

MoveType moveValidationRook(int row, int column, Coords c2, Board& obj)
{
    // if valid
    if(row == c2.x || column == c2.y)
    {
        int dx,dy,xi,yi;
        if(c2.x != row)
            dx = (c2.x > row) ? 1 : -1;
        else
            dx = 0;
        if(c2.y != column)
            dy = (c2.y > column) ? 1 : -1;
        else
            dy = 0;
        xi = row + dx;
        yi = column + dy;
        while(xi != c2.x || yi != c2.y)
        {
            if(obj.getpiece(xi, yi) != nullptr)
            {
                return MoveType::INVALID; // obstruction faced
            }
            xi += dx;
            yi += dy;
        }
        if(obj.getpiece(c2.x, c2.y) == nullptr)
            return MoveType::GENERAL;
        else if(obj.getpiece(c2.x,c2.y)->team != obj.getpiece(row,column) -> team)
            return MoveType::GENERAL; // capture case
        else
            return MoveType::INVALID; // destination is obstruction itself
    }
    else
        return MoveType::INVALID; // destination is not parallel
}

MoveType moveValidationBishop(int row, int column, Coords c2, Board& obj)
{
    // if valid
    /*
        absolute difference between x1 and x2 is equal to the difference between y1 and y2 for diagonal condition
    */
    if((abs(c2.y - column) == abs(c2.x - row)))
    {
        int dx,dy,xi,yi;
        dx = (row > c2.x) ? -1 : 1;
        dy = (column > c2.y) ? -1 : 1;
        xi = row + dx;
        yi = column + dy;
        while(c2.x != xi || c2.y != yi)
        {
            if(obj.getpiece(xi,yi) != nullptr)
                return MoveType::INVALID; // obstruction faced
            xi += dx;
            yi += dy;
        }
        if(obj.getpiece(c2.x,c2.y) == nullptr)
            return MoveType::GENERAL;
        else if(obj.getpiece(c2.x,c2.y)-> team != obj.getpiece(row, column) -> team)
            return MoveType::GENERAL; // capture case
        else
            return MoveType::INVALID; // destination is obstruction itself
    }
    else
        return MoveType::INVALID; // destination is not diagonal
}

MoveType moveValidationKnight(int row, int column, Coords c2, Board &obj)
{
    int dx, dy;
    dx = c2.x - row;
    dy = c2.y - column;
    // forwards and backwards(first layer check: general validation)
    if((abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2))
    {
        if(obj.getpiece(c2.x, c2.y) == nullptr)
            return MoveType::GENERAL;
        else if(obj.getpiece(c2.x, c2.y)-> team != obj.getpiece(row, column)-> team)
            return MoveType::GENERAL;
    }
    return MoveType::INVALID; // invalidated
}

MoveType moveValidationPawn(int row, int column, Coords c2, Board &obj)
{
    Pieces* lastPiece = obj.getlastmovedpiece();
    MoveType ret = MoveType::INVALID;
    int dx, dy, step;
    dx = c2.x - row;
    dy = c2.y - column;
    // direction validation
    if(dx > 0 && obj.getpiece(row, column)-> team == 'w')
        return MoveType::INVALID;
    else if(dx < 0 && obj.getpiece(row, column)-> team == 'b')
        return MoveType::INVALID;
    // double forward
    if(!(obj.getpiece(row, column)->hasMoved) && abs(dx) == 2 && dy == 0 && obj.getpiece(c2.x,c2.y) == nullptr)
    {
        step = (c2.x > row) ? 1 : -1;
        if(!(obj.getpiece(row + step, column))) // no obstruction in the intermediate square
            ret = MoveType::GENERAL;
    }
    // forwards
    else if((abs(dx) == 1 && dy == 0))
    {
        if(obj.getpiece(c2.x, c2.y) == nullptr)
            ret = MoveType::GENERAL;
    }
    // diagonal capture
    else if((abs(dx) == 1 && abs(dy) == 1))
    {
        // en passant diagonal capture
        Pieces* adjacent = obj.getpiece(row, column + dy);
        if (adjacent != nullptr && lastPiece != nullptr)
        {
            if (adjacent == lastPiece &&
                adjacent->team != obj.getpiece(row, column)->team &&
                adjacent->type != obj.getpiece(row, column)->type)
                ret = MoveType::EN_PASSANT;
        }
        // diagonal capture
        if(ret != MoveType::EN_PASSANT)
        {
            if(obj.getpiece(c2.x, c2.y) == nullptr)
                ret = MoveType::INVALID;
            else if(obj.getpiece(c2.x, c2.y)-> team != obj.getpiece(row, column)-> team)
                ret = MoveType::GENERAL;
        }
    }
    else
    // invalidity
        ret = MoveType::INVALID;
    if(ret != MoveType::INVALID && ((c2.x == 0 && obj.getpiece(row, column)-> team == 'w') || (c2.x == 7 && obj.getpiece(row, column)-> team == 'b')))
        ret = MoveType::PROMOTION;                        
    return ret;
}

MoveType moveValidationKing(int row, int column, Coords c2, Board &obj)
{
    //***Threat Check not applied***
    int dx, dy;
    dx = c2.x - row;
    dy = c2.y - column;
    if(abs(dx) > 1 || abs(dy) > 1) // since 0 is applicable for parallel moves
        return MoveType::INVALID;
    if(obj.getpiece(row + dx, column + dy)==nullptr)
        return MoveType::GENERAL;
    else if(obj.getpiece(row + dx, column + dy)->team != obj.getpiece(row,column)->team)
        return MoveType::GENERAL;
    else
        return MoveType::INVALID;
}

MoveType moveValidation(Pieces piece, Coords c2, Board &obj)
{
    int row = piece.coords.x;
    int column = piece.coords.y;
    if (c2.x == row && c2.y == column) // current coords of the piece
        return MoveType::INVALID;

    switch (piece.type)
    {
    case 'P':  //black pawn
    case 'p':  // white Pawn
        return moveValidationPawn(row, column, c2, obj);
    case 'r': // white rook
    case 'R': // black rook
        return moveValidationRook(row, column, c2, obj);
    case 'b': // white bishop
    case 'B': // black bishop
        return moveValidationBishop(row, column, c2, obj);
    case 'q': // white queen
    case 'Q': // black queen
        if(moveValidationBishop(row, column, c2, obj) != MoveType::INVALID||moveValidationRook(row,column,c2, obj)!=MoveType::INVALID)
            return MoveType::GENERAL;
        else
            return MoveType::INVALID;
    case 'n': // white knight
    case 'N': // black knight
        return moveValidationKnight(row,column, c2, obj);
    case 'k': // white king
    case 'K': // black king
        return moveValidationKing(row,column, c2, obj);
    default:
    printf("Error: moveValidations.invalidTeam");
    return MoveType::INVALID;
    }
}

