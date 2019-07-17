#include <string>

#include "exception.h"

using namespace std;

// Sorcery Exception
// Abstract base class for all exceptions thrown in the game

SorceryException::SorceryException() {}

SorceryException::~SorceryException() {}

// Invalid Move Exception
// Abstract base class for all exceptions thrown relating to moving a piece

InvalidMoveException::InvalidMoveException() {}

InvalidMoveException::~InvalidMoveException() {}

// Invalid Default Promotion Piece Exception

InvalidDefaultPromotionPieceException::InvalidDefaultPromotionPieceException() {}

string InvalidDefaultPromotionPieceException::what() {
    return "Invalid default promotion piece selected. Can only select queen, bishop, knight or rook";
}

// Did Not Move Exception

DidNotMoveException::DidNotMoveException() {}

string DidNotMoveException::what() {
    return "Position entered is same as current position";
}

// Out of Bounds Exception

OutOfBoundsException::OutOfBoundsException() {}

string OutOfBoundsException::what() {
    return "Position entered is out of bounds of the board.";
}


// No Piece Selected Exception

NoPieceSelectedException::NoPieceSelectedException() {}

string NoPieceSelectedException::what() {
    return "No piece selected.";
}

// Wrong Piece Selected Exception

WrongPieceSelectedException::WrongPieceSelectedException() {}

string WrongPieceSelectedException::what() {
    return "Selected wrong player's piece";
}

// Blocked Path Exception

BlockedPathException::BlockedPathException() {}

string BlockedPathException::what() {
    return "There is another piece blocking the path of this move.";
}

// Invalid Piece Movement Exception

InvalidPieceMovementException::InvalidPieceMovementException() {}

string InvalidPieceMovementException::what() {
    return "Cannot move this piece in this way.";
}