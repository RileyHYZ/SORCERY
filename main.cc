#include <iostream>

#include "game.h"
#include "display.h"
#include "point.h"

using namespace std;

int main(void) {
    Game g;
    TextDisplay t{&g, cout};

    g.notifyObservers();

    string cmd;

    while (cin >> cmd && cmd != "q") {
        if (cmd == "move") {
            Point start;
            Point end;
            cin >> start >> end;
        } else if (cmd == "restart") {
            g = Game();
        } else if (cmd == "defaultpromotion") {
            char d;
            cin >> d;
            g.getChessBoard()->setDefaultPromotionPiece(d);
        } else {
            cout << "Invalid command: " << cmd << endl; 
        }
    }
}