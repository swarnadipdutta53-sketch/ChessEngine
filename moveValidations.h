#include "stdiodef.h"
#include "pieces.h"
#include "Board.h"
#define t_MOVVALID
#ifdef t_MOVVALID
enum class ReturnType
{
    en_valid, // enpassant
    cas_valid, // castling
    gen_valid, // general valid
    invalid // not valid
};
ReturnType moveValidation(Pieces, Coords, Board&);
ReturnType moveValidationRook(int, int, Coords, Board&);
ReturnType moveValidationBishop(int, int, Coords, Board&);
ReturnType moveValidationKnight(int, int, Coords, Board&, Pieces);
ReturnType moveValidationKing(int, int, Coords, Board&);
#endif