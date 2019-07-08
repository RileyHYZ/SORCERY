#include <iostream>

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

    int whiteKingHP = 0;
    int blackKingHP = 0;

    for (Square& square : *board) {
        if (King* k = dynamic_cast<King*>(square.getPiece())) {
            if (k->getColor() == WHITE) {
                whiteKingHP = k->getHP();
            } else {
                blackKingHP = k->getHP();
            }   
        }

        if (square.getPiece() != nullptr) {
            out << square.getPiece()->getDisplayIcon();
        } else if (square.getColor() == BLACK) {
            out << "| ";
        } else {
            out << "|\u2588";
        }

        if (col == 7) {
            out << "|\n";
            col = 0;
        } else {
            ++col;
        }
    }

    out << "The white player's king has " << whiteKingHP << " HP." << endl;
    out << "The black player's king has " << blackKingHP << " HP." << endl;

    if (getSubject()->getLastCardApplied() != NONE) {
        out << "The card that was played in this term was " << getSubject()->getLastCardApplied();
    }
}