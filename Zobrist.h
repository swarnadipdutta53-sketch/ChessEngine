#pragma once
#include <cstdint>

class Board;

namespace Zobrist{

    extern uint64_t Piece[12][64]; 
    extern uint64_t Castle[16]; 
    extern uint64_t En_pass[8]; 
    extern uint64_t Turn; 

    void initialize();
    uint64_t computeHash(const Board& b);
}