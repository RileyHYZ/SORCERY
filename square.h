#ifndef __SQUARE_H__
#define __SQUARE_H__

#include <memory>
#include "chessPiece.h"
#include "card.h"

class Square {
    // not sure what pointer we should use here so just used shared for now
    std::shared_ptr<ChessPiece> piece;
    Card card;

    std::shared_ptr<ChessPiece> getPiece();
    Card getCard();

  public:
    Square(std::shared_ptr<ChessPiece>, Card);
};

#endif