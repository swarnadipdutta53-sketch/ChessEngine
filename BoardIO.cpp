#include "BoardIO.h"
using namespace std;
bool parser(string inp, Coords &from, Coords &to)
{
    char ch;
    int tempOrds, scanX = 0, scanY = -1; // X scans source, Y scans destination
    from = {-1, -1}; to = {-1, -1};
    for(auto len = inp.begin(); len != inp.end(); ++len)
    {
        if(scanY == 0) scanX = -1; // stop source scanning, start destination scanning
        ch = tolower(*len);
        if(ch == ' ') continue;
        // coordinate encoding
        if(ch >= '1' && ch <= '8') tempOrds = '8' - ch;   
        else if(ch >= 'a' && ch <= 'h') tempOrds = ch - 'a';   
        else return false;
        if(scanX < 2 && scanX >= 0)
        {
            if(scanX == 0 && ch >= 'a' && ch <= 'h') from.y = tempOrds;
            else if(scanX == 1 && ch >= '1' && ch <= '8')
            {
                from.x = tempOrds;
                scanY = 0;
            }
            else return false;
            scanX++;
        }
        else if(scanY >= 0 && scanY < 2)
        {
            if(scanY == 0 && ch >= 'a' && ch <= 'h') to.y = tempOrds;
            else if(scanY == 1 && ch >= '1' && ch <= '8') to.x = tempOrds;
            else return false;
            scanY++;
        }
        else return false; // extra characters
    }
    if(from.x != -1 && from.y != -1 &&
       to.x != -1 && to.y != -1)
        return true;
    return false;
}   


bool Board::loadFEN(const string& fen)

{
    cout << "LOAD FEN START\n";

     clearBoard();

    stringstream ss(fen);
    vector<string> fields;
    string temp;

    while (ss >> temp)
    fields.push_back(temp);

    if(fields.size() != 6)
        return false;

    if(!loadPieces(fields[0])) return false;
    if(!setTurn(fields[1][0])) return false;
    if(!loadCastling(fields[2])) return false;
    if(!loadEnPassant(fields[3])) return false;
    // if(!loadHalfMove(fields[4])) return false;
    // if(!loadFullMove(fields[5])) return false;

    return true;
}

void Board::clearBoard(){

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            board[i][j]=nullptr;
        }
    }

    movehistory.clear();
    capturedpieces.clear();

    for(int i=0;i<32;i++){
        pieces[i].alive=false;
        pieces[i].hasMoved=0;
    }
}


