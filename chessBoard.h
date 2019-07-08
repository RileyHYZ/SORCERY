#ifndef __CHESSBOARD_H__
#define __CHESSBOARD_H__

#include <vector>
#include <memory>

#include "square.h"
#include "chessPiece.h"
#include "color.h"

class ChessBoard {
    const int NUM_ROWS;//if row and col are always 8 why do we still need these
    const int NUM_COLS;
    std::vector<std::vector<Square> > board;
    std::vector<std::unique_ptr<ChessPiece> > pieces;
  public:
    ChessBoard();
		void makeMove(Point&, Point&, Color);
		bool checkStandstill();
		void applyCardAt(Point&);
};

#endif