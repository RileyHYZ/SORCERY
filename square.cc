#include <memory>
#include "square.h"

using namespace std;

// Private Methods

std::shared_ptr<ChessPiece> Square::getPiece() {
    return piece;
}

Card Square::getCard() {
    return card;
}

// Public Methods

// this will change depending on how you want to initialize the board, if 
// initialize all at once or initialize squares first, then put pieces/cards in
Square::Square(shared_ptr<ChessPiece> p, Card c) : piece{p}, card{c} {}