#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "command.h"

#include <string>

// Adapted from CS 247 Tutorial 9 code

class Controller {
    virtual Command command() = 0;

  public:
    virtual ~Controller() = default;
    Command getCommand();
};

#endif