bool Board::loadPieces(string s){
    int WhitePawn=0,WhiteRook=0,WhiteBishop=0,WhiteKnight=0,WhiteKing=0,WhiteQueen=0;
    int WhitePawnIndex=24,WhiteRookIndex=16,WhiteBishopIndex=18,WhiteKnightIndex=17;
    int BlackPawn=0,BlackRook=0,BlackBishop=0,BlackKnight=0,BlackKing=0,BlackQueen=0;
    int BlackPawnIndex=8,BlackRookIndex=0,BlackBishopIndex=2,BlackKnightIndex=1;
    int r=0,c=0;
    for(auto it:s){
        if(it=='/'){
            if(c!=8) return false;
            if(r>7) return false;
            r++;
            c=0;
        }
        else if(isdigit(it)){c+=(it-'0'); if(c>8)return false;}
        else if(isalpha(it)){
            if(c==8) return false;
            if(isupper(it)){
                switch(it){
                    case 'P': 
                        if(WhitePawn==8)return false;
                        board[r][c]=&pieces[WhitePawnIndex];
                        pieces[WhitePawnIndex].alive=true;
                        pieces[WhitePawnIndex].coords={r,c};
                        WhitePawn++;
                        c++;
                        WhitePawnIndex++;
                        break;
                    case 'R': 
                        if(WhiteRook==2)return false;
                        board[r][c]=&pieces[WhiteRookIndex];
                        pieces[WhiteRookIndex].alive=true;
                        pieces[WhiteRookIndex].coords={r,c};
                        WhiteRook++;
                        c++;
                        WhiteRookIndex+=7;
                        break;
                    case 'B': 
                        if(WhiteBishop==2)return false;
                        board[r][c]=&pieces[WhiteBishopIndex];
                        pieces[WhiteBishopIndex].alive=true;
                        pieces[WhiteBishopIndex].coords={r,c};
                        WhiteBishop++;
                        c++;
                        WhiteBishopIndex+=3;
                        break;
                    case 'N': 
                        if(WhiteKnight==2)return false;
                        board[r][c]=&pieces[WhiteKnightIndex];
                        pieces[WhiteKnightIndex].alive=true;
                        pieces[WhiteKnightIndex].coords={r,c};
                        WhiteKnight++;
                        c++;
                        WhiteKnightIndex+=5;
                        break;
                    case 'Q': 
                        if(WhiteQueen==1)return false;
                        board[r][c]=&pieces[19];
                        pieces[19].alive=true;
                        pieces[19].coords={r,c};
                        WhiteQueen++;
                        c++;
                        break;
                    case 'K': 
                        if(WhiteKing==1)return false;
                        board[r][c]=&pieces[20];
                        pieces[20].alive=true;
                        pieces[20].coords={r,c};
                        WhiteKing++;
                        c++;
                        break;
                    default: return false;
                }
            }
            else {
                    switch(it){
                    case 'p': 
                        if(BlackPawn==8)return false;
                        board[r][c]=&pieces[BlackPawnIndex];
                        pieces[BlackPawnIndex].alive=true;
                        pieces[BlackPawnIndex].coords={r,c};
                        BlackPawn++;
                        c++;
                        BlackPawnIndex++;
                        break;
                    case 'r': 
                        if(BlackRook==2)return false;
                        board[r][c]=&pieces[BlackRookIndex];
                        pieces[BlackRookIndex].alive=true;
                        pieces[BlackRookIndex].coords={r,c};
                        BlackRook++;
                        c++;
                        BlackRookIndex+=7;
                        break;
                    case 'b': 
                        if(BlackBishop==2)return false;
                        board[r][c]=&pieces[BlackBishopIndex];
                        pieces[BlackBishopIndex].alive=true;
                        pieces[BlackBishopIndex].coords={r,c};
                        BlackBishop++;
                        c++;
                        BlackBishopIndex+=3;
                        break;
                    case 'n': 
                        if(BlackKnight==2)return false;
                        board[r][c]=&pieces[BlackKnightIndex];
                        pieces[BlackKnightIndex].alive=true;
                        pieces[BlackKnightIndex].coords={r,c};
                        BlackKnight++;
                        c++;
                        BlackKnightIndex+=5;
                        break;
                    case 'q': 
                        if(BlackQueen==1)return false;
                        board[r][c]=&pieces[3];
                        pieces[3].alive=true;
                        pieces[3].coords={r,c};
                        BlackQueen++;
                        c++;
                        break;
                    case 'k': 
                        if(BlackKing==1)return false;
                        board[r][c]=&pieces[4];
                        pieces[4].alive=true;
                        pieces[4].coords={r,c};
                        BlackKing++;
                        c++;
                        break;
                    default: return false;
                }

            }
        }

        else return false;

    }
    if(c!=8 || r!=7) return false;
    return true;
}

bool Board::loadCastling(string s){
    CastlingRights=0;
    if(s.length()>4)return false;
    for(const char& c:s){
        if(c=='-'){CastlingRights=0; return true;}
        else if(c=='K'){CastlingRights|=WK;}
        else if(c=='Q'){CastlingRights|=WQ;}
        else if(c=='k'){CastlingRights|=BK;}
        else if(c=='q'){CastlingRights|=BQ;}
        else return false;
    }
    return true;
}

bool Board::loadEnPassant(string s){
    En_PassantTargetSquare={-1,-1};
    int len=s.length();
    if(len>2||len<1)return false;
    if(len==1){if(s!="-")return false; return true;}
    else {
        if(!isalpha(s[0]))return false;
        En_PassantTargetSquare.y=s[0]-'a';

        if(!isdigit(s[1]))return false;
        En_PassantTargetSquare.x='8'-s[1];
    }
    return true;
}