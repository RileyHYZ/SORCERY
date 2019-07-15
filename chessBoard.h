#ifndef __CHESSBOARD_H__
#define __CHESSBOARD_H__

#include <vector>
#include <memory>

#include "square.h"
#include "chessPiece.h"
#include "color.h"
#include "point.h"

class ChessBoard {
    const int NUM_ROWS;
    const int NUM_COLS;
    std::vector<std::vector<Square> > board;
    std::vector<std::unique_ptr<ChessPiece> > pieces;
    std::vector<int> hp;
    std::vector<char> defaultPromotionPieces; // white at 0, black at 1

    void initPieces(Color);
    void initCards();
    void removePieceAt(Square&);

  public:
    ChessBoard();

    std::vector<int> getHP();
    Card getCardAt(Point&);
    void setCardAt(Point&, Card);
    void setDefaultPromotionPiece(Color, char);

    void updateHP(Color, int);
		void makeMove(Point&, Point&, Color);
		bool checkStandstill();
		void applyCardAt(Color, Point&);
    int getPlayerHp(Color);
    bool armyIsAlive(Color);

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