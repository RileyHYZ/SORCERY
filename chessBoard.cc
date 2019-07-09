#include "chessBoard.h"
#include "point.h"
#include "color.h"

// Constructor

ChessBoard::ChessBoard() : NUM_ROWS{8}, NUM_COLS{8} {}

// Public Methods

void ChessBoard::makeMove(Point& curPos, Point& newPos, Color player) {

}

bool ChessBoard::checkStandstill() {

}

void ChessBoard::applyCardAt(Point& pos) {

}

bool ChessBoard::armyIsAlive(Color color) {
    int count = 0;
    for(std::unique_ptr<ChessPiece>& cp: pieces) {
        if(cp.get()->getColor() == color) {
            count++;
        }
        if(count >= 2) return true;
    }
    return false;
}

int ChessBoard::getPlayerHp(Color color) {
    King* k;
    if(color == WHITE) {
        Square sq = board[7][4];
        k = dynamic_cast<King*>(sq.getPiece());
    } else {
        Square sq = board[0][4];
        k = dynamic_cast<King*>(sq.getPiece());
    }
    return k->getHP();
}