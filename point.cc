#include <iostream>
#include "point.h"

using namespace std;

// Private Methods

// Accessors

int Point::getX() {
    return x;
}

int Point::getY() {
    return y;
}

// Public Methods

Point::Point(int x, int y) : x{x}, y{y} {}

istream& operator>>(istream& in, Point& p) {

}

ostream& operator<<(ostream& out, Point& p) {

}