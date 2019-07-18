#include "controller.h"

// Adapted from CS 247 Tutorial 9 code

Command Controller::getCommand() {
    return command(); 
}

Point Controller::getPoint() {
    return point();
}

char Controller::getPiece() {
    return piece();
}