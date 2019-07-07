#include "chessPiece.h"
#include "color.h"
#include "point.h"

// Chess Piece

ChessPiece::ChessPiece(Color c) : color{c} {}

ChessPiece::~ChessPiece() {}

bool ChessPiece::checkValidMove(Point curPos, Point newPos) {
    return isValidMove(curPos, newPos);
}

// Pawn

Pawn::Pawn(Color c) : ChessPiece{c} {}
		
bool Pawn::isValidMove(Point curPos, Point newPos) {

}


// Knight

Knight::Knight(Color c) : ChessPiece{c} {}

bool Knight::isValidMove(Point curPos, Point newPos) {

}

// Bishop

Bishop::Bishop(Color c) : ChessPiece{c} {}

bool Bishop::isValidMove(Point curPos, Point newPos) {

}

// Rook

Rook::Rook(Color c) : ChessPiece{c} {}

bool Rook::isValidMove(Point curPos, Point newPos) {

}

// King

King::King(Color c) : ChessPiece{c} {}

bool King::isValidMove(Point curPos, Point newPos) {

}

// Queen

Queen::Queen(Color c) : ChessPiece{c} {}

bool Queen::isValidMove(Point curPos, Point newPos) {

}