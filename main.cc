#include "game.h"

#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
    bool textOnly = false;

    for ( int i = 1; i < argc; ++i ) {
        string arg = argv[i];
        if (arg == "-text") textOnly = true;
    }

    Game g{textOnly};
    g.start();
}