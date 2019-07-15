#include <iostream>
#include "point.h"

using namespace std;

// Public Methods

// Accessors

int Point::getX() {
    return x;
}

int Point::getY() {
    return y;
}

// Constructor

Point::Point(int x, int y) : x{x}, y{y} {}

// Overloaded Equality/Inequality Operators

bool Point::operator==(Point& p) {
    return x == p.x && y == p.y;
}

bool Point::operator!=(Point& p) {
    return !(*this == p);
}

// Overloaded Input/Output Operators

istream& operator>>(istream& in, Point& p) {
    int rank;
    char file;
    in >> file >> rank;

    p.x = rank - 1;
    p.y = file - 'a';

    return in;
}

ostream& operator<<(ostream& out, Point& p) {
    return out << char(p.y + 'a') << p.x + 1 << endl;
}