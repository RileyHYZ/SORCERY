#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

#include <string>

class SorceryException {
  public:
    SorceryException();
    virtual ~SorceryException() = default;
    virtual std::string what() = 0;
};

class InvalidMoveException : public SorceryException {
  public:
    InvalidMoveException();
    virtual ~InvalidMoveException() = default;
};

class InvalidDefaultPromotionPieceException : public SorceryException {
  public:
    InvalidDefaultPromotionPieceException();
    std::string what();
};

class DidNotMoveException : public InvalidMoveException {
  public:
    DidNotMoveException();
    std::string what();
};

class OutOfBoundsException : public InvalidMoveException {
  public:
    OutOfBoundsException();
    std::string what();
};

class InvalidSquareSelectionException : public InvalidMoveException {
  public:
    InvalidSquareSelectionException();
    std::string what();
};

class BlockedPathException : public InvalidMoveException {
  public:
    BlockedPathException();
    std::string what();
};

class InvalidPieceMovementException : public InvalidMoveException {
  public:
    InvalidPieceMovementException();
    std::string what();
};

#endif