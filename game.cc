#include "subject.h"
#include "chessBoard.h"
#include "color.h"
#include "game.h"

using namespace std;

Game::Game() {}

bool Game::playTurn() {
    return checkWin();
}

bool Game::checkWin() {
    Color opponent = curPlayer == WHITE ? BLACK : WHITE;
    if(!chessBoard.getPlayerHp(opponent) || !chessBoard.armyIsAlive(opponent)){
        winner = curPlayer;
        return true;
    }
    if(chessBoard.checkStandstill()) {
        if (chessBoard.getPlayerHp(opponent) > chessBoard.getPlayerHp(curPlayer)){
            winner = opponent;
        } else {
            winner = curPlayer;
        }
        return true;
    }
    return false;
}