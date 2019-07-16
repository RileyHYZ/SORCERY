#include <iostream>

#include "game.h"
#include "display.h"
#include "point.h"
#include "exception.h"

using namespace std;

int main(void) {
    Game g;
    TextDisplay t{&g, cout};
    bool enhancementsOn = false;

    g.notifyObservers();

    string cmd;

    while (cin >> cmd && cmd != "q") {
        if (cmd == "move") {
            Point curPos;
            Point newPos;
            cin >> curPos >> newPos;

            try {
                g.playTurn(curPos, newPos);
            } catch (InvalidMoveException& e) {
                cerr << e.what() << endl;
            }
        } else if (cmd == "restart") {
            g = Game();
        } else if (cmd == "defaultpromotion") {
            char piece;
            cin >> piece;
            
            try {
                g.setDefaultPromotionPiece(piece);
            } catch (InvalidDefaultPromotionPieceException& e) {
                cerr << e.what() << endl;
            }
        }  else if (enhancementsOn && cmd == "validmoves") {
            Point pos;
            cin >> pos;
            try {
                g.showValidMoves(pos);
            } catch (InvalidMoveException& e) {
                cerr << e.what() << endl;
            }
        } else if (cmd == "enhancements") {
            string s;
            cin >> s;
            enhancementsOn = s == "on" ? true : false;
        } else {
            cout << "Invalid command: " << cmd << endl; 
        }
    }
}