#include "moveValidations.h"
#include "Board.h"
#include "stdiodef.h"
/*
    
*/
bool moveValidationRook(int x, int y, Coords c2, Board& obj)
{
    printf("Rook called\n");
    return true;
    if (c2.x < 8 && c2.x >= 0 && c2.y < 8 && c2.x >= 0)
    {
        int i = 0;
        if (c2.x == x) // forward and backwards
        {
            while (i < 8)
            {
                if (i == y)
                {
                    i++;
                    continue;
                }
                if(i == c2.y)
                    return true; // valid
                if (obj.getpiece(x,i) != nullptr)
                    return false; // obstruction faced
                i++;
            }
        }
        else if (c2.y == y) // sideways
        {
            while (i < 8)
            {
                if (i == x)
                {
                    i++;
                    continue;
                }
                if(i == c2.x)
                    return true; // valid
                if (obj.getpiece(i,y) != nullptr)
                    return false; // obstruction faced
                i++;
            }
            return true; // no obstruction faced
        }
        else
            return false;
    }
}

bool moveValidationBishop(int x, int y, Coords c2, Board& obj)
{
    printf("bishop called\n");
    return true;

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
    printf("Rook called\n");
    return true;

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
    printf("here\n");
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
            else
            {
                printf("invalid input for c1");
                return false;
            }
        }
        else if ((c2.x == row + 1) && (c2.y == column + 1) && (column + 1 < 8) && (row + 1 < 8)) // left diagonal forward
        {
            if ((obj.getpiece(row+1,column+1) != nullptr))
            { 
                if(obj.getpiece(row + 1, column + 1)->team != obj.getpiece(row,column)->team)
                return true;
            }
            else
            {
                printf("invalid input for c2");
                return false;
            }
        }
        else if ((c2.y == column - 1) && (c2.x == row + 1) && (row + 1 < 8) & (column - 1 >= 0)) // right diagonal forward
        {
            if ((obj.getpiece(row + 1, column - 1) != nullptr))
            {
                if(obj.getpiece(row + 1, column - 1)->team != obj.getpiece(row, column)->team)
                return true;
            }
            else
            {
                printf("invalid input for c3");
                return false;
            }
        }
        else // invalid input for c2
        {
            printf("invalid input for c4");
            return false;
        }
        break;

    case 'p':  // white Pawn
        if ((c2.y == column) && (c2.x == row - 1) && ((row - 1) >= 0)) // forward move
        {
            if (obj.getpiece(row-1,column) == nullptr)
                return true;
            else
            {
                printf("invalid input1");
                return false;
            }
        }
        else if ((c2.x == row-1) && (c2.y == column+1) && (row - 1 >= 0) & (column + 1 < 8)) // right diagonal forward
        {
            if ((obj.getpiece(row - 1,column + 1) != nullptr))
            {
                if(obj.getpiece(row - 1, column + 1)->team != obj.getpiece(row,column)->team)
                return true;
            }
            else
            {
                printf("invalid input2");
                return false;
            }
        }
        else if ((c2.x == row - 1) && (c2.y == column - 1) && (row - 1 >= 0) && (column - 1 >= 0)) // left diagonal forward
        {
            if ((obj.getpiece(row - 1,column - 1) != nullptr))
            {
                if(obj.getpiece(row - 1,column - 1)->team != obj.getpiece(row,column)->team)
                return true;
            }
            else
            {
                printf("invalid input3");
                return false;  
            }
        }
        else // invalid input for c2
        {
            printf("invalid input4");
            return false;
        }
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
        
    default: return false;
    break;
    }
}