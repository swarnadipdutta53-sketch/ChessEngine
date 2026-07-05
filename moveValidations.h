#include "stdiodef.h"
#include "Board.h"
#define t_MOVVALID
#ifdef t_MOVVALID
ReturnType moveValidation(Pieces, Coords, Board&);
ReturnType moveValidationRook(int, int, Coords, Board&);
ReturnType moveValidationBishop(int, int, Coords, Board&);
ReturnType moveValidationKnight(int, int, Coords, Board&, Pieces);
ReturnType moveValidationKing(int, int, Coords, Board&);
#endif