#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <iostream>

#include "observer.h"
#include "game.h"

class Display : public Observer {
    Game* subject;

  public:
    Display(Game*);
    virtual ~Display() = 0;

    Game* getSubject();
};

class TextDisplay : public Display {
    std::ostream& out;

  public:
    TextDisplay(Game*, std::ostream&);
    ~TextDisplay();
    void notify() override;
};

#endif