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

// Overloaded Input/Output Operators

istream& operator>>(istream& in, Point& p) {

}

ostream& operator<<(ostream& out, Point& p) {

}