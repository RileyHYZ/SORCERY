#include "windowController.h"
#include "window.h"
#include "exception.h"

#include <vector>

using namespace std;

WindowController::WindowController(Xwindow &window, bool enhancementsOn) : window{window}, enhancementsOn{enhancementsOn} {}

Command WindowController::command() {
    vector<int> position = window.getSelectedCommand();
    if (position[1] > 106 && position[0] < 175) {
        enhancementsOn = !enhancementsOn;
        return Command::NONE;
    } else if (position[1] > 106) {
        return enhancementsOn ? Command::VALIDMOVES : throw InvalidCommandException();
    } 
    if (position[1] > 73) return Command::DEFAULTPROMOTION;
    if (position[0] < 95) return Command::MOVE;
    if (position[0] < 150) return Command::RESTART;
    return Command::QUIT;
}

Point& WindowController::point() {
    vector<int> position = window.getPointSelected();
    int y = (position[0] - 390) / 40;
    int x = (410 - position[1]) / 40;
    Point point {x, y};
    cout << "POINT is: "<<x <<", "<<y<<endl;
    return point;
}

char WindowController::piece() {
    int x = window.getSelectedPiece();
    if (x < 180) return 'q';
    else if (x < 220) return 'r';
    else if (x < 260) return 'b';
    else return 'n';
}


