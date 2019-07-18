#include "game.h"

#include <iostream>
#include <sstream>

using namespace std;

// Adapted from CS 247 Tutorial 9 code

int main(int argc, char* argv[]) {
    bool textOnly = false;
    bool graphicOnly = false;
    bool enhancementsOn = false;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-text" && !graphicOnly) textOnly = true;
        if (arg == "-enablebonus") enhancementsOn = true;
        if (arg == "-graphic" && !textOnly) graphicOnly = true;
    }

    Game g{textOnly, graphicOnly, enhancementsOn};
    g.start();
}