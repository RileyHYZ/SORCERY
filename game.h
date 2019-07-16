#ifndef __GAME_H__
#define __GAME_H__

#include "model.h"
#include "chessBoard.h"
#include "color.h"
#include "card.h"
#include "point.h"

#include <memory>

class Game : public Model {
    std::unique_ptr<ChessBoard> chessBoard;
		Color curPlayer;
    Card lastCardApplied;
    Color winner;
    bool tie;
    bool validMoves; // showing valid moves

    bool checkWin();

  public:
    Game(bool = false);

    ChessBoard* getChessBoard();
    Card getLastCardApplied();
    Color getWinner();
    bool isTie();
    bool showingValidMoves();

    void setDefaultPromotionPiece(char);

    void start(); // Game loop
		bool playTurn(Point&, Point&);
    void showValidMoves(Point&);
};

#endif