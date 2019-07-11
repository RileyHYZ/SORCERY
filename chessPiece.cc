#include "chessPiece.h"
#include "color.h"
#include "point.h"

// Chess Piece

ChessPiece::ChessPiece(Color c) : color{c} {}

ChessPiece::~ChessPiece() {}

Color ChessPiece::getColor() {
     return color;
}

char ChessPiece::getDisplayIcon() {
    return displayIcon();
}

bool ChessPiece::checkValidMove(Point& curPos, Point& newPos, bool capture) {
    return isValidMove(curPos, newPos, capture);
}

// Pawn

Pawn::Pawn(Color c) : ChessPiece{c} {}

char Pawn::displayIcon() {
    return getColor() == WHITE ? 'p' : 'P';
}
		
bool Pawn::isValidMove(Point& curPos, Point& newPos, bool capture) {
    if(capture) {
        return abs(curPos.getX() - newPos.getX()) == 1 &&
                    abs(curPos.getY() - curPos.getY()) == 1;
    }
    bool forwardOne = getColor() == WHITE ? newPos.getY() == curPos.getY() - 1 :
                    newPos.getY() == curPos.getY() + 1;
    return curPos.getX() == newPos.getX() && forwardOne; 
}

// Knight

Knight::Knight(Color c) : ChessPiece{c} {}

bool Knight::isValidMove(Point& curPos, Point& newPos, bool cap = false) {
    return abs(curPos.getX() - newPos.getX()) + abs(curPos.getY() - newPos.getY()) == 3;
}

char Knight::displayIcon() {
    return getColor() == WHITE ? 'n' : 'N';
}

// Bishop

Bishop::Bishop(Color c) : ChessPiece{c} {}

bool Bishop::isValidMove(Point& curPos, Point& newPos, bool cap = false) {
    return abs(curPos.getX() - newPos.getX()) == abs(curPos.getY() - curPos.getY());
}

char Bishop::displayIcon() {
    return getColor() == WHITE ? 'b' : 'B';
}

// Rook

Rook::Rook(Color c) : ChessPiece{c} {}

bool Rook::isValidMove(Point& curPos, Point& newPos, bool cap = false) {
    return curPos.getX() == newPos.getX() || curPos.getY() == newPos.getY();
}

char Rook::displayIcon() {
    return getColor() == WHITE ? 'r' : 'R';
}

// King

King::King(Color c) : ChessPiece{c}, hp{2} {}

char King::displayIcon() {
    return getColor() == WHITE ? 'k' : 'K';
}

int King::getHP() {
    return hp;
}

void King::setHP(int newHP) {
    hp = newHP;
}

bool King::isValidMove(Point& curPos, Point& newPos, bool cap = false) {
    return false;
}

// Queen

Queen::Queen(Color c) : ChessPiece{c} {}

bool Queen::isValidMove(Point& curPos, Point& newPos, bool cap = false) {
    return abs(curPos.getX() - newPos.getX()) == abs(curPos.getY() - curPos.getY())
                    || curPos.getX() == newPos.getX()
                    || curPos.getY() == newPos.getY();
}

char Queen::displayIcon() {
    return getColor() == WHITE ? 'q' : 'Q';
}