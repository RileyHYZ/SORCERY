#ifndef __GAME_H__
#define __GAME_H__

#include<memory>

#include "subject.h"
#include "chessBoard.h"
#include "color.h"

class Game : public Subject {
    std::unique_ptr<ChessBoard> chessBoard;
		Color curPlayer;
    Card lastCardApplied;

  public:
    Game();

    ChessBoard* getChessBoard();
    Card getLastCardApplied();

		bool playTurn();
};

#endif