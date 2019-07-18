#include "keyboardController.h"
#include "exception.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Adapted from CS 247 Tutorial 9 code

// Constructor

KeyboardController::KeyboardController(bool enhancementsOn, istream& in) : in{in}, enhancementsOn{enhancementsOn} {
    commandMap["move"] = Command::MOVE;
    commandMap["restart"] = Command::RESTART;
    commandMap["defaultpromotion"] = Command::DEFAULTPROMOTION;
    commandMap["validmoves"] = Command::VALIDMOVES;
    commandMap["quit"] = Command::QUIT;
}

// Private Helper Methods

Command KeyboardController::command() {
    string input;

    if (in >> input) {
        // Remap command
        if (input == "remap") {
            string oldCmd, newCmd;
            in >> oldCmd >> newCmd;
            remap(oldCmd, newCmd);
            return Command::NONE;
        } else if (input == "enhancements") {
            string status;
            in >> status;
            enhancementsOn = status == "on" ? true : false;
            return Command::NONE;
        }

        // Try to find command in map
        vector<Command> matchingCommands;

        for (auto kvp : commandMap) {
            // Command entirely matches
            if (input == kvp.first) {
                if (!enhancementsOn && kvp.second == Command::VALIDMOVES) throw InvalidCommandException();
                else return kvp.second;
            }

            // Command partially matches
            if (input.length() <= kvp.first.length() && kvp.first.compare(0, input.length(), input) == 0) {
                matchingCommands.push_back(kvp.second);
            }
        }

        // Return command only if 1 match
        if (matchingCommands.size() == 1) {
            if (!enhancementsOn && matchingCommands.at(0) == Command::VALIDMOVES) throw InvalidCommandException();
            else return matchingCommands.at(0);
        }
    }

    // No input stream or command not found in map
    throw InvalidCommandException();
}

Point KeyboardController::point() {
    Point point;
    cin >> point;
    return point;
}

char KeyboardController::piece() {
    char piece;
    cin >> piece;
    return piece;
}

void KeyboardController::remap(const std::string& oldCmd, const std::string& newCmd) {
    auto kvp = commandMap.find(oldCmd);

    if (kvp != commandMap.end()) {
        Command val = kvp->second;
        commandMap.erase(kvp);
        commandMap[newCmd] = val;
    }
}
