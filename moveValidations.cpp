#include "moveValidations.h"
#include "Board.h"
/*
    forwards and backwards are regarded here with respect to white side,
    this has its effect only on the backend, not in the frontend at all
*/
bool moveValidationRook(int x, int y, Coords c2)
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
                if (board[x][i] != NULL)
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
                if (board[i][y] != NULL)
                    return false; // obstruction faced
                i++;
            }
            return true; // no obstruction faced
        }
        else
            return false;
    }
}

bool moveValidationBishop(int x, int y, Coords c2)
{
    int found = 0;
    
    // right diagonal movement(forwards)
    int xi = x + 1, yi = y + 1;
    while(xi < 8 && yi < 8)
    {
        if((c2.x == xi) && (c2.y == yi))
            return true; // valid 
        if(board[xi][yi] != NULL)
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
        if(board[xi][yi] != NULL)
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
        if(board[xi][yi] != NULL)
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
        if(board[xi][yi] != NULL)
            return false; // obstruction faced
        xi++;
        yi--;
    }
    return false; // invalid input for c2 for bishop
}
bool moveValidation(Pieces piece, Coords c2)
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
            if (board[x][y + 1] == NULL)
                return true;
            else
                return false;
        }
        else if ((c2.x == x + 1) && (c2.y == y + 1) && (y + 1 < 8) && (x + 1 < 8)) // right diagonal forward
        {
            if ((board[x + 1][y + 1] != NULL) && (board[x + 1][y + 1]->type == 'b'))
                return true;
            else
                return false;
        }
        else if ((c2.x == x - 1) && (c2.y == y + 1) && (y + 1 < 8) & (x - 1 >= 0)) // left diagonal forward
        {
            if ((board[x - 1][y + 1] != NULL) && (board[x - 1][y + 1]->type == 'b'))
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
            if (board[x][y - 1] == NULL)
                return true;
            else
                return false;
        }
        else if ((c2.x == x + 1) && (c2.y == y - 1) && (y - 1 >= 0) & (x + 1 < 8)) // right diagonal forward
        {
            if ((board[x + 1][y - 1] != NULL) && (board[x + 1][y - 1]->type == 'b'))
                return true;
            else
                return false;
        }
        else if ((c2.x == x - 1) && (c2.y == y - 1) && (y - 1 >= 0) && (x - 1 >= 0)) // left diagonal forward
        {
            if ((board[x - 1][y - 1] != NULL) && (board[x - 1][y - 1]->type == 'b'))
                return true;
            else
                return false;
        }
        else // invalid input for c2
            return false;
        break;

    case 'r': // white rook
    case 'R': // black rook
        return moveValidationRook(x, y, c2);
        break;
    case 'b': // white bishop
    case 'B': // black bishop
        return moveValidationBishop(x, y, c2);
        break;
    case 'q': // white queen
    case 'Q': // black queen
        return (moveValidationBishop(x, y, c2) || moveValidationRook(x,y,c2));
    case 'n': // white knight
    case 'N': // black knight
    case 'k': // white king
    case 'K': // black king
        
    default:
    }
}