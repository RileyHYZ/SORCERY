#include <vector>

#include "chessPiece.h"
#include "color.h"
#include "point.h"

using namespace std;

// Chess Piece

ChessPiece::ChessPiece(Color c) : color{c} {}

ChessPiece::~ChessPiece() {}

void ChessPiece::setType(string type) {
    this->type = type;
}

string ChessPiece::getType() {
    return type;
}

Color ChessPiece::getColor() {
     return color;
}

// Virtual Pass-Through Methods

char ChessPiece::getDisplayIcon() {
    return displayIcon();
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
    setType("pawn");
}

char Pawn::displayIcon() {
    return getColor() == WHITE ? 'p' : 'P';
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
    setType("knight");
}

bool Knight::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return abs(curPos.getX() - newPos.getX()) + abs(curPos.getY() - newPos.getY()) == 3;
}

char Knight::displayIcon() {
    return getColor() == WHITE ? 'n' : 'N';
}

vector<Point> Knight::piecePath(Point& curPos, Point& newPos) {
    return vector<Point>{};
}

// Bishop

Bishop::Bishop(Color c) : ChessPiece{c} {
    setType("bishop");
}

bool Bishop::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return isDiagonalMove(curPos, newPos);
}

char Bishop::displayIcon() {
    return getColor() == WHITE ? 'b' : 'B';
}

vector<Point> Bishop::piecePath(Point& curPos, Point& newPos) {
    return getDiagonalPath(curPos, newPos);
}

// Rook

Rook::Rook(Color c) : ChessPiece{c} {
    setType("rook");
}

bool Rook::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return curPos.getX() == newPos.getX() || curPos.getY() == newPos.getY();
}

char Rook::displayIcon() {
    return getColor() == WHITE ? 'r' : 'R';
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
    setType("king");
}

char King::displayIcon() {
    return getColor() == WHITE ? 'k' : 'K';
}

bool King::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return false;
}

vector<Point> King::piecePath(Point& curPos, Point& newPos) {
    return vector<Point>{};
}

// Queen

Queen::Queen(Color c) : ChessPiece{c} {
    setType("queen");
}

bool Queen::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return isDiagonalMove(curPos, newPos)
                    || curPos.getX() == newPos.getX()
                    || curPos.getY() == newPos.getY();
}

char Queen::displayIcon() {
    return getColor() == WHITE ? 'q' : 'Q';
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
