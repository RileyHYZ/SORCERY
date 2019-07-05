#include <vector>
#include "square.h"

enum Color {BLACK, WHITE};

class ChessBoard {
    std::vector<std::vector<Square> > board;
    //chessboard owns chesspieces? vector of chesspieces?
  public:
		void makeMove(Point&, Point&, Color);
		bool checkStandstill();
		void applyCardAt(Point&);
};