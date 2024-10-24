#pragma once

#include <unordered_map>
#include <unordered_set>
#include "State.h"
#include "Gate.h"
#include "utils.h"

class Simulator{
public:
    Simulator() : s() {}
    
    bool loadState(std::string& filename);

    void parseCommand(const std::string& command);

    void handleLoad(std::istringstream& iss);

    void handleGateCommand(std::string& gateName, std::istringstream& iss);

    void printCustomGates();

/*
Printing utilities
*/

    void listCommands();

    void printHelp();

    bool exitCmd = false;

private:
    State s;
    std::unordered_map<std::string, Gate> customGates;
};

const extern std::string helpMessage;