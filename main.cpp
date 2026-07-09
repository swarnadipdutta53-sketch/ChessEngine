#include <iostream>
#include "board.h"
#include "BoardIO.h"

int main(){
    Board b;
    b.initialize();
    b.printBoard(true);
    
    Coords from,to;
    bool p,whiteturn=true;
    string inp;
    while(true){
        getline(cin,inp);
        system("cls");
        if(inp=="0")exit(0);
        // if(inp=="1")b.printcapt();
        if(inp=="2"){
            if(b.undoMove())whiteturn=!whiteturn;
            else cout<<"No moves yet\n";
        }
        if(!parser(inp,from,to)){cout<<"Invalid input\n";}
        else if(b.isEmpty(from)){ cout << "No piece selected\n";}
        else if(whiteturn && b.getTeam(from) != 'w'){cout << "It's White's turn\n";}
        else if(!whiteturn && b.getTeam(from) != 'b'){cout << "It's Black's turn\n";}
        else{
            bool val=false;
            vector<moves> m=b.generatePseudoLegalMoves(b.getpiece(from.x,from.y));
            for(const moves& l:m){
                     if(l.from.x==from.x&&l.from.y==from.y&&l.to.x==to.x&&l.to.y==to.y){
                     b.makeMove(l);
                    whiteturn=!whiteturn;
                    val=true;
                     break;
                }     
            }    
            if(!val){cout<<"That Piece cant move like that\n";}    
        }
        b.printBoard(whiteturn);
    }
}
