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

bool ChessPiece::checkValidMove(Point& curPos, Point& newPos) {
    return isValidMove(curPos, newPos);
}

// Pawn

Pawn::Pawn(Color c) : ChessPiece{c} {}

char Pawn::displayIcon() {
    return getColor() == WHITE ? '\u2659' : '\u265F';
}
		
bool Pawn::isValidMove(Point& curPos, Point& newPos) {

}


// Knight

Knight::Knight(Color c) : ChessPiece{c} {}

char Knight::displayIcon() {
    return getColor() == WHITE ? '\u2658' : '\u265E';
}

bool Knight::isValidMove(Point& curPos, Point& newPos) {

}

// Bishop

Bishop::Bishop(Color c) : ChessPiece{c} {}

char Bishop::displayIcon() {
    return getColor() == WHITE ? '\u2657' : '\u265D';
}

bool Bishop::isValidMove(Point& curPos, Point& newPos) {

}

// Rook

Rook::Rook(Color c) : ChessPiece{c} {}

char Rook::displayIcon() {
    return getColor() == WHITE ? '\u2656' : '\u265C';
}

bool Rook::isValidMove(Point& curPos, Point& newPos) {

}

// King

King::King(Color c) : ChessPiece{c}, hp{2} {}

char King::displayIcon() {
    return getColor() == WHITE ? '\u2654' : '\u265A';
}

int King::getHP() {
    return hp;
}

void King::setHP(int newHP) {
    hp = newHP;
}

bool King::isValidMove(Point& curPos, Point& newPos) {

}

// Queen

Queen::Queen(Color c) : ChessPiece{c} {}

char Queen::displayIcon() {
    return getColor() == WHITE ? '\u2655' : '\u265B';
}

bool Queen::isValidMove(Point& curPos, Point& newPos) {

}