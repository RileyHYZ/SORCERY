#include "point.h"

#include <iostream>

using namespace std;

// Constructor

Point::Point(int x, int y) : x{x}, y{y} {}

// Accessors

int Point::getX() {
    return x;
}

int Point::getY() {
    return y;
}

// Overloaded Equality/Inequality Operators

bool Point::operator==(Point& p) {
    return x == p.x && y == p.y;
}

bool Point::operator!=(Point& p) {
    return !(x == p.x && y == p.y);
}

// Overloaded Input/Output Operators

istream& operator>>(istream& in, Point& p) {
    char rank;
    char file;
    in >> file >> rank;

    // assume rank starts from 1, file starts from a
    p.x = rank - '1';
    p.y = file - 'a';

    return in;
}

ostream& operator<<(ostream& out, Point& p) {
    return out << char(p.y + 'a') << p.x + 1;
}