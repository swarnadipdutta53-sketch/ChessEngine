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
        return false;
}

bool moveValidationBishop(int x, int y, Coords c2, Board& obj)
{
    int found = 0;
    
    // right diagonal movement(forwards)
    int xi = x + 1, yi = y + 1;
    while(xi < 8 && yi < 8)
    {
        if((c2.x == xi) && (c2.y == yi))
            return true; // valid 
        if(obj.getpiece(xi,yi) != nullptr)
            return false; // obstruction faced
        xi++;
        yi++;
    }
    // right diagonal movement(backwards)
    xi = x - 1, yi = y - 1;
    while(xi >= 0 && yi >= 0)
    {
        if((c2.x == xi) && (c2.y == yi))
            return true; // valid
        if(obj.getpiece(xi,yi) != nullptr)
            return false; // obstruction faced
        xi--;
        yi--;
    }
    // left diagonal movement(forwards)
    xi = x-1, yi = y+1;
    while(xi >= 0 && yi < 8)
    {
        if((c2.x == xi) && (c2.y == yi))
            return true; // valid 
        if(obj.getpiece(xi,yi) != nullptr)
            return false; // obstruction faced
        xi--;
        yi++;
    }
    // left diagonal movement(backwards)
    xi = x+1, yi = y-1;
    while(xi < 8 && yi >= 0)
    {
        if((c2.x == xi) && (c2.y == yi))
            return true; // valid 
        if(obj.getpiece(xi,yi) != nullptr)
            return false; // obstruction faced
        xi++;
        yi--;
    }
    return false; // invalid input for c2 for bishop
}

bool moveValidationKnight(int x, int y, Coords c2, Board &obj, Pieces piece)
{
    // forward right
    if(c2.x == x + 1 && c2.y == y + 2 && ((obj.getpiece(x+1, y+2)->team != piece.team) || (obj.getpiece(x,y) != nullptr)))
        return true;
    // forward left
    else if(c2.x == x - 1 && c2.y == y + 2 && ((obj.getpiece(x-1, y+2)->team != piece.team )|| (obj.getpiece(x,y) != nullptr)))
        return true;
    // backward right
    else if(c2.x == x + 1 && c2.y == y - 2 && ((obj.getpiece(x+1, y-2)->team != piece.team)|| (obj.getpiece(x,y) != nullptr)))
        return true;
    // backward left
    else if(c2.x == x - 1 && c2.y == y - 2 && ((obj.getpiece(x-1, y-2)->team != piece.team)|| (obj.getpiece(x,y) != nullptr)))
        return true;
    // leftward up
    else if(c2.x == x - 2 && c2.y == y + 1 && ((obj.getpiece(x-2,y+1)->team != piece.team)|| (obj.getpiece(x,y) != nullptr)))
        return true;
    // leftward down
    else if(c2.x == x - 2 && c2.y == y - 1 && ((obj.getpiece(x-2,y-1)->team != piece.team)|| (obj.getpiece(x,y) != nullptr)))
        return true;
    // rightward up
    else if(c2.x == x + 2 && c2.y == y + 1 && ((obj.getpiece(x+2,y+1)->team != piece.team)|| (obj.getpiece(x,y) != nullptr)))
        return true;
    // rightward down
    else if(c2.x == x + 2 && c2.y == y - 1 && ((obj.getpiece(x+2,y-1)->team != piece.team)|| (obj.getpiece(x,y) != nullptr)))
        return true;
    // invalid
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
        if ((c2.y == column) && (c2.x == row + 1) && (row + 1 < 8)) // forward move
        {
            if (obj.getpiece(row + 1, column) == nullptr)
                return true;
        }
        else if ((c2.x == row + 1) && (c2.y == column + 1) && (column + 1 < 8) && (row + 1 < 8)) // left diagonal forward
        {
            if ((obj.getpiece(row+1,column+1) == nullptr))  
                return false;
            else if(obj.getpiece(row + 1, column + 1)->team != obj.getpiece(row,column)->team)
                return true;
        }
        else if ((c2.y == column - 1) && (c2.x == row + 1) && (row + 1 < 8) & (column - 1 >= 0)) // right diagonal forward
        {
            if ((obj.getpiece(row + 1, column - 1) == nullptr))
                return false;
            else if(obj.getpiece(row + 1, column - 1)->team != obj.getpiece(row, column)->team)
                return true;
        }
        else
            return false;
        break;

    case 'p':  // white Pawn
        if ((c2.y == column) && (c2.x == row - 1) && ((row - 1) >= 0)) // forward move
        {
            if (obj.getpiece(row-1,column) == nullptr)
                return true;
        }
        else if ((c2.x == row-1) && (c2.y == column+1) && (row - 1 >= 0) & (column + 1 < 8)) // right diagonal forward
        {
            if ((obj.getpiece(row - 1,column + 1) == nullptr))
                return false;
            else if(obj.getpiece(row - 1, column + 1)->team != obj.getpiece(row,column)->team)
                return true;
        }
        else if ((c2.x == row - 1) && (c2.y == column - 1) && (row - 1 >= 0) && (column - 1 >= 0)) // left diagonal forward
        {
            if ((obj.getpiece(row - 1,column - 1) == nullptr))
                return false;
            else if(obj.getpiece(row - 1,column - 1)->team != obj.getpiece(row,column)->team)
                return true;
        }
        else // invalid input for c2
            return false;
        break;

    case 'r': // white rook
    case 'R': // black rook
        return moveValidationRook(row, column, c2, obj);
    case 'b': // white bishop
    case 'B': // black bishop
        return moveValidationBishop(row, column, c2, obj);
    case 'q': // white queen
    case 'Q': // black queen
        return (moveValidationBishop(row, column, c2, obj) || moveValidationRook(row,column,c2, obj));
    case 'n': // white knight
    case 'N': // black knight
        return moveValidationKnight(row,column,c2,obj,piece);
    case 'k': // white king
    case 'K': // black king
        
    default:
    break;
    }
}