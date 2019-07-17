#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "command.h"
#include "point.h"

#include <string>

// Adapted from CS 247 Tutorial 9 code

class Controller {
    virtual Command command() = 0;
    virtual Point& point() = 0;
    virtual char piece() = 0;

  public:
    virtual ~Controller() = default;
    Command getCommand();
    Point& getPoint();
    char getPiece();
};

#endif
