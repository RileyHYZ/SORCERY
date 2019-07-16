#ifndef __TEXTVIEW_H__
#define __TEXTVIEW_H__

#include "view.h"

#include <iostream>

class Game;

class TextView : public View {
    Game& model;
    int numRows;
    int numCols;
    std::ostream& out;

    void outputHP(int);

  public:
    TextView(Game&, int, int, std::ostream& = std::cout);
    // void update(const std::string& msg) override;
    // void update(int row, int col, State state) override;
    void updateView() override;
};

#endif