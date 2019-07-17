#ifndef __MODEL_H__
#define __MODEL_H__

#include "controller.h"
#include "view.h"

#include <memory>
#include <vector>

enum Command;

// Adapted from CS 247 Tutorial 9 code

class Model {
    std::vector<std::unique_ptr<View>> views;
    std::unique_ptr<Controller> controller;

  protected:
    void addView(std::unique_ptr<View>);
    void addController(std::unique_ptr<Controller>);

  public:
    Model();
    virtual ~Model() = default;
    Command getCommand();
    void displayMessage(const std::string&);
    void displayViews();
};

#endif
