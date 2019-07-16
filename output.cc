#include <iostream>

#include "output.h"
#include "game.h"
#include "square.h"

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

    if (getSubject()->getLastCardApplied() != NONE) {
        out << "The card that was played in this term was " << getSubject()->getLastCardApplied();
    }
}

// Graphical Display

// Constructor

GraphicalDisplay::GraphicalDisplay(Game* subject) : Output{subject} {
    window = new Xwindow{};
    window->drawRectangle(90, 90, 320, 320, 3);
    for (int i = 0; i < 8; i ++) {
        for (int j = 0; j < 8; j++) {
            if ((i + j) % 2 == 0) {
                window->fillRectangle(90 + 40 * j, 90 + 40 * i, 40, 40, 3);
            }
        }
    }
    getSubject()->attach(this);
}

// Destructor

GraphicalDisplay::~GraphicalDisplay() {
    delete window;
    getSubject()->detach(this);
}

// Public Method

void GraphicalDisplay::notify() {
    ChessBoard* board = getSubject()->getChessBoard();

    vector<int> hp = board->getHP();
    for(int i = 0; i < hp.at(WHITE); i++) {
        window->fillRectangle(40 + 30 * i, 30, 20, 20, 2);
    }
    for(int i = 0; i < hp.at(BLACK); i++) {
        window->fillRectangle(410 + 30 * i, 460, 20, 20, 2);
    }
    int row = 0, col = 0;
    for (Square& square : *board) {
        if (square.getPiece() != nullptr) {
            window->drawString(100 + 40 * col, 100 + 40 * row, "周");//square.getPiece()->getDisplayIcon());
            // window->putImage(100 + 40 * col, 100 + 40 * row, "./test.png");
            cout << "FINISH PRINTING" << endl;
            break;
        }
        col ++;
        if (col == 8) {
            col = 0;
            row ++;
        }
        

        // if (square.getPiece() != nullptr) {
        //     out << square.getPiece()->getDisplayIcon();
        // } else if (square.getColor() == BLACK) {
        //     out << " ";
        // } else {
        //     out << "\u2588";
        // }

        // if (col == 7) {
        //     out << "|\n";
        //     col = 0;
        // } else {
        //     ++col;
        // }
    }
}