#include "chessPiece.h"
#include "color.h"
#include "point.h"

// Chess Piece

ChessPiece::ChessPiece(Color c) : color{c} {}

ChessPiece::~ChessPiece() {}

Color ChessPiece::getColor() {
     return color;
}

std::string ChessPiece::getDisplayIcon() {
    return displayIcon();
}

bool ChessPiece::checkValidMove(Point& curPos, Point& newPos, bool capture = false) {
    return isValidMove(curPos, newPos, capture);
}

bool isDiagonalMove(Point &curPos, Point &newPos, bool capture) {
    return (capture && abs(curPos.getX() - newPos.getX()) == 1 &&
                    abs(curPos.getY() - curPos.getY()) == 1) 
                    || (!capture && abs(curPos.getX() - newPos.getX()) 
                        == abs(curPos.getY() - curPos.getY()));
}

// Pawn

Pawn::Pawn(Color c) : ChessPiece{c} {}

std::string Pawn::displayIcon() {
    return getColor() == WHITE ? "\u2659" : "\u265F";
}
		
bool Pawn::isValidMove(Point& curPos, Point& newPos, bool capture) {
    bool forwardOne = getColor() == WHITE ? newPos.getX() == curPos.getX() - 1 :
                    newPos.getX() == curPos.getX() + 1;
    return isDiagonalMove(curPos, newPos, capture) || (curPos.getY() == newPos.getY() && forwardOne); 
}

// Knight

Knight::Knight(Color c) : ChessPiece{c} {}

bool Knight::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return abs(curPos.getX() - newPos.getX()) + abs(curPos.getY() - newPos.getY()) == 3;
}

std::string Knight::displayIcon() {
    return getColor() == WHITE ? "\u2658" : "\u265E";
}

// Bishop

Bishop::Bishop(Color c) : ChessPiece{c} {}

bool Bishop::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return isDiagonalMove(curPos, newPos, capture);
}

std::string Bishop::displayIcon() {
    return getColor() == WHITE ? "\u2657" : "\u265D";
}

// Rook

Rook::Rook(Color c) : ChessPiece{c} {}

bool Rook::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return curPos.getX() == newPos.getX() || curPos.getY() == newPos.getY();
}

std::string Rook::displayIcon() {
    return getColor() == WHITE ? "\u2656" : "\u265C";
}

// King

King::King(Color c) : ChessPiece{c} {}

std::string King::displayIcon() {
    return getColor() == WHITE ? "\u2654" : "\u265A";
}

bool King::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return false;
}

// Queen

Queen::Queen(Color c) : ChessPiece{c} {}

bool Queen::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return isDiagonalMove(curPos, newPos, capture)
                    || curPos.getX() == newPos.getX()
                    || curPos.getY() == newPos.getY();
}

std::string Queen::displayIcon() {
    return getColor() == WHITE ? "\u2655" : "\u265B";
}