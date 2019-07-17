#include <vector>

#include "chessPiece.h"
#include "color.h"
#include "point.h"

using namespace std;

// Chess Piece

ChessPiece::ChessPiece(Color c) : color{c} {}

ChessPiece::~ChessPiece() {}

Color ChessPiece::getColor() {
     return color;
}

string ChessPiece::getViewIcon() {
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

vector<Point> ChessPiece::getValidMoves(Point& pos, Color player, int endRow, int endCol) {
    vector<Point> v;
    vector<Point> vm = validMoves(pos, player, endRow, endCol);
    for (Point& p : vm) {
        vector<Point> path = getPiecePath(pos, p);
        v.insert(v.end(), path.begin(), path.end());
    }
    return v;
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

vector<Point> ChessPiece::getHorizontalMoves(Point& pos, int endRow, int endCol) {
    return vector<Point> {
        Point{pos.getX(), 0},
        Point{pos.getX(), endCol}
    };
}

vector<Point> ChessPiece::getVerticalMoves(Point& pos, int endRow, int endCol) {
    return vector<Point> {
        Point{0, pos.getY()},
        Point{endRow, pos.getY()}
    };
}

vector<Point> ChessPiece::getDiagonalMoves(Point& pos, int endRow, int endCol) {
    vector<Point> v;
    int diagTopLeft = min(endRow - pos.getX(), pos.getY());
    int diagTopRight = min(endRow - pos.getX(), endCol - pos.getY());
    int diagBottomLeft = min(pos.getX(), pos.getY());
    int diagBottomRight = min(pos.getX(), endCol - pos.getY());
    v.push_back(Point{pos.getX() + diagTopLeft, pos.getY() - diagTopLeft});
    v.push_back(Point{pos.getX() + diagTopRight, pos.getY() + diagTopRight});
    v.push_back(Point{pos.getX() - diagBottomLeft, pos.getY() - diagBottomLeft});
    v.push_back(Point{pos.getX() - diagBottomRight, pos.getY() + diagBottomRight});
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

string Pawn::displayIcon() {
    return getColor() == Color::WHITE ? "\u2659" : "\u265F";
}
		
bool Pawn::isValidMove(Point& curPos, Point& newPos, bool capture) {
    int incr = getColor() == Color::WHITE ? 1 : -1;
    bool forwardOne = newPos.getX() == curPos.getX() + incr && newPos.getY() == curPos.getY();
    return (capture && isDiagonalMove(curPos, newPos, 1)) || forwardOne; 
}

vector<Point> Pawn::piecePath(Point& curPos, Point& newPos) {
    return vector<Point>{newPos};
}

vector<Point> Pawn::validMoves(Point& pos, Color player, int endRow, int endCol) {
    vector<Point> v;
    int increment = player == Color::WHITE ? 1 : -1; 

    v.push_back(Point{pos.getX() + increment, pos.getY()}); // Forward
    v.push_back(Point{pos.getX() + increment, pos.getY() - 1}); // Diagonal left
    v.push_back(Point{pos.getX() + increment, pos.getY() + 1}); // Diagonal right

    return v;
}

// Knight

Knight::Knight(Color c) : ChessPiece{c} {
    type = "knight";
}

bool Knight::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return abs(curPos.getX() - newPos.getX()) + abs(curPos.getY() - newPos.getY()) == 3;
}

string Knight::displayIcon() {
    return getColor() == Color::WHITE ? "\u2658" : "\u265E";
}

vector<Point> Knight::piecePath(Point& curPos, Point& newPos) {
    return vector<Point>{newPos};
}

vector<Point> Knight::validMoves(Point& pos, Color player, int endRow, int endCol) {
    vector<Point> v;

    for (int i = -2; i <= 2; ++i) {
        if (i == 0) continue;
        int y = abs(i) == 2 ? 1 : 2;
        v.push_back(Point{pos.getX() + i, pos.getY() + y});
        v.push_back(Point{pos.getX() + i, pos.getY() - y});
    }

    return v;
}

// Bishop

Bishop::Bishop(Color c) : ChessPiece{c} {
    type = "bishop";
}

bool Bishop::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return isDiagonalMove(curPos, newPos);
}

string Bishop::displayIcon() {
    return getColor() == Color::WHITE ? "\u2657" : "\u265D";
}

vector<Point> Bishop::piecePath(Point& curPos, Point& newPos) {
    return getDiagonalPath(curPos, newPos);
}

vector<Point> Bishop::validMoves(Point& pos, Color player, int endRow, int endCol) {
    return getDiagonalMoves(pos, endRow, endCol);
}

// Rook

Rook::Rook(Color c) : ChessPiece{c} {
    type = "rook";
}

bool Rook::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return curPos.getX() == newPos.getX() || curPos.getY() == newPos.getY();
}

string Rook::displayIcon() {
    return getColor() == Color::WHITE ? "\u2656" : "\u265C";
}

vector<Point> Rook::piecePath(Point& curPos, Point& newPos) {
    if (curPos.getX() == newPos.getX()) {
        return getHorizontalPath(curPos, newPos);
    } else if (curPos.getY() == newPos.getY()) {
        return getVerticalPath(curPos, newPos);
    }
    return vector<Point>{};
}

vector<Point> Rook::validMoves(Point& pos, Color player, int endRow, int endCol) {
    vector<Point> v = getHorizontalMoves(pos, endRow, endCol);
    vector<Point> vertical = getVerticalMoves(pos, endRow, endCol);
    v.insert(v.end(), vertical.begin(), vertical.end());
    return v;
}

// King

King::King(Color c) : ChessPiece{c} {
    type = "king";
}

std::string King::displayIcon() {
    return getColor() == Color::WHITE ? "\u2654" : "\u265A";
}

bool King::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return false;
}

vector<Point> King::piecePath(Point& curPos, Point& newPos) {
    return vector<Point>{};
}

vector<Point> King::validMoves(Point& pos, Color player, int endRow, int endCol) {
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

string Queen::displayIcon() {
    return getColor() == Color::WHITE ? "\u2655" : "\u265B";
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

vector<Point> Queen::validMoves(Point& pos, Color player, int endRow, int endCol) {
    vector<Point> v = getHorizontalMoves(pos, endRow, endCol);
    vector<Point> vertical = getVerticalMoves(pos, endRow, endCol);
    vector<Point> diagonal = getDiagonalMoves(pos, endRow, endCol);
    v.insert(v.end(), vertical.begin(), vertical.end());
    v.insert(v.end(), diagonal.begin(), diagonal.end());
    return v;
}
