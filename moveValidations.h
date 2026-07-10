#include "stdiodef.h"
#include "Board.h"
#define t_MOVVALID
#ifdef t_MOVVALID
MoveType moveValidation(Pieces, Coords, Board&);
MoveType moveValidationRook(int, int, Coords, Board&);
MoveType moveValidationBishop(int, int, Coords, Board&);
MoveType moveValidationKnight(int, int, Coords, Board&, Pieces);
MoveType moveValidationKing(int, int, Coords, Board&);
#endif