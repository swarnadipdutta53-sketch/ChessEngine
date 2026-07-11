#include "Board.h"
#include <iostream>
#define CHECKPIECE(x1, y1, x2, y2) (board[x1][y1] == board[x2][y2])
#define CHECKTEAM(x1, y1, x2, y2) ((board[x1][y1]->team) == (board[x2][y2]->team)) // only used when (x1, y1)  != (x2, y2)
#define CHECKPIECETYPE(x1, y1, t) ((board[x1][y1]->type) == t)
#define CHECKPAWN(x1, y1) (CHECKPIECETYPE(x1, y1, 'P') || CHECKPIECETYPE(x1, y1, 'p'))
#define CHECKBOUND(x, y) ((x >= 0) && (x < 8) && (y >= 0) && (y < 8))
#define CHECKPROMOTION(x) ((x == 7) || (x == 0))
#define GETTEAM(x1, y1) (board[x1][y1]->team)
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
vector<moves> Board::generatePseudoLegalMovesKing(Pieces *piece)
{
    vector<moves> ret;
    Coords directions[] = {{1, 0}, {1, 1}, {1, -1}, {-1, 0}, {-1, 1}, {-1, -1}, {0, 1}, {0, -1}};
    Coords currPos = {piece->coords.x, piece->coords.y};
    Coords castDirections[] = {{-4, -1}, {3, 1}};
    int xi, yi;
    bool castFlag;
    // normal case
    for (Coords dir : directions)
    {
        xi = currPos.x + dir.x;
        yi = currPos.y + dir.y;
        if (CHECKBOUND(xi, yi))
        {
            if (board[xi][yi] != nullptr)
            {
                if (!CHECKTEAM(currPos.x, currPos.y, xi, yi))
                    ret.push_back({{currPos.x, currPos.y}, {xi, yi}, piece, board[xi][yi], MoveType::GENERAL});
            }
            else
                ret.push_back({{currPos.x, currPos.y}, {xi, yi}, piece, board[xi][yi], MoveType::GENERAL});
        }
    }
    // castle case
    if (!(piece->hasMoved))
    {
        for (Coords dir : castDirections)
        {
            if (board[currPos.x][currPos.y + dir.x] != nullptr)
            {
                castFlag = true;
                if (CHECKPIECETYPE(currPos.x, currPos.y + dir.x, 'r') || CHECKPIECETYPE(currPos.x, currPos.y + dir.x, 'R'))
                {
                    if (!(board[currPos.x][currPos.y + dir.x]->hasMoved)) // checking rook hasnt moved
                    {
                        // check obstruction
                        yi = currPos.y + dir.y;
                        while (yi != currPos.y + dir.x)
                        {
                            if (board[currPos.x][yi] != nullptr) // obstruction faced
                            {
                                castFlag = false;
                                break;
                            }
                            yi += dir.y;
                        }
                        if (castFlag)
                            ret.push_back({{currPos.x, currPos.y}, {currPos.x, currPos.y + 2 * dir.y}, piece, nullptr, MoveType::CASTLING, board[currPos.x][currPos.y + dir.x]});
                    }
                }
            }
        }
    }
    return ret;
}
vector<moves> Board::generatePseudoLegalMovesKnight(Pieces *piece)
{
    vector<moves> ret;
    Coords currPos = {piece->coords.x, piece->coords.y};
    for (int doub : {-2, 2})
    {
        for (int single : {-1, 1})
        {
            // double vertial movement
            if (CHECKBOUND(currPos.x + doub, currPos.y + single))
            {
                if (board[currPos.x + doub][currPos.y + single] != nullptr)
                {
                    if (!CHECKTEAM(currPos.x, currPos.y, currPos.x + doub, currPos.y + single))
                        ret.push_back({{currPos.x, currPos.y}, {currPos.x + doub, currPos.y + single}, piece, board[currPos.x + doub][currPos.y + single], MoveType::GENERAL});
                }
                else
                    ret.push_back({{currPos.x, currPos.y}, {currPos.x + doub, currPos.y + single}, piece, board[currPos.x + doub][currPos.y + single], MoveType::GENERAL});
            }
            // double horizontal movement
            if (CHECKBOUND(currPos.x + single, currPos.y + doub))
            {
                if (board[currPos.x + single][currPos.y + doub] != nullptr)
                {
                    if (!CHECKTEAM(currPos.x, currPos.y, currPos.x + single, currPos.y + doub))
                        ret.push_back({{currPos.x, currPos.y}, {currPos.x + single, currPos.y + doub}, piece, board[currPos.x + single][currPos.y + doub], MoveType::GENERAL});
                }
                else
                    ret.push_back({{currPos.x, currPos.y}, {currPos.x + single, currPos.y + doub}, piece, board[currPos.x + single][currPos.y + doub], MoveType::GENERAL});
            }
        }
    }
    return ret;
}
vector<moves> Board::generatePseudoLegalMovesRook(Pieces *piece)
{
    vector<moves> ret;
    Coords currPos = {piece->coords.x, piece->coords.y};
    Coords directions[] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (Coords dir : directions)
    {
        int dx = dir.x, dy = dir.y, xi = currPos.x + dx, yi = currPos.y + dy;
        while (CHECKBOUND(xi, yi))
        {
            if (board[xi][yi] != nullptr)
            {
                if (!CHECKTEAM(currPos.x, currPos.y, xi, yi))
                    ret.push_back({{currPos.x, currPos.y}, {xi, yi}, piece, board[xi][yi], MoveType::GENERAL});
                break;
            }
            else
                ret.push_back({{currPos.x, currPos.y}, {xi, yi}, piece, board[xi][yi], MoveType::GENERAL});
            xi += dx;
            yi += dy;
        }
    }
    return ret;
}
vector<moves> Board::generatePseudoLegalMovesBishop(Pieces *piece)
{
    vector<moves> ret;
    Coords currPos = {piece->coords.x, piece->coords.y};
    Coords directions[] = {{1, 1}, {-1, -1}, {-1, 1}, {1, -1}};
    for (Coords dir : directions)
    {
        int dx = dir.x, dy = dir.y, xi = currPos.x + dx, yi = currPos.y + dy;
        while (CHECKBOUND(xi, yi))
        {
            if (board[xi][yi] != nullptr)
            {
                if (!CHECKTEAM(currPos.x, currPos.y, xi, yi))
                    ret.push_back({{currPos.x, currPos.y}, {xi, yi}, piece, board[xi][yi], MoveType::GENERAL});
                break;
            }
            else
                ret.push_back({{currPos.x, currPos.y}, {xi, yi}, piece, board[xi][yi], MoveType::GENERAL});
            xi += dx;
            yi += dy;
        }
    }
    return ret;
}
vector<moves> Board::generatePseudoLegalMovesPawn(Pieces *piece)
{
    vector<moves> ret;
    Coords currPos = {piece->coords.x, piece->coords.y};
    bool adjacent[2] = {false, false};
    int dx = (piece->type == 'p') ? -1 : 1; // dy = 0(forward) , 1 , -1
    // en-passant
    // checking if adjacent pawn is enabling enpassant, if yes then assigning it to the adjacent
    int i = 0;
    for (int dy : {-1, 1}) // checking adjascency
    {
        if (CHECKBOUND(currPos.x, currPos.y + dy))
        {
            if (board[currPos.x][currPos.y + dy] != nullptr)
            {
                if (CHECKPAWN(currPos.x, currPos.y + dy) && !CHECKTEAM(currPos.x, currPos.y, currPos.x, currPos.y + dy) && getlastmovedpiece() == board[currPos.x][currPos.y + dy] && (abs(movehistory.back().to.x - movehistory.back().from.x) == 2))
                    adjacent[i] = true;
            }
        }
        i++;
    }
    if (adjacent[0]) // left side enpassant
        ret.push_back({{currPos.x, currPos.y}, {dx + currPos.x, currPos.y - 1}, piece, board[currPos.x][currPos.y - 1], MoveType::EN_PASSANT});
    if (adjacent[1]) // right side enpassant
        ret.push_back({{currPos.x, currPos.y}, {dx + currPos.x, currPos.y + 1}, piece, board[currPos.x][currPos.y + 1], MoveType::EN_PASSANT});

    if (CHECKBOUND(currPos.x + 2 * dx, currPos.y) && CHECKBOUND(currPos.x + dx, currPos.y)) // double forward
    {
        if (!(piece->hasMoved) && board[currPos.x + dx * 2][currPos.y + 0] == nullptr && board[currPos.x + dx][currPos.y] == nullptr)
            ret.push_back({{currPos.x, currPos.y}, {2 * dx + currPos.x, currPos.y + 0}, piece, board[currPos.x + dx * 2][currPos.y], MoveType::GENERAL});
    }

    if (CHECKBOUND(currPos.x + dx, currPos.y)) // single forward
    {
        if (board[dx + currPos.x][currPos.y] == nullptr)
        {
            // promotion hanlde
            if (CHECKPROMOTION(currPos.x + dx))
                ret.push_back({{currPos.x, currPos.y}, {currPos.x + dx, currPos.y}, piece, board[currPos.x + dx][currPos.y], MoveType::PROMOTION});
            else
                ret.push_back({{currPos.x, currPos.y}, {dx + currPos.x, currPos.y}, piece, board[currPos.x + dx][currPos.y], MoveType::GENERAL});
        }
    }

    for (int dy : {-1, 1})
    {
        if (CHECKBOUND(currPos.x + dx, currPos.y + dy))
        {
            if (board[dx + currPos.x][currPos.y + dy] != nullptr) // left diagonal capture (w.r.t white)
            {
                if (!CHECKTEAM(dx + currPos.x, currPos.y + dy, currPos.x, currPos.y))
                {
                    if (CHECKPROMOTION(currPos.x + dx)) // promotion handle
                        ret.push_back({{currPos.x, currPos.y}, {currPos.x + dx, currPos.y + dy}, piece, board[currPos.x + dx][currPos.y + dy], MoveType::PROMOTION});
                    else
                        ret.push_back({{currPos.x, currPos.y}, {dx + currPos.x, currPos.y + dy}, piece, board[currPos.x + dx][currPos.y + dy], MoveType::GENERAL});
                }
            }
        }
    }
    return ret;
}
vector<moves> Board::generatePseudoLegalMoves(Pieces *piece)
{
    vector<moves> retB, retR;
    switch (piece->type)
    {
    // for pawn
    case 'p':
    case 'P':
        return generatePseudoLegalMovesPawn(piece);

    // for rook
    case 'r':
    case 'R':
        return generatePseudoLegalMovesRook(piece);
    // for bishop
    case 'b':
    case 'B':
        return generatePseudoLegalMovesBishop(piece);
    // for Queen
    case 'q':
    case 'Q':
        retB = generatePseudoLegalMovesBishop(piece);
        retR = generatePseudoLegalMovesRook(piece);
        retB.insert(retB.end(), retR.begin(), retR.end());
        return retB;
    // for knight
    case 'n':
    case 'N':
        return generatePseudoLegalMovesKnight(piece);
    // for king
    case 'k':
    case 'K':
        return generatePseudoLegalMovesKing(piece);
    default:
        cout << "Invalid Piece Selection Error From LegalMovesGenerator: 1.0";
        return {};
    }
}
bool Board::isAttacked(Pieces *p)
{
    if (p->team == 'b')
    {
        for (Pieces *index : whitepieces)
        {
            if (index->alive && canAttack(p->coords, index))
                return true;
        }
    }
    else
    {
        for (Pieces *index : blackpieces)
        {
            if (index->alive && canAttack(p->coords, index))
                return true;
        }
    }
    return false;
}
bool Board::isCellAttacked(Coords c, char team)
{
    if (team == 'b')
    {
        for (Pieces *index : whitepieces)
        {
            if (index->alive && canAttack(c, index))
                return true;
        }
    }
    else
    {
        for (Pieces *index : blackpieces)
        {
            if (index->alive && canAttack(c, index))
                return true;
        }
    }
    return false;
}
bool Board::canAttack(Coords c, Pieces *piece)
{
    switch (piece->type)
    {
    case 'P':
        return (c.x == piece->coords.x + 1 &&
                abs(c.y - piece->coords.y) == 1);
    case 'p':
        return (c.x == piece->coords.x - 1 &&
                abs(c.y - piece->coords.y) == 1);
    default:
        if (moveValidation(*piece, c, *this) != MoveType::INVALID)
            return true;
        else
            return false;
    }
}
vector<moves> Board::generateLegalMoves(Pieces *piece)
{
    vector<moves> retlegal = generatePseudoLegalMoves(piece);
    for (auto it = retlegal.begin(); it != retlegal.end();)
    {
        if (it->movetype == MoveType::CASTLING)
        {
            bool flagRem = false;
            int step = (it->to.y > piece->coords.y) ? 1 : -1;
            int yi = it->from.y;
            while (true)
            {
                if (isCellAttacked({piece->coords.x, yi}, piece->team))
                {
                    flagRem = true;
                    break;
                }
                if (yi == it->to.y)
                    break;
                yi += step;
            }
            if (flagRem)
                it = retlegal.erase(it);
            else
                ++it;
            continue;
        }
        makeMove(*it);
        if (isAttacked(getking(piece->team)))
            it = retlegal.erase(it);
        else
            ++it;
        undoMove();
    }
    return retlegal;
}