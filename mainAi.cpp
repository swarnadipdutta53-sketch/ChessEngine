#include <iostream>
#include "board.h"
#include "BoardIO.h"
#include "Evaluator.h"
#include "ChessAI.h"   

int main()
{
    Board b;
    string mode;

    b.initialize();
    Zobrist::initialize();
    // cout << b.perft(1, 'w') << endl;
    // cout << b.perft(2, 'w') << endl;
    // cout << b.perft(3, 'w') << endl;
    // cout << b.perft(4, 'w') << endl;
    // cout << b.perft(5, 'w') << endl;
    // cout << b.perft(6, 'w') << endl;


    cout << "Press 0 for debug mode, 1 for normal mode, 3 for fen loader\n";
    getline(cin, mode);

    if (!mode.empty() && mode[0] == '0') b.overWrite();
    if (!mode.empty() && mode[0] == '3'){
        string x; cout<<"enter fen pos :"; getline(cin, x); 
        if(!(b.loadFEN(x))){
            cout<<"Invalid Fen \n";
            b.initialize();
        }
    }

    string input;
    b.printBoard();

    if (!b.getTurn()){
    cout << "AI thinking...\n";

    ChessAI::setnode();
    moves aiMove = ChessAI::findBestMove(b, false, 0);
    ChessAI::getnode();

    b.makeMove(aiMove);

    cout << "AI played\n";

    b.printBoard();
    }

    while (true)
    {
        // =====================
        // WHITE HUMAN TURN
        // =====================

        getline(cin, input);
        system("cls");

        if (input == "0")
            break;

        if (input == "2")
        {
            if (!b.undoMove())
                cout << "No moves yet\n";

            b.printBoard();
            continue;
        }


        Coords from, to;

        if (!parser(input, from, to))
        {
            cout << "Invalid input\n";
            b.printBoard();
            continue;
        }

        if (b.isEmpty(from))
        {
            cout << "No piece selected\n";
            b.printBoard();
            continue;
        }

        if (b.getTeam(from) != 'w')
        {
            cout << "It's White's turn\n";
             b.printBoard();
            continue;
        }


        bool movePlayed = false;

        vector<moves> legalMoves =
            b.generateLegalMoves(b.getpiece(from.x, from.y));


        for ( moves& move : legalMoves)
        {
            if (move.from.x == from.x &&
                move.from.y == from.y &&
                move.to.x == to.x &&
                move.to.y == to.y)
            {
                if(move.movetype==MoveType::PROMOTION){
                    char promt;
                    prom:
                    cout<<"Enter promotion type for pawn: "<<endl;
                    cin>>promt;
                    promt=toupper(promt);
                    switch(promt){
                        case 'Q': move.promotiontype=PromotionType::QUEEN;break;
                        case 'R': move.promotiontype=PromotionType::ROOK;break;
                        case 'B': move.promotiontype=PromotionType::BISHOP;break;
                        case 'N': move.promotiontype=PromotionType::KNIGHT;break;
                        default: cout<<"Wrong promotion type"<<endl; goto prom;
                    }
                }
                b.makeMove(move);
                movePlayed = true;
                break;
            }
        }


        if (!movePlayed)
        {
            cout << "That piece can't move there\n";
            b.printBoard();
            continue;
        }


        // =====================
        // BLACK AI TURN
        // =====================

        cout << "AI thinking...\n";

        ChessAI::setnode();
        moves aiMove = ChessAI::findBestMove(b,false,0);

        cout<<"Found move\n";
        ChessAI::getnode();
        b.makeMove(aiMove);


        cout << "AI played\n";


        // =====================
        // CHECK GAME STATE
        // =====================

        char team = b.getTurn() ? 'w' : 'b';

        auto legal =
            b.generateAllLegalMoves(team);

        bool noMoves = legal.empty();
        bool inCheck = b.isAttacked(b.getking(team));


        if (inCheck && noMoves)
        {
            cout << "Checkmate by "
                 << (team == 'w' ? "Black\n" : "White\n");
            break;
        }

        if (noMoves)
        {
            cout << "Stalemate\n";
            break;
        }

        if (inCheck)
        {
            cout << (team == 'w' ? "White" : "Black")
                 << " King in check\n";
        }


        cout << "Evaluation: "
             << Evaluator::evaluate(b)
             << "\n";

        b.printBoard();
    }


    return 0;
}