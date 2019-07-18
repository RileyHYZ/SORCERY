#ifndef __VIEW_H__
#define __VIEW_H__

#include <string>

class Game;

// Adapted from CS 247 Tutorial 9 code

class View {
  public:
    virtual ~View() = default;
    virtual void displayMessage(const std::string&) = 0;
    virtual void displayView() = 0;
};

#endif