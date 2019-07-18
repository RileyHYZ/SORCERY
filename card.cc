#include "card.h"

using namespace std;

// Constructor

Card::Card(Value v) : v{v} {}

// Accessors

Card::Value Card::getValue() {
    return v;
}

string Card::getName() const {
    switch (v) {
        case Card::BLANK:
            return "BLANK";
        case Card::CURSE:
            return "CURSE";
        case Card::ENCHANTMENT:
            return "ENCHANTMENT";
        case Card::FIRECOLUMN:
            return "FIRE COLUMN";
        case Card::PLUSONEHP:
            return "PLUS ONE HP";
        case Card::MOAT:
            return "MOAT";
        case Card::DESTRUCTION:
            return "DESTRUCTION";
        case Card::RESURRECTION:
            return "RESURRECTION";
        default:
            return "";
    }
}

string Card::getDescription() {
    switch (v) {
        case Card::BLANK:
            return "This card does not do anything.";
        case Card::CURSE:
            return "Opponent loses 1 HP.";
        case Card::ENCHANTMENT:
            return "Skip opponent's turn and move again.";
        case Card::FIRECOLUMN:
            return "All pieces in front are destroyed.";
        case Card::PLUSONEHP:
            return "Gain 1 HP.";
        case Card::MOAT:
            return "All pieces in the row are destroyed.";
        case Card::DESTRUCTION:
            return "Destroys all pieces in the 3x3 square surrounding the piece.";
        case Card::RESURRECTION:
            return "All pieces are revived and army is reset.";
        default:
            return "";
    }
}

// Overloaded equality/inequality operators

bool Card::operator==(const Card& c) const {
    return v == c.v;
}

bool Card::operator!=(const Card& c) const {
    return v != c.v;
}

// Hash for card

size_t Card::CardHash::operator()(const Card& c) const {
    return hash<int>()(c.v);
}