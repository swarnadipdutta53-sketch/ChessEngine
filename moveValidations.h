#include "stdiodef.h"
#include "pieces.h"
#include "Board.h"
#define t_MOVVALID
#ifdef t_MOVVALID
typedef enum ReturnType
{
    en_valid, // enpassant
    cas_valid, // castling
    gen_valid, // general valid
    invalid // not valid
}ReturnType;
ReturnType moveValidation(Pieces, Coords, Board&);
ReturnType moveValidationRook(int, int, Coords, Board&);
ReturnType moveValidationBishop(int, int, Coords, Board&);
ReturnType moveValidationKnight(int, int, Coords, Board&, Pieces);
#endif