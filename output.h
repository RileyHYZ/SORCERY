#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <iostream>

#include "observer.h"
#include "game.h"
#include "window.h"

class Output : public Observer {
    Game* subject;

  public:
    Output(Game*);
    virtual ~Output() = 0;

    Game* getSubject();
};

class TextDisplay : public Output {
    std::ostream& out;

  public:
    TextDisplay(Game*, std::ostream&);
    ~TextDisplay();
    void notify() override;
};

class GraphicalDisplay : public Output {
    Xwindow *window;
    Point& getPoint(std::vector<int>);
    
  public: 
    GraphicalDisplay(Game*);
    void notify() override;
    ~GraphicalDisplay();
};
#endif