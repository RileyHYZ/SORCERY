#ifndef __VIEW_H__
#define __VIEW_H__

class Game;

// Adapted from CS 247 Tutorial 9 code

class View {
  public:
    virtual ~View() = default;
    // virtual void update(const std::string& msg) = 0;
    // virtual void update(int row, int col, State state) = 0;
    virtual void updateView() = 0;
};

#endif