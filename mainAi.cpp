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

    cout << "Press 0 for debug mode, 1 for normal mode\n";
    getline(cin, mode);

    if (!mode.empty() && mode[0] == '0')
        b.overWrite();

    string input;

    b.printBoard();

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
            if (b.undoMove())
                b.FlipTurn();
            else
                cout << "No moves yet\n";

            b.printBoard();
            continue;
        }


        Coords from, to;

        if (!parser(input, from, to))
        {
            cout << "Invalid input\n";
            continue;
        }

        if (b.isEmpty(from))
        {
            cout << "No piece selected\n";
            continue;
        }

        if (b.getTeam(from) != 'w')
        {
            cout << "It's White's turn\n";
            continue;
        }


        bool movePlayed = false;

        vector<moves> legalMoves =
            b.generateLegalMoves(b.getpiece(from.x, from.y));


        for (const moves& move : legalMoves)
        {
            if (move.from.x == from.x &&
                move.from.y == from.y &&
                move.to.x == to.x &&
                move.to.y == to.y)
            {
                b.makeMove(move);
                b.FlipTurn();
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
        b.FlipTurn();


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