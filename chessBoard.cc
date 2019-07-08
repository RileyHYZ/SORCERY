#include <vector>

#include "chessBoard.h"
#include "point.h"
#include "color.h"

using namespace std;

// Constructor

ChessBoard::ChessBoard() : NUM_ROWS{8}, NUM_COLS{8} {
    vector<vector<Square> > tmp;
    board = tmp;

    for (int i = 0; i < NUM_ROWS; ++i) {
        vector<Square> v;
        
        for (int j = 0; j < NUM_COLS; ++j) {
            Square s{nullptr, NONE, (i + j) % 2 == 0 ? BLACK : WHITE};
            v.push_back(s);
        }

        board.push_back(v);
    }
}

// Public Methods

void ChessBoard::makeMove(Point& curPos, Point& newPos, Color player) {

}

bool ChessBoard::checkStandstill() {

}

void ChessBoard::applyCardAt(Point& pos) {

}

// Iterator

ChessBoard::Iterator::Iterator(std::vector<std::vector<Square> > board, int curRow, int curCol, int numCols) \
 : board{board}, curRow{curRow}, curCol{curCol}, numCols{numCols} {}

bool ChessBoard::Iterator::operator!=(const Iterator& it) const {
    return !(curRow == it.curRow && curCol == it.curCol);
}

ChessBoard::Iterator& ChessBoard::Iterator::operator++() {
    if (curCol == numCols - 1) {
        --curRow;
        curCol = 0;
    } else {
        ++curCol;
    }

    return *this;
}

Square& ChessBoard::Iterator::operator*() {
    return board.at(curRow).at(curCol);
}

ChessBoard::Iterator ChessBoard::begin() {
    return Iterator{board, NUM_ROWS - 1, 0, NUM_COLS};
}

ChessBoard::Iterator ChessBoard::end() {
    return Iterator{board, -1, 0, NUM_COLS};
}