#include <memory>
#include "square.h"

using namespace std;

// Public Methods

// Accessors

ChessPiece* Square::getPiece() {
    return piece;
}

Card Square::getCard() {
    return card;
}

// Constructor

// this will change depending on how you want to initialize the board, if 
// initialize all at once or initialize squares first, then put pieces/cards in
Square::Square(ChessPiece* p, Card c) : piece{p}, card{c} {}