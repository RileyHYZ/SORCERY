#include <memory>

#include "game.h"
#include "chessBoard.h"
#include "color.h"
#include "card.h"

using namespace std;

// Constructor

Game::Game() : chessBoard{make_unique<ChessBoard>()}, curPlayer{WHITE}, lastCardApplied{Card::NONE}, winner{UNDEF}, tie{false}, validMoves{false}  {}

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

bool Game::showingValidMoves() {
    return validMoves;
}

// Public Methods

void Game::setDefaultPromotionPiece(char piece) {
    chessBoard->setDefaultPromotionPiece(curPlayer, piece);
}

bool Game::playTurn(Point& curPos, Point& newPos) {
    chessBoard->makeMove(curPos, newPos, curPlayer);
    lastCardApplied = chessBoard->getCardAt(newPos);
    switch (lastCardApplied.getValue()) {
        case Card::CURSE:
            chessBoard->updateHP(curPlayer == WHITE ? BLACK : WHITE, -1);
            break;
        case Card::PLUSONEHP:
            chessBoard->updateHP(curPlayer, 1);
            break;
        case Card::FIRECOLUMN:
        case Card::MOAT:
        case Card::DESTRUCTION:
        case Card::RESURRECTION:
            chessBoard->applyCardAt(curPlayer, newPos);
            break;
        default:
            break;
    }
    chessBoard->setCardAt(newPos, Card::NONE);

    // Check for winner
    bool gameEnded = checkWin();

    // Switch turn if ENCHANTMENT card not applied
    if (!(lastCardApplied == Card::ENCHANTMENT)) curPlayer = curPlayer == WHITE ? BLACK : WHITE;

    // Notify observers to display screen
    notifyObservers();

    return gameEnded;
}

void Game::showValidMoves(Point& pos) {
    chessBoard->markValidMoves(pos, curPlayer, true);
    validMoves = true;
    notifyObservers();
    chessBoard->markValidMoves(pos, curPlayer, false);
    validMoves = false;
} 

bool Game::checkWin() {
    Color opponent = curPlayer == WHITE ? BLACK : WHITE;

    if(chessBoard->getPlayerHp(opponent) <= 0 || !chessBoard->armyIsAlive(opponent)){
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