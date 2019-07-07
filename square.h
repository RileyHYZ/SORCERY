#ifndef __SQUARE_H__
#define __SQUARE_H__

#include <memory>
#include "chessPiece.h"
#include "card.h"

class Square {
    ChessPiece* piece;
    Card card;

  public:
    Square(ChessPiece*, Card);
    ChessPiece* getPiece();
    Card getCard();
};

#endif