#include <iostream>
#include "board.h"
#include "BoardIO.h"
#include "Evaluator.h"

int main()
{
    Board b;
    string mode;

    b.initialize();

    cout << "Press 0 for debug mode, 1 for normal mode\n";
    getline(cin, mode);

    if (!mode.empty() && mode[0] == '0')
        b.overWrite();

    bool whiteTurn = true;
    string input;

    b.printBoard(whiteTurn);

    while (true)
    {
        getline(cin, input);
        system("cls");

        if (input == "0") break;

        if (input == "2"){

            if (b.undoMove())whiteTurn = !whiteTurn;
            else cout << "No moves yet\n";

            cout << "Evaluation: "<< Evaluator::evaluate(b)<< "\n";
            b.printBoard(whiteTurn);
            continue;
        }

        Coords from, to;

        if (!parser(input, from, to)) cout << "Invalid input\n";

        else if (b.isEmpty(from)) cout << "No piece selected\n";

        else if (whiteTurn && b.getTeam(from) != 'w') cout << "It's White's turn\n";

        else if (!whiteTurn && b.getTeam(from) != 'b') cout << "It's Black's turn\n";

        else
        {
            bool movePlayed = false;

            vector<moves> legalMoves = b.generateLegalMoves(b.getpiece(from.x, from.y));

            for (const moves& move : legalMoves)
            {
                if (move.from.x == from.x &&
                    move.from.y == from.y &&
                    move.to.x == to.x &&
                    move.to.y == to.y){
                    
                    cout<<"making move...\n";
                    b.makeMove(move);

                    whiteTurn = !whiteTurn;
                    movePlayed = true;

                    break;
                }
            }


            if (!movePlayed){
                cout << "That piece can't move there\n";
            }

            else
            {
                char team = (whiteTurn)? 'w':'b';
                auto teamlegalmoves = b.generateAllLegalMoves(team);
                bool NoMoves = teamlegalmoves.empty();
                bool KingInCheck = b.isAttacked(b.getking(team));

                if(KingInCheck&&NoMoves){
                    cout<<"Checkmate by "<<(whiteTurn? "Black\n" : "White\n");
                    break;
                }
                else if(NoMoves){
                    cout<<"Stalemate by "<<(whiteTurn? "Black\n" : "White\n");
                    break;
                }
                else if(KingInCheck){
                    cout << (whiteTurn ? "White" : "Black") << " King in check\n";
                }
            }
        }

        cout << "Evaluation in favor of white: "
             << Evaluator::evaluate(b)
             << "\n";


        b.printBoard(whiteTurn);
    }


    return 0;
}