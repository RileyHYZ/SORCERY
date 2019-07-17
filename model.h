#ifndef __MODEL_H__
#define __MODEL_H__

#include "controller.h"
#include "view.h"

#include <memory>
#include <vector>

enum class Command;

// Adapted from CS 247 Tutorial 9 code

class Model {
    std::vector<std::unique_ptr<View>> views;
    std::unique_ptr<Controller> controller;

  protected:
    void addView(std::unique_ptr<View>);
    void addController(std::unique_ptr<Controller>);
    bool hasController();

  public:
    Model();
    virtual ~Model() = default;
//   void updateViews(int, int, State);
    void displayMessage(const std::string& s);
    Command getCommand();
    Point& getPoint();
    char getPromotPiece();
    void displayViews();
};

#endif
