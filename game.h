#ifndef __GAME_H__
#define __GAME_H__
#include "subject.h"
#include "chessBoard.h"

class Game : public Subject{
    ChessBoard *chessBoard;
		Color curPlayer;
  public:
		bool playTurn();
};

#endif