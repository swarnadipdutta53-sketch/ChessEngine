#include "Zobrist.h"
#include "Board.h"
#include <random>
namespace Zobrist{

    uint64_t Piece[12][64];
    uint64_t Castle[16];
    uint64_t En_pass[8];
    uint64_t Turn;

    void initialize(){
        std::mt19937_64 zob(123456789);

        for(int i=0;i<12;i++){
            for(int j=0;j<64;j++){
                Piece[i][j]=zob();
            }
        }

        for(int i=0;i<16;i++){
            if(i<8)En_pass[i]=zob();
            Castle[i]=zob();
        }
        Turn=zob();
    }

   uint64_t computeHash(const Board& b){
        uint64_t hash=0;
        for(const Pieces* p:b.getWhitePieces()){
            if(p->alive)
            hash^=Piece[pieceIndex(p->type)][squareIndex(p->coords)];
        }

        for(const Pieces* p:b.getBlackPieces()){
            if(p->alive)
            hash^=Piece[pieceIndex(p->type)][squareIndex(p->coords)];
        }

        hash^=Castle[b.getCastle()];
        if(b.getEn_file()!=-1) hash^=En_pass[b.getEn_file()];
        if(b.getTurn())hash^=Turn;

        return hash;
   }
}