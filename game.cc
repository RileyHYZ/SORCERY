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

bool Game::playTurn() {

}