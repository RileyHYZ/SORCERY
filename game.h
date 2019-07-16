#ifndef __GAME_H__
#define __GAME_H__

#include<memory>

#include "subject.h"
#include "chessBoard.h"
#include "color.h"
#include "point.h"

class Game : public Subject {
    std::unique_ptr<ChessBoard> chessBoard;
		Color curPlayer;
    Card lastCardApplied;
    Color winner;
    bool tie;

    bool checkWin();

  public:
    Game();

    ChessBoard* getChessBoard();
    Card getLastCardApplied();
    Color getWinner();
    bool isTie();

    void setDefaultPromotionPiece(char);

		bool playTurn(Point&, Point&);
};

#endif