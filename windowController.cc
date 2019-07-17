#include "windowController.h"
#include "window.h"

#include <vector>

using namespace std;

WindowController::WindowController(Game &model, Xwindow &window) : model{model}, window{window} {
    cout<<"WINDCONTROL INIT DONE"<<endl;
}

Command WindowController::command() {
    vector<int> position = window.getSelectedCommand();
    if (position[1] > 73) return Command::DEFAULTPROMOTION;
    else if (position[0] < 95) return Command::MOVE;
    else if (position[0] < 150) return Command::RESTART;
    else if (position[0] <195) return Command::QUIT;
    else return Command::VALIDMOVES;
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
    if (x < 150) return 'q';
    else if (x < 190) return 'r';
    else if (x < 230) return 'b';
    else return 'n';
}


