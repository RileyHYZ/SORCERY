#ifndef __CHESSBOARD_H__
#define __CHESSBOARD_H__

#include <vector>
#include "square.h"
#include "chessPiece.h"
#include "color.h"

class ChessBoard {
    std::vector<std::vector<Square> > board;
    std::vector<ChessPiece> pieces;
  public:
		void makeMove(Point&, Point&, Color);
		bool checkStandstill();
		void applyCardAt(Point&);
};

#endif