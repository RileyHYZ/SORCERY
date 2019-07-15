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
    bool validMoves; // showing valid moves

    bool checkWin();

  public:
    Game();

    ChessBoard* getChessBoard();
    Card getLastCardApplied();
    Color getWinner();
    bool isTie();
    bool showingValidMoves();

    void setDefaultPromotionPiece(char);

		bool playTurn(Point&, Point&);
    void showValidMoves(Point&);
};

#endif