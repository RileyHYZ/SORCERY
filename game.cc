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
    lastCardApplied = chessBoard->getCardAt(newPos);
    switch (lastCardApplied) {
        case CURSE:
            chessBoard->updateHP(curPlayer == WHITE ? BLACK : WHITE, -1);
            break;
        case PLUSONEHP:
            chessBoard->updateHP(curPlayer, 1);
            break;
        case FIRECOLUMN:
        case MOAT:
        case DESTRUCTION:
        case RESURRECTION:
            chessBoard->applyCardAt(curPlayer, newPos);
            break;
        default:
            break;
    }
    chessBoard->setCardAt(newPos, NONE);
    notifyObservers();
    if (!(lastCardApplied == ENCHANTMENT)) curPlayer = curPlayer == WHITE ? BLACK : WHITE;
    return false;
}