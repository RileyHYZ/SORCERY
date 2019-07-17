#ifndef __CHESSBOARD_H__
#define __CHESSBOARD_H__

#include <vector>
#include <unordered_map>
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
    std::unordered_map<Card, int, Card::CardHash> numCards;
    std::unordered_map<Color, int, Color::ColorHash> hp;
    std::unordered_map<Color, char, Color::ColorHash> defaultPromotionPieces;

    void initPieces(Color);
    void initCards();
    void checkMakeMove(Point&, Point&, Color);
    bool isWithinBounds(Point&);
    bool validPieceSelected(ChessPiece*, Color);
    void removePieceAt(Square&);

  public:
    ChessBoard(int, int);

    int getPlayerHP(Color);
    
    void setDefaultPromotionPiece(Color, char);

		void makeMove(Point&, Point&, Color);
    Card applyCardAt(Point&, Color);
		bool isAtStandstill();
    bool armyIsAlive(Color);
    void markValidMoves(Point&, Color, bool);

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