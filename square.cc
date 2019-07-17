#include "square.h"
#include "chessPiece.h"
#include "card.h"
#include "color.h"

using namespace std;

// Constructor

Square::Square(ChessPiece* p, Card c, Color co) : piece{p}, card{c}, color{co}, valid{false} {}

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

bool Square::isValid() {
    return valid;
}

// Mutators

void Square::setPiece(ChessPiece* p) {
    piece = p;
}

void Square::setCard(Card c) {
    card = c;
}

void Square::setValid(bool v) {
    valid = v;
}