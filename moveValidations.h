#include "stdiodef.h"
#include "pieces.h"
#include "Board.h"
#define t_MOVVALID
#ifdef t_MOVVALID
bool MoveValidation(Pieces, Coords, Board&);
bool moveValidationRook(int, int, Coords, Board&);
bool moveValidationBishop(int, int, Coords, Board&);
bool moveValidationKnight(int, int, Coords, Board&, Pieces);
#endif