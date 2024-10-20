#include <unistd.h>

#include "utils.h"
#include "State.h"
#include "Gate.h"

void handleCommand(const std::string& command, State& s){
    std::istringstream iss(command);
    std::string gateName;
    size_t idx;

    if (iss >> gateName >> idx) {
        // first of all check if index is valid
        if (idx >= s.getQubitNr()){
            std::cerr << "Error: Index out of range." << std::endl;
        }
        else {
            if (gateName == "PauliX") {
                std::vector<size_t> indices {idx};
                Gate pauliX(GateType::PauliX, indices);
                pauliX.apply(s);
            }
            else if (gateName == "PauliY") {
                std::vector<size_t> indices {idx};
                Gate pauliY(GateType::PauliY, indices);
                pauliY.apply(s);
            }
            else if (gateName == "PauliZ"){
                std::vector<size_t> indices {idx};
                Gate pauliZ(GateType::PauliZ, indices);
                pauliZ.apply(s);
            }
            else if (gateName == "Hadamard") {
                std::vector<size_t> indices {idx};
                Gate hadamard(GateType::Hadamard, indices);
                hadamard.apply(s);
            }
            else if (gateName == "Measure") {
                std::vector<size_t> indices {idx};
                Gate measure(GateType::Measure, indices);
                measure.apply(s);
            }
            else {
                std::cerr << "Unknown gate: " << gateName << std::endl;
            }
        }
    }
    else if (command == "show") {
        s.printState();
    }
    else if (command == "check") {
        if (s.isValid()){
            std::cout << "State is valid!" << std::endl;
        }
        else {
            std::cout << "State is invalid! Sum of norms is: " << s.getSumOfSquares() << std::endl;
        }
    }
    else if (command == "exit") {
        std::cout << "Exiting the simulator. Bye!" << std::endl;
        exit(0);
    }
}


int main(int argc, char** argv){
    std::cout << "\033[33mWelcome to my Quantum Circuit Simulator!\033[0m" << std::endl;
    
    std::string vec_file;
    int opt;

    while ((opt = getopt(argc, argv, "hs:")) != -1){
        switch(opt) {
            case 's':
                vec_file = optarg;
                break;
            case 'h':
                printHelp();
                return 0;
            default:
                std::cout << "Unknown argument: " << opt << std::endl;
                printHelp();
                return 1;
        }
    }

    if (vec_file.empty()){
        std::cerr << "Initial state file is required!" << std::endl;
        printHelp();
        return 1;
    }

    State s{};
    if (!s.parseVector(vec_file)){
        std::cerr << "Couldn't parse vector from file: " << vec_file << std::endl;
        printHelp();
        return 1;
    }

    std::string command;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);
        handleCommand(command, s);
    }

    return 0;
}