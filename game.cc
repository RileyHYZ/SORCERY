#include <memory>

#include "game.h"
#include "chessBoard.h"
#include "color.h"
#include "card.h"

using namespace std;

// Constructor

Game::Game() : chessBoard{make_unique<ChessBoard>()}, curPlayer{WHITE}, lastCardApplied{NONE} {}

// Accessors

ChessBoard* Game::getChessBoard() {
    return chessBoard.get();
}

Card Game::getLastCardApplied() {
    return lastCardApplied;
}

// Public Methods

void Game::setDefaultPromotionPiece(char piece) {
    chessBoard->setDefaultPromotionPiece(curPlayer, piece);
}

bool Game::playTurn(Point& curPos, Point& newPos) {
    chessBoard->makeMove(curPos, newPos, curPlayer);
    notifyObservers();
    curPlayer = curPlayer == WHITE ? BLACK : WHITE;
    return false;
}