#ifndef __GAME_H__
#define __GAME_H__

#include<memory>

#include "subject.h"
#include "chessBoard.h"
#include "color.h"

class Game : public Subject {
    std::unique_ptr<ChessBoard> chessBoard;
		Color curPlayer;
    Color winner;
    Card lastCardApplied;
    bool tie;

    bool checkWin();

  public:
    Game();

    ChessBoard* getChessBoard();
    Card getLastCardApplied();
    Color getWinner();

    bool isTie();
		bool playTurn(Point&, Point&, Color);
};

#endif