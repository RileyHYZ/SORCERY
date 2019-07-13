#include <memory>

#include "game.h"
#include "chessBoard.h"
#include "color.h"
#include "card.h"

using namespace std;

// Constructor

Game::Game() : chessBoard{make_unique<ChessBoard>()}, curPlayer{WHITE}, lastCardApplied{NONE}, winner{UNDEF}, tie{false} {}

// Accessors

ChessBoard* Game::getChessBoard() {
    return chessBoard.get();
}

Card Game::getLastCardApplied() {
    return lastCardApplied;
}

Color Game::getWinner() {
    return winner;
}

bool Game::isTie() {
    return tie;
}

// Public Methods

bool Game::playTurn(Point& curPos, Point& newPos, Color curPlayer) {
    chessBoard->makeMove(curPos, newPos, curPlayer);
    notifyObservers();
    curPlayer = curPlayer == WHITE ? BLACK : WHITE;
    return checkWin();
}

bool Game::checkWin() {
    Color opponent = curPlayer == WHITE ? BLACK : WHITE;
    if(!chessBoard->getPlayerHp(opponent) || !chessBoard->armyIsAlive(opponent)){
        winner = curPlayer;
        return true;
    }
    if(chessBoard->checkStandstill()) {
        if (chessBoard->getPlayerHp(opponent) > chessBoard->getPlayerHp(curPlayer)) {
            winner = opponent;
        } else if (chessBoard->getPlayerHp(opponent) == chessBoard->getPlayerHp(curPlayer)) {
            tie = true;
        } else {
            winner = curPlayer;
        }
        return true;
    }
    return false;
}