#include <memory>

#include "square.h"
#include "chessPiece.h"
#include "card.h"
#include "color.h"

using namespace std;

// Public Methods

// Accessors

ChessPiece* Square::getPiece() {
    return piece;
}

Card Square::getCard() {
    return card;
}

Color Square::getColor() {
    return color;
}

// Constructor

// this will change depending on how you want to initialize the board, if 
// initialize all at once or initialize squares first, then put pieces/cards in
Square::Square(ChessPiece* p, Card c, Color co) : piece{p}, card{c}, color{co} {}