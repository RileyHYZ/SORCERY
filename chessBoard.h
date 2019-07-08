#ifndef __CHESSBOARD_H__
#define __CHESSBOARD_H__

#include <vector>
#include <memory>

#include "square.h"
#include "chessPiece.h"
#include "color.h"

class ChessBoard {
    const int NUM_ROWS;
    const int NUM_COLS;
    std::vector<std::vector<Square> > board;
    std::vector<std::unique_ptr<ChessPiece> > pieces;

  public:
    ChessBoard();
		void makeMove(Point&, Point&, Color);
		bool checkStandstill();
		void applyCardAt(Point&);

    class Iterator {
        std::vector<std::vector<Square> > board;
        int curRow;
        int curCol;
        int numCols;
        Iterator(std::vector<std::vector<Square> >, int, int, int);
        friend class ChessBoard;
      public:
        bool operator!=(const Iterator&) const;
        Iterator& operator++();
        Square& operator*();
    };

		Iterator begin();
    Iterator end();
};

#endif