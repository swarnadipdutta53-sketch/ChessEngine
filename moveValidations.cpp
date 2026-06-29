#include "moveValidations.h"
#include "Board.h"
/*
    forwards and backwards are regarded here with respect to white side,
    this has its effect only on the backend, not in the frontend at all
*/
bool moveValidationRook(int x, int y, Coords c2, Board& obj)
{
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
                if (obj.getpiece(x,i) != NULL)
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
                if (obj.getpiece(i,y) != NULL)
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
    int found = 0;
    
    // right diagonal movement(forwards)
    int xi = x + 1, yi = y + 1;
    while(xi < 8 && yi < 8)
    {
        if((c2.x == xi) && (c2.y == yi))
            return true; // valid 
        if(obj.getpiece(xi,yi) != NULL)
            return false; // obstruction faced
        xi++;
        yi++;
    }
    // right diagonal movement(backwards)
    int xi = x - 1, yi = y - 1;
    while(xi >= 0 && yi >= 0)
    {
        if((c2.x == xi) && (c2.y == yi))
            return true; // valid
        if(obj.getpiece(xi,yi) != NULL)
            return false; // obstruction faced
        xi--;
        yi--;
    }
    // left diagonal movement(forwards)
    int xi = x-1, yi = y+1;
    while(xi >= 0 && yi < 8)
    {
        if((c2.x == xi) && (c2.y == yi))
            return true; // valid 
        if(obj.getpiece(xi,yi) != NULL)
            return false; // obstruction faced
        xi--;
        yi++;
    }
    // left diagonal movement(backwards)
    int xi = x+1, yi = y-1;
    while(xi < 8 && yi >= 0)
    {
        if((c2.x == xi) && (c2.y == yi))
            return true; // valid 
        if(obj.getpiece(xi,yi) != NULL)
            return false; // obstruction faced
        xi++;
        yi--;
    }
    return false; // invalid input for c2 for bishop
}

bool moveValidationKnight(int x, int y, Coords c2, Board &obj, Pieces piece)
{
    // forward right
    if(c2.x == x + 1 && c2.y == y + 2 && obj.getpiece(x+1, y+2)->team != piece.team)
        return true;
    // forward left
    else if(c2.x == x - 1 && c2.y == y + 2 && obj.getpiece(x-1, y+2)->team != piece.team)
        return true;
    // backward right
    else if(c2.x == x + 1 && c2.y == y - 2 && obj.getpiece(x+1, y-2)->team != piece.team)
        return true;
    // backward left
    else if(c2.x == x - 1 && c2.y == y - 2 && obj.getpiece(x-1, y-2)->team != piece.team)
        return true;
    // leftward up
    else if(c2.x == x - 2 && c2.y == y + 1 && obj.getpiece(x-2,y+1)->team != piece.team)
        return true;
    // leftward down
    else if(c2.x == x - 2 && c2.y == y - 1 && obj.getpiece(x-2,y-1)->team != piece.team)
        return true;
    // rightward up
    else if(c2.x == x + 2 && c2.y == y + 1 && obj.getpiece(x+2,y+1)->team != piece.team)
        return true;
    // rightward down
    else if(c2.x == x + 2 && c2.y == y - 1 && obj.getpiece(x+2,y-1)->team != piece.team)
        return true;
    // invalid
    else
        return false;
}

bool moveValidation(Pieces piece, Coords c2, Board &obj)
{
    bool result;
    int x = piece.coords.x;
    int y = piece.coords.y;

    if (c2.x == x && c2.y == y) // current coords of the piece
        return false;

    switch (piece.type)
    {
    case 'p':  // white pawn
        if ((c2.x == x) && (c2.y == y + 1) && (y + 1 < 8)) // forward move
        {
            if (obj.getpiece(x,y + 1) == NULL)
                return true;
            else
                return false;
        }
        else if ((c2.x == x + 1) && (c2.y == y + 1) && (y + 1 < 8) && (x + 1 < 8)) // right diagonal forward
        {
            if ((obj.getpiece(x+1,y+1) != NULL) && (obj.getpiece(x + 1,y + 1)->type == 'b'))
                return true;
            else
                return false;
        }
        else if ((c2.x == x - 1) && (c2.y == y + 1) && (y + 1 < 8) & (x - 1 >= 0)) // left diagonal forward
        {
            if ((obj.getpiece(x - 1,y + 1) != NULL) && (obj.getpiece(x - 1,y + 1)->type == 'b'))
                return true;
            else
                return false;
        }
        else // invalid input for c2
            return false;
        break;

    case 'P':  // black pawn
        if ((c2.x == x) && (c2.y == y - 1) && ((y - 1) >= 0)) // forward move
        {
            if (obj.getpiece(x,y - 1) == NULL)
                return true;
            else
                return false;
        }
        else if ((c2.x == x + 1) && (c2.y == y - 1) && (y - 1 >= 0) & (x + 1 < 8)) // right diagonal forward
        {
            if ((obj.getpiece(x + 1,y - 1) != NULL) && (obj.getpiece(x + 1,y - 1)->type == 'b'))
                return true;
            else
                return false;
        }
        else if ((c2.x == x - 1) && (c2.y == y - 1) && (y - 1 >= 0) && (x - 1 >= 0)) // left diagonal forward
        {
            if ((obj.getpiece(x - 1,y - 1) != NULL) && (obj.getpiece(x - 1,y - 1)->type == 'b'))
                return true;
            else
                return false;
        }
        else // invalid input for c2
            return false;
        break;

    case 'r': // white rook
    case 'R': // black rook
        return moveValidationRook(x, y, c2, obj);
    case 'b': // white bishop
    case 'B': // black bishop
        return moveValidationBishop(x, y, c2, obj);
    case 'q': // white queen
    case 'Q': // black queen
        return (moveValidationBishop(x, y, c2, obj) || moveValidationRook(x,y,c2, obj));
    case 'n': // white knight
    case 'N': // black knight
        return moveValidationKnight(x,y,c2,obj,piece);
    case 'k': // white king
    case 'K': // black king
        
    default:
    }
}