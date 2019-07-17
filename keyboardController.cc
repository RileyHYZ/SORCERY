#include "keyboardController.h"

#include <string>
#include <vector>

using namespace std;

// Adapted from CS 247 Tutorial 9 code

KeyboardController::KeyboardController(istream& in) : in{in} {
    commandMap["move"] = Command::MOVE;
    commandMap["restart"] = Command::RESTART;
    commandMap["defaultpromotion"] = Command::DEFAULTPROMOTION;
    commandMap["validmoves"] = Command::VALIDMOVES;
    commandMap["enhancementson"] = Command::ENHANCEMENTSON;
    commandMap["enhancementsoff"] = Command::ENHANCEMENTSOFF;
    commandMap["quit"] = Command::QUIT;
}

Command KeyboardController::command(){
    string input;

    if (in >> input) {
        // Remap command
        if (input == "remap") {
            string oldCmd, newCmd;
            in >> oldCmd >> newCmd;
            remap(oldCmd, newCmd);
            return Command::NONE;
        }

        // Can find command in the map
        vector<Command> matchingCommands;

        for (auto kvp : commandMap) {
            // Command entirely matches
            if (input == kvp.first) return kvp.second;

            // Command partially matches
            if (input.length() <= kvp.first.length() && kvp.first.compare(0, input.length(), input) == 0) matchingCommands.push_back(kvp.second);
        }

        // Return command only if 1 match
        if (matchingCommands.size() == 1) return matchingCommands.at(0);
    }

    // No input stream or command not found in map
    return Command::INVALID;
}

Point& KeyboardController::point() {
    Point curPos{0,0};
    if(cin >> curPos) return curPos;
    return curPos;
}

char KeyboardController::piece() {
    char piece;
    if(cin >> piece) return piece;
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
