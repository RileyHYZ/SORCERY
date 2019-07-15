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
    bool valid;

  public:
    Square(ChessPiece*, Card, Color);
    ChessPiece* getPiece();
    Card getCard();
    Color getColor();
    bool isValid();
    void setPiece(ChessPiece*);
    void setCard(Card);
    void setValid(bool);
};

#endif