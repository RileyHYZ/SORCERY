#ifndef __SQUARE_H__
#define __SQUARE_H__

#include <memory>

#include "chessPiece.h"
#include "card.h"
#include "color.h"

class Square {
    ChessPiece* piece;
    Card card;
    Color color;

  public:
    Square(ChessPiece*, Card, Color);
    ChessPiece* getPiece();
    Card getCard();
    Color getColor();
};

#endif