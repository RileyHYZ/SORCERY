#include <iostream>

#include "game.h"
#include "output.h"
#include "point.h"
#include "exception.h"

using namespace std;

int main(void) {
    Game g;
    TextDisplay t{&g, cout};

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
        } else {
            cout << "Invalid command: " << cmd << endl; 
        }
    }
}