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
    void displayMessage(const std::string&) override;
    void displayView() override;
};

#endif