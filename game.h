#ifndef __GAME_H__
#define __GAME_H__
#include "subject.h"
#include "chessBoard.h"
#include "color.h"

class Game : public Subject {
    ChessBoard chessBoard;
		Color curPlayer;
  public:
    Game();
		bool playTurn();
};

#endif