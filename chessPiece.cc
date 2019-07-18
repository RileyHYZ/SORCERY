#include "chessPiece.h"
#include "color.h"
#include "point.h"

#include <vector>

using namespace std;

// Chess Piece

// Constructor

ChessPiece::ChessPiece(Color c, string name) : color{c}, name{name} {}

// Accessors

string ChessPiece::getName() {
    return name;
}

Color ChessPiece::getColor() {
     return color;
}

// Protected Helper Functions

bool ChessPiece::isHorizontalMove(Point& curPos, Point& newPos) {
    return newPos.getX() == curPos.getX();
}

bool ChessPiece::isVerticalMove(Point& curPos, Point& newPos) {
    return newPos.getY() == curPos.getY();
}

bool ChessPiece::isDiagonalMove(Point& curPos, Point& newPos, int diff) {
    int xDiff = abs(newPos.getX() - curPos.getX());
    int yDiff = abs(newPos.getY() - curPos.getY());
    return diff == 0 ? xDiff == yDiff : xDiff == diff && yDiff == diff;
}

vector<Point> ChessPiece::getHorizontalPath(Point& curPos, Point& newPos) {
    vector<Point> v;

    int i = curPos.getY();
    int inc = newPos.getY() > curPos.getY() ? 1 : -1;

    while (i != newPos.getY()) {
        i += inc;
        v.push_back(Point{curPos.getX(), i});
    }

    return v;
}

vector<Point> ChessPiece::getVerticalPath(Point& curPos, Point& newPos) {
    vector<Point> v;

    int i = curPos.getX();
    int inc = newPos.getX() > curPos.getX() ? 1 : -1;

    while (i != newPos.getX()) {
        i += inc;
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

vector<Point> ChessPiece::farthestHorizontalMoves(Point& pos, int endCol) {
    return vector<Point> {
        Point{pos.getX(), 0},
        Point{pos.getX(), endCol}
    };
}

vector<Point> ChessPiece::farthestVerticalMoves(Point& pos, int endRow) {
    return vector<Point> {
        Point{0, pos.getY()},
        Point{endRow, pos.getY()}
    };
}

vector<Point> ChessPiece::farthestDiagonalMoves(Point& pos, int endRow, int endCol) {
    vector<Point> v;

    int incTopLeft = min(endRow - pos.getX(), pos.getY());
    int incTopRight = min(endRow - pos.getX(), endCol - pos.getY());
    int incBottomLeft = min(pos.getX(), pos.getY());
    int incBottomRight = min(pos.getX(), endCol - pos.getY());

    v.push_back(Point{pos.getX() + incTopLeft, pos.getY() - incTopLeft});
    v.push_back(Point{pos.getX() + incTopRight, pos.getY() + incTopRight});
    v.push_back(Point{pos.getX() - incBottomLeft, pos.getY() - incBottomLeft});
    v.push_back(Point{pos.getX() - incBottomRight, pos.getY() + incBottomRight});

    return v;
}

// Public Interface Methods (Pass-Through to Virtual Methods)

char ChessPiece::getDisplayIcon() {
    return displayIcon();
}

bool ChessPiece::checkValidMove(Point& curPos, Point& newPos, bool capture = false) {
    return isValidMove(curPos, newPos, capture);
}

vector<Point> ChessPiece::getPath(Point& curPos, Point& newPos) {
    return path(curPos, newPos);
}

vector<Point> ChessPiece::getValidMoves(Point& pos, Color player, int endRow, int endCol) {
    vector<Point> vm;
    vector<Point> fvm = farthestValidMoves(pos, player, endRow, endCol);

    // Get path to each of the farthest valid moves
    for (Point& p : fvm) {
        vector<Point> path = getPath(pos, p);
        vm.insert(vm.end(), path.begin(), path.end());
    }

    return vm;
}

// Pawn

Pawn::Pawn(Color c) : ChessPiece{c, "pawn"} {}

char Pawn::displayIcon() {
    return getColor() == Color::WHITE ? 'p' : 'P';
}
		
bool Pawn::isValidMove(Point& curPos, Point& newPos, bool capture) {
    int incr = getColor() == Color::WHITE ? 1 : -1;
    bool forwardOne = newPos.getX() == curPos.getX() + incr && newPos.getY() == curPos.getY();
    return (capture && isDiagonalMove(curPos, newPos, 1)) || (!capture && forwardOne); 
}

vector<Point> Pawn::farthestValidMoves(Point& pos, Color player, int endRow, int endCol) {
    vector<Point> v;
    int increment = player == Color::WHITE ? 1 : -1; 

    v.push_back(Point{pos.getX() + increment, pos.getY()}); // Forward
    v.push_back(Point{pos.getX() + increment, pos.getY() - 1}); // Diagonal left
    v.push_back(Point{pos.getX() + increment, pos.getY() + 1}); // Diagonal right

    return v;
}

vector<Point> Pawn::path(Point& curPos, Point& newPos) {
    return vector<Point>{newPos};
}

// Knight

Knight::Knight(Color c) : ChessPiece{c, "knight"} {}

char Knight::displayIcon() {
    return getColor() == Color::WHITE ? 'n' : 'N';
}

bool Knight::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return (abs(curPos.getX() - newPos.getX()) == 2 && abs(curPos.getY() - newPos.getY()) == 1) || 
        (abs(curPos.getX() - newPos.getX()) == 1 && abs(curPos.getY() - newPos.getY()) == 2);
}

vector<Point> Knight::farthestValidMoves(Point& pos, Color player, int endRow, int endCol) {
    vector<Point> v;

    for (int incX = -2; incX <= 2; ++incX) {
        if (incX == 0) continue; // same x value as pos

        int incY = abs(incX) == 2 ? 1 : 2;
        v.push_back(Point{pos.getX() + incX, pos.getY() + incY});
        v.push_back(Point{pos.getX() + incX, pos.getY() - incY});
    }

    return v;
}

vector<Point> Knight::path(Point& curPos, Point& newPos) {
    return vector<Point>{newPos};
}

// Bishop

Bishop::Bishop(Color c) : ChessPiece{c, "bishop"} {}

char Bishop::displayIcon() {
    return getColor() == Color::WHITE ? 'b' : 'B';
}

bool Bishop::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return isDiagonalMove(curPos, newPos);
}

