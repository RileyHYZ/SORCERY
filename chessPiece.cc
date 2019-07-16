#include <vector>

#include "chessPiece.h"
#include "color.h"
#include "point.h"

using namespace std;

// Chess Piece

ChessPiece::ChessPiece(Color c) : color{c} {}

ChessPiece::~ChessPiece() {}

string ChessPiece::getType() {
    return type;
}

Color ChessPiece::getColor() {
     return color;
}

string ChessPiece::getDisplayIcon() {
    return displayIcon();
}

string ChessPiece::getType() {
    return type;
}

bool ChessPiece::checkValidMove(Point& curPos, Point& newPos, bool capture = false) {
    return isValidMove(curPos, newPos, capture);
}

vector<Point> ChessPiece::getPiecePath(Point& curPos, Point& newPos) {
    return piecePath(curPos, newPos);
}

// Protected Helper Functions

vector<Point> ChessPiece::getHorizontalPath(Point& curPos, Point& newPos) {
    vector<Point> v;

    int i = curPos.getY();
    int incI = newPos.getY() > curPos.getY() ? 1 : -1;

    while (i != newPos.getY()) {
        i += incI;
        v.push_back(Point{curPos.getX(), i});
    }

    return v;
}

vector<Point> ChessPiece::getVerticalPath(Point& curPos, Point& newPos) {
    vector<Point> v;

    int i = curPos.getX();
    int incI = newPos.getX() > curPos.getX() ? 1 : -1;

    while (i != newPos.getX()) {
        i += incI;
        v.push_back(Point{i, curPos.getY()});
    }

    return v;
}

vector<Point> ChessPiece::getDiagonalPath(Point& curPos, Point& newPos) {
    vector<Point> v;

    int x = curPos.getX();
    int y = curPos.getY();
    const int incX = newPos.getX() > curPos.getX() ? 1 : -1;
    const int incY = newPos.getY() > curPos.getY() ? 1 : -1;

    while (!(x == newPos.getX() && y == newPos.getY())) {
        x += incX;
        y += incY;
        v.push_back(Point{x, y});
    }

    return v;
}

bool isDiagonalMove(Point& curPos, Point& newPos, int diff = 0) {
    int xDiff = abs(newPos.getX() - curPos.getX());
    int yDiff = abs(newPos.getY() - curPos.getY());
    return diff == 0 ? xDiff == yDiff : xDiff == diff && yDiff == diff;
}

// Pawn

Pawn::Pawn(Color c) : ChessPiece{c} {
    type = "pawn";
}

std::string Pawn::displayIcon() {
    return getColor() == WHITE ? "\u2659" : "\u265F";
}
		
bool Pawn::isValidMove(Point& curPos, Point& newPos, bool capture) {
    int incr = getColor() == WHITE ? 1 : -1;
    bool forwardOne = newPos.getX() == curPos.getX() + incr && newPos.getY() == curPos.getY();
    return (capture && isDiagonalMove(curPos, newPos, 1)) || forwardOne; 
}

vector<Point> Pawn::piecePath(Point& curPos, Point& newPos) {
    return vector<Point>{newPos};
}

// Knight

Knight::Knight(Color c) : ChessPiece{c} {
    type = "knight";
}

bool Knight::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return abs(curPos.getX() - newPos.getX()) + abs(curPos.getY() - newPos.getY()) == 3;
}

std::string Knight::displayIcon() {
    return getColor() == WHITE ? "\u2658" : "\u265E";
}

vector<Point> Knight::piecePath(Point& curPos, Point& newPos) {
    return vector<Point>{};
}

// Bishop

Bishop::Bishop(Color c) : ChessPiece{c} {
    type = "bishop";
}

bool Bishop::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return isDiagonalMove(curPos, newPos);
}

std::string Bishop::displayIcon() {
    return getColor() == WHITE ? "\u2657" : "\u265D";
}

vector<Point> Bishop::piecePath(Point& curPos, Point& newPos) {
    return getDiagonalPath(curPos, newPos);
}

// Rook

Rook::Rook(Color c) : ChessPiece{c} {
    type = "rook";
}

bool Rook::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return curPos.getX() == newPos.getX() || curPos.getY() == newPos.getY();
}

std::string Rook::displayIcon() {
    return getColor() == WHITE ? "\u2656" : "\u265C";
}

vector<Point> Rook::piecePath(Point& curPos, Point& newPos) {
    if (curPos.getX() == newPos.getX()) {
        return getHorizontalPath(curPos, newPos);
    } else if (curPos.getY() == newPos.getY()) {
        return getVerticalPath(curPos, newPos);
    }
}

// King

King::King(Color c) : ChessPiece{c} {
    type = "king";
}

std::string King::displayIcon() {
    return getColor() == WHITE ? "\u2654" : "\u265A";
}

bool King::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return false;
}

vector<Point> King::piecePath(Point& curPos, Point& newPos) {
    return vector<Point>{};
}

// Queen

Queen::Queen(Color c) : ChessPiece{c} {
    type = "queen";
}

bool Queen::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return isDiagonalMove(curPos, newPos)
                    || curPos.getX() == newPos.getX()
                    || curPos.getY() == newPos.getY();
}

std::string Queen::displayIcon() {
    return getColor() == WHITE ? "\u2655" : "\u265B";
}

vector<Point> Queen::piecePath(Point& curPos, Point& newPos) {
    if (curPos.getX() == newPos.getX()) {
        return getHorizontalPath(curPos, newPos);
    } else if (curPos.getY() == newPos.getY()) {
        return getVerticalPath(curPos, newPos);
    } else {
        return getDiagonalPath(curPos, newPos);
    }
}
