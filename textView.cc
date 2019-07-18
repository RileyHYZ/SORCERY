#include "textView.h"
#include "game.h"
#include "square.h"

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Constructor

TextView::TextView(Game& model, int numRows, int numCols, ostream& out) : model{model}, numRows{numRows}, \
    numCols{numCols}, out{out} {}

// Private Helper Methods

void TextView::outputHP(int hp) {
    for (int i = 0; i < hp; ++i) {
        out << "\u2665" << " "; // Outputs hearts
    }
    out << endl;
}

// Public Interface Methods

void TextView::displayView() {
    ChessBoard* board = model.getChessBoard();

    outputHP(board->getPlayerHP(Color::BLACK));
    
    int col = 0;
    int row = numRows;

    for (Square& square : *board) {
        // If start of row, output rank 
        if (col == 0) {
            out << row << " ";
            --row;
        }

        // Output separator
        out << '|';
        
        // Displaying valid moves
        if (square.isValid()) {
            out << "●";
        } 
        
        // Piece exists at that square
        else if (square.getPiece() != nullptr) {
            out << square.getPiece()->getDisplayIcon();
        } 
        
        // Output correct square color
        else {
            out << (square.getColor() == Color::BLACK ? " " : "\u2588");
        }

        // If end of row, output separator and new line
        if (col == 7) {
            out << "|\n";
            col = 0;
        } else {
            ++col;
        }
    }

    // Output file
    out << "   ";
    for (char i = 'A'; i < 'A' + numCols; ++i) {
        out << i << " ";
    }
    out << endl;

    outputHP(board->getPlayerHP(Color::WHITE));

    // Output last card applied
    if (model.getCardApplied() != Card::NONE) {
        out << "The card that was played in this turn was " << model.getCardApplied().getName() << ". " << model.getCardApplied().getDescription() << endl;
    }
}

void TextView::displayMessage(const string& msg) {
    if (msg.size() > 0)
        out << msg << endl;
}