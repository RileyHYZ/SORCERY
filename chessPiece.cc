#include "chessPiece.h"
#include "color.h"
#include "point.h"

// Chess Piece

ChessPiece::ChessPiece(Color c) : color{c} {}

ChessPiece::~ChessPiece() {}

//we can add a bool to tell if the newPos has opponent's piece
bool ChessPiece::checkValidMove(Point& curPos, Point& newPos, bool capture) {
    return isValidMove(curPos, newPos, capture);
}

Color ChessPiece::getColor() {
    return color;
}

// Pawn

Pawn::Pawn(Color c) : ChessPiece{c} {}
		
bool Pawn::isValidMove(Point& curPos, Point& newPos, bool capture) {
    if(capture) {
        return abs(curPos.getX - newPos.getX) == 1 &&
                    abs(curPos.getY - curPos.getY) == 1;
    }
    bool forwardOne = getColor() == WHITE ? newPos.getY == curPos.getY - 1 :
                    newPos.getY == curPos.getY + 1;
    return curPos.getX == newPos.getX && forwardOne; 
}

// Knight

Knight::Knight(Color c) : ChessPiece{c} {}

bool Knight::isValidMove(Point& curPos, Point& newPos, bool cap = false) {
    return abs(curPos.getX - newPos.getX) + abs(curPos.getY - newPos.getY) == 3;
}

// Bishop

Bishop::Bishop(Color c) : ChessPiece{c} {}

bool Bishop::isValidMove(Point& curPos, Point& newPos, bool cap = false) {
    return abs(curPos.getX - newPos.getX) == abs(curPos.getY - curPos.getY);
}

// Rook

Rook::Rook(Color c) : ChessPiece{c} {}

bool Rook::isValidMove(Point& curPos, Point& newPos, bool cap = false) {
    return curPos.getX == newPos.getX || curPos.getY == newPos.getY;
}

// King

King::King(Color c) : ChessPiece{c} {}

bool King::isValidMove(Point& curPos, Point& newPos, bool cap = false) {
    return false;
}

// Queen

Queen::Queen(Color c) : ChessPiece{c} {}

bool Queen::isValidMove(Point& curPos, Point& newPos, bool cap = false) {
    return abs(curPos.getX - newPos.getX) == abs(curPos.getY - curPos.getY)
                    || curPos.getX == newPos.getX
                    || curPos.getY == newPos.getY;
}