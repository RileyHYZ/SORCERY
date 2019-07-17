#ifndef __GAME_H__
#define __GAME_H__

#include "model.h"
#include "chessBoard.h"
#include "color.h"
#include "card.h"
#include "point.h"

#include <memory>
#include <iostream>

class Game : public Model {
    const int NUM_ROWS;
    const int NUM_COLS;

    std::unique_ptr<ChessBoard> chessBoard;
		Color curPlayer;
    Card cardApplied;
    std::istream& in;

    bool playTurn(Point& curPos, Point& newPos);
    bool checkWin();
    void showValidMoves(Point&);
    void restart();

  public:
    Game(bool, bool, std::istream& = std::cin, int = 8, int = 8);

    ChessBoard* getChessBoard();
    Card getCardApplied();

    void start(); // Game loop
};

#endif