#include <iostream>
#include <vector>

#include "display.h"
#include "game.h"
#include "square.h"

using namespace std;

// Display

// Constructor

Display::Display(Game* subject) : subject{subject} {}

// Destructor

Display::~Display() {}

// Accessors

Game* Display::getSubject() {
    return subject;
}

// TextDisplay

// Constructor

TextDisplay::TextDisplay(Game* subject, ostream& out) : Display{subject}, out{out} {
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

    out << "The white player's king has " << hp.at(0) << " HP." << endl;
    out << "The black player's king has " << hp.at(1) << " HP." << endl;

    if (getSubject()->getLastCardApplied() != NONE) {
        out << "The card that was played in this turn was " << getSubject()->getLastCardApplied() << endl;
    }
}