vector<Point> Bishop::farthestValidMoves(Point& pos, Color player, int endRow, int endCol) {
    return farthestDiagonalMoves(pos, endRow, endCol);
}

vector<Point> Bishop::path(Point& curPos, Point& newPos) {
    return getDiagonalPath(curPos, newPos);
}

// Rook

Rook::Rook(Color c) : ChessPiece{c, "rook"} {}

char Rook::displayIcon() {
    return getColor() == Color::WHITE ? 'r' : 'R';
}

bool Rook::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return isHorizontalMove(curPos, newPos) || isVerticalMove(curPos, newPos);
}

vector<Point> Rook::farthestValidMoves(Point& pos, Color player, int endRow, int endCol) {
    vector<Point> v;
    vector<Point> hm = farthestHorizontalMoves(pos, endCol);
    vector<Point> vm = farthestVerticalMoves(pos, endRow);

    v.insert(v.end(), hm.begin(), hm.end());
    v.insert(v.end(), vm.begin(), vm.end());

    return v;
}

vector<Point> Rook::path(Point& curPos, Point& newPos) {
    if (isHorizontalMove(curPos, newPos)) {
        return getHorizontalPath(curPos, newPos);
    } else {
        return getVerticalPath(curPos, newPos);
    }
}

// King

King::King(Color c) : ChessPiece{c, "king"} {}

char King::displayIcon() {
    return getColor() == Color::WHITE ? 'k' : 'K';
}

bool King::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return false;
}

vector<Point> King::farthestValidMoves(Point& pos, Color player, int endRow, int endCol) {
    return vector<Point>{};
}

vector<Point> King::path(Point& curPos, Point& newPos) {
    return vector<Point>{};
}

// Queen

Queen::Queen(Color c) : ChessPiece{c, "queen"} {}

char Queen::displayIcon() {
    return getColor() == Color::WHITE ? 'q' : 'Q';
}

bool Queen::isValidMove(Point& curPos, Point& newPos, bool capture) {
    return isHorizontalMove(curPos, newPos) || isVerticalMove(curPos, newPos) || isDiagonalMove(curPos, newPos);
}

vector<Point> Queen::farthestValidMoves(Point& pos, Color player, int endRow, int endCol) {
    vector<Point> v;
    vector<Point> hm = farthestHorizontalMoves(pos, endCol);
    vector<Point> vm = farthestVerticalMoves(pos, endRow);
    vector<Point> dm = farthestDiagonalMoves(pos, endRow, endCol);

    v.insert(v.end(), hm.begin(), hm.end());
    v.insert(v.end(), vm.begin(), vm.end());
    v.insert(v.end(), dm.begin(), dm.end());
    
    return v;
}

vector<Point> Queen::path(Point& curPos, Point& newPos) {
    if (isHorizontalMove(curPos, newPos)) {
        return getHorizontalPath(curPos, newPos);
    } else if (isVerticalMove(curPos, newPos)) {
        return getVerticalPath(curPos, newPos);
    } else {
        return getDiagonalPath(curPos, newPos);
    }
}
