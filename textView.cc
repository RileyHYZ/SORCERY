#include "textView.h"
#include "game.h"
#include "square.h"

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Private Helper Methods

void TextView::outputHP(int hp) {
    for (int i = 0; i < hp; ++i) {
        out << "\u2665" << " "; // Outputs hearts
    }
    out << endl;
}

// Constructor

TextView::TextView(Game& model, int numRows, int numCols, ostream& out) : model{model}, numRows{numRows}, \
    numCols{numCols}, out{out} {}

// Public Methods

void TextView::updateView() {
    ChessBoard* board = model.getChessBoard();
    unordered_map<Color, int> hp = board->getHP();

    outputHP(hp.at(Color::BLACK));
    
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
            out << "·";
        } 
        
        // Piece exists at that square
        else if (square.getPiece() != nullptr) {
            out << square.getPiece()->getViewIcon();
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
    for (char i = 'A'; i < 'I'; ++i) {
        out << i << " ";
    }
    out << endl;

    outputHP(hp.at(Color::WHITE));

    if (!model.showingValidMoves()) {
        if (model.getLastCardApplied() != Card::NONE) {
            out << "The card that was played in this turn was " << model.getLastCardApplied().getName() << ". " << model.getLastCardApplied().getDescription() << endl;
        } else {
            out << "No card was played in this turn." << endl;
        }
        if (model.getWinner() == Color::WHITE) {
            out << "The white player wins!" << endl;
        } else if (model.getWinner() == Color::BLACK) {
            out << "The black player wins!" << endl;
        } else if (model.isTie()) {
            out << "The game ends in a tie." << endl;
        }
    }
}
