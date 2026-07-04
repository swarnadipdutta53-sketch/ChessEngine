//TODO: REMOVING THE CAPTURED PAWN FROM THE BOARD(implementation of enum in return values)

#include "moveValidations.h"
#include "Board.h"
#include "stdiodef.h"

bool moveValidationRook(int row, int column, Coords c2, Board& obj)
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
                return false; // obstruction faced
            }
            xi += dx;
            yi += dy;
        }
        if(obj.getpiece(c2.x, c2.y) == nullptr)
            return true;
        else if(obj.getpiece(c2.x,c2.y)->team != obj.getpiece(row,column) -> team)
            return true; // capture case
        else
            return false; // destination is obstruction itself
    }
    else
        return false; // destination is not parallel
}

bool moveValidationBishop(int row, int column, Coords c2, Board& obj)
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
                return false; // obstruction faced
            xi += dx;
            yi += dy;
        }
        if(obj.getpiece(c2.x,c2.y) == nullptr)
            return true;
        else if(obj.getpiece(c2.x,c2.y)-> team != obj.getpiece(row, column) -> team)
            return true; // capture case
        else
            return false; // destination is obstruction itself
    }
    else
        return false; // destination is not diagonal
}

bool moveValidationKnight(int row, int column, Coords c2, Board &obj)
{
    int dx, dy;
    dx = c2.x - row;
    dy = c2.y - column;
    // forwards and backwards
    if((abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2))
    {
        if(obj.getpiece(c2.x, c2.y) == nullptr)
            return true;
        else if(obj.getpiece(c2.x, c2.y)-> team != obj.getpiece(row, column)-> team)
            return true;
    }
    return false; // invalidated
}

bool moveValidationPawn(int row, int column, Coords c2, Board &obj)
{
    Pieces* lastPiece = obj.getlastmovedpiece();
    int dx, dy, step;
    dx = c2.x - row;
    dy = c2.y - column;
    // direction validation
    if(dx > 0 && obj.getpiece(row, column)-> team == 'p')
        return false;
    else if(dx < 0 && obj.getpiece(row, column)-> team == 'P')
        return false;
    // double forward
    if(!(obj.getpiece(row, column)->hasMoved) && abs(dx) == 2 && dy == 0 && obj.getpiece(c2.x,c2.y) == nullptr)
    {
        step = (c2.x > row) ? 1 : -1;
        if(!(obj.getpiece(row + step, column))) // no obstruction in the intermediate square
            return true;
    }
    // forwards
    else if((abs(dx) == 1 && dy == 0))
    {
        if(obj.getpiece(c2.x, c2.y) == nullptr)
            return true;
    }
    // diagonal capture
    else if((abs(dx) == 1 && abs(dy) == 1))
    {
        // en passant diagonal capture
        Pieces* adjacent = obj.getpiece(row, column + dy);
        Pieces* lastPiece = obj.getlastmovedpiece();
        if (adjacent != nullptr && lastPiece != nullptr)
        {
            if (adjacent == lastPiece &&
                adjacent->team != obj.getpiece(row, column)->team &&
                adjacent->type != obj.getpiece(row, column)->type)
                return true;
        }
        // diagonal capture
        if(obj.getpiece(c2.x, c2.y) == nullptr)
            return false;
        else if(obj.getpiece(c2.x, c2.y)-> team != obj.getpiece(row, column)-> team)
            return true;
    }
    // invalidity
    return false;
}

bool moveValidationKing(int row, int column, Coords c2, Board &obj)
{
    //***Threat Check not applied***
    int dx, dy;
    dx = c2.x - row;
    dy = c2.y - column;
    if(abs(dx) > 1 || abs(dy) > 1) // since 0 is applicable for parallel moves
        return false;
    if(obj.getpiece(row + dx, column + dy)==nullptr)
        return true;
    else if(obj.getpiece(row + dx, column + dy)->team != obj.getpiece(row,column)->team)
        return true;
    else
        return false;
}

bool moveValidation(Pieces piece, Coords c2, Board &obj)
{
    bool result;
    int row = piece.coords.x;
    int column = piece.coords.y;
    if (c2.x == row && c2.y == column) // current coords of the piece
        return false;

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
        return (moveValidationBishop(row, column, c2, obj)||moveValidationRook(row,column,c2, obj));
    case 'n': // white knight
    case 'N': // black knight
        return moveValidationKnight(row,column, c2, obj);
    case 'k': // white king
    case 'K': // black king
        return moveValidationKing(row,column, c2, obj);
    default:
    printf("Error: moveValidations.invalidTeam");
    return false;
    }
}