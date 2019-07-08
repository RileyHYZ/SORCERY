#include <iostream>
#include "game.h"
#include "display.h"

using namespace std;

int main(void) {
    Game g;
    TextDisplay t{&g, cout};

    g.notifyObservers();
}