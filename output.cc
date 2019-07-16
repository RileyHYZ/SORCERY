#include <iostream>

#include "output.h"
#include "game.h"
#include "square.h"
#include "card.h"
#include "exception.h"

using namespace std;

// Output

// Constructor

Output::Output(Game* subject) : subject{subject} {}

// Destructor

Output::~Output() {}

// Accessors

Game* Output::getSubject() {
    return subject;
}

// TextDisplay

// Constructor

TextDisplay::TextDisplay(Game* subject, ostream& out) : Output{subject}, out{out} {
    getSubject()->attach(this);
}

// Destructor

TextDisplay::~TextDisplay() {
    getSubject()->detach(this);
}

// Public Methods

void TextDisplay::notify() {
    ChessBoard* board = getSubject()->getChessBoard();
    int col = 0;
    int row = 8;

    vector<int> hp = board->getHP();

    for (Square& square : *board) {
        if (col == 0) {
            out << row << " ";
            --row;
        }

        out << '|';

        if (square.getPiece() != nullptr) {
            out << square.getPiece()->getDisplayIcon();
        } else if (square.getColor() == BLACK) {
            out << " ";
        } else {
            out << "\u2588";
        }

        if (col == 7) {
            out << "|\n";
            col = 0;
        } else {
            ++col;
        }
    }
    out << "   A B C D E F G H" << endl;

    out << "The white player's king has " << hp.at(WHITE) << " HP." << endl;
    out << "The black player's king has " << hp.at(BLACK) << " HP." << endl;

    if (getSubject()->getLastCardApplied() != Card::NONE) {
        out << "The card that was played in this turn was " << getSubject()->getLastCardApplied().getName() << ". " << getSubject()->getLastCardApplied().getDescription() << endl;
    } else {
        out << "No card was played in this turn." << endl;
    }
    
    if (getSubject()->getWinner() == WHITE) {
        out << "The white player wins!" << endl;
    } else if (getSubject()->getWinner() == BLACK) {
        out << "The black player wins!" << endl;
    } else if (getSubject()->isTie()) {
        out << "The game ends in a tie." << endl;
    }
}

// Graphical Display

// Constructor

GraphicalDisplay::GraphicalDisplay(Game* subject) : Output{subject} {
    window = new Xwindow{};
    getSubject()->attach(this);
}

// Destructor

GraphicalDisplay::~GraphicalDisplay() {
    delete window;
    getSubject()->detach(this);
}

// Private Method

Point& GraphicalDisplay::getPoint(vector<int> position) {
    int y = (position[0] - 390) / 40;
    int x = (410 - position[1]) / 40;
    Point pt {x, y};
    cout << "POINT is: "<<x <<", "<<y<<endl;
    return pt;
}

// Public Method

void GraphicalDisplay::notify() {
    ChessBoard* board = getSubject()->getChessBoard();
    window->clearWindow();
    window->drawRectangle(390, 90, 320, 320, 1);
    for (int i = 0; i < 8; i ++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0) {
                window->fillRectangle(390 + 40 * j, 90 + 40 * i, 40, 40, 1);
            }
        }
    }
    vector<int> hp = board->getHP();
    for(int i = 0; i < hp.at(WHITE); i++) {
        window->fillRectangle(340 + 30 * i, 460, 20, 20, 2);
    }
    for(int i = 0; i < hp.at(BLACK); i++) {
        window->fillRectangle(340 + 30 * i, 30, 20, 20, 2);
    }
    int row = 0, col = 0;
    for (Square& square : *board) {
        if (square.getPiece() != nullptr) {
            string path;
            string name = square.getPiece()->getType();
            if (square.getPiece()->getColor() == BLACK) name = "b" + name;
            if ((row + col) % 2) path = "./pieces/" + name + ".png";
            else path = "./pieces/" + name + "2.png";
            window->putImage(395 + 40 * col, 95 + 40 * row, path.c_str());
        }
        col ++;
        if (col == 8) {
            col = 0;
            row ++;
        }
    }
    if (getSubject()->getLastCardApplied() != Card::NONE) {
        cout<<"play card"<<endl;
        string path = "./cards/" + getSubject()->getLastCardApplied().getName()+".png";
        window->putImage(50, 90, path.c_str());
    }
    //getSubject()->playTurn(pos,pos);
    int i = 1;
    while(i) {
        window->drawString(30, 30,"Click on the piece you want to move");
        vector<int> point1 = window->getButtonPressed();
        if(point1.size() > 0) {
            window->fillRectangle(0,0,300,50,0);
            window->drawString(30, 30,"Click on the target position");
        }
        vector<int> point2 = window->getButtonPressed();
        Point curPos = getPoint(point1);
        Point newPos = getPoint(point2);
        try {
            i = 0;
            getSubject()->playTurn(curPos, newPos);
        } catch (InvalidMoveException& e) {
            i = 1;
        }
    }
    
}