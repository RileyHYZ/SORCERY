#ifndef __KEYBOARDCONTROLLER_H__
#define __KEYBOARDCONTROLLER_H__

#include "controller.h"

#include <iostream>
#include <string>
#include <unordered_map>

// Adapted from CS 247 Tutorial 9 code

class KeyboardController : public Controller {
    std::istream& in;
    std::unordered_map<std::string, Command> commandMap;
    bool enhancementsOn;
  
    Command command() override;
    Point& point() override;
    char piece() override;

    void remap(const std::string&, const std::string&);

  public:
    KeyboardController(bool, std::istream&);
};

#endif
