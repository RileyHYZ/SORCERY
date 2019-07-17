#include "color.h"

using namespace std;

// Constructor

Color::Color(Value v) : v{v} {}

// Accessors

string Color::getName() {
    switch (v) {
        case Color::WHITE:
            return "WHITE";
        case Color::BLACK:
            return "BLACK";
        default:
            return "";
    }
}

// Overloaded equality/inequality operators

bool Color::operator==(const Color& c) const {
    return v == c.v;
}

bool Color::operator!=(const Color& c) const {
    return v != c.v;
}

// Hash for color

size_t Color::ColorHash::operator()(const Color& c) const {
    return hash<int>()(c.v);
}