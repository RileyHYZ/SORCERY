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
    return checkWin();
}

bool Game::checkWin() {
    Color opponent = curPlayer == WHITE ? BLACK : WHITE;
    if(!chessBoard.get()->getPlayerHp(opponent) || !chessBoard.get()->armyIsAlive(opponent)){
        winner = curPlayer;
        return true;
    }
    if(chessBoard.get()->checkStandstill()) {
        if (chessBoard.get()->getPlayerHp(opponent) > chessBoard.get()->getPlayerHp(curPlayer)){
            winner = opponent;
        } else {
            winner = curPlayer;
        }
        return true;
    }
    return false;
}