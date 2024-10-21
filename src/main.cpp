#include <unistd.h>

#include "utils.h"
#include "State.h"
#include "Gate.h"

void handleCommand(const std::string& command, State& s){
    if (command == "list"){
        listCommands();
        return;
    }
    else if (command == "show") {
        s.printState();
        return;
    }
    else if (command == "check") {
        if (s.isValid()){
            std::cout << "State is valid!" << std::endl;
        }
        else {
            std::cout << "State is invalid! Sum of norms is: " << s.getSumOfSquares() << std::endl;
        }
        return;
    }
    else if (command == "exit") {
        std::cout << "Exiting the simulator. Bye!" << std::endl;
        exit(0);
    }

    std::istringstream iss(command);
    std::string gateName;
    size_t idx;
    std::vector<size_t> indices;

    if (iss >> gateName) {
        while(iss >> idx) {
            indices.push_back(idx);
        }

        // first of all we check the validity of the indices
        if(indices.empty()){
            std::cerr << "Error: No indices provided for gate." << std::endl;
            return;
        }
        for (const auto& idx : indices){
            if (idx >= s.getQubitNr()){
                std::cerr << "Error: Index " << idx << " out of range." << std::endl;
                return;
            }
        }
        
        if (gateName == "paulix") {
            Gate pauliX(GateType::PauliX, indices);
            pauliX.apply(s);
        }
        else if (gateName == "pauliy") {
            Gate pauliY(GateType::PauliY, indices);
            pauliY.apply(s);
        }
        else if (gateName == "pauliz"){
            Gate pauliZ(GateType::PauliZ, indices);
            pauliZ.apply(s);
        }
        else if (gateName == "hadamard") {
            Gate hadamard(GateType::Hadamard, indices);
            hadamard.apply(s);
        }
        else if (gateName == "cnot") {
            Gate cnot(GateType::CNot, indices);
            cnot.apply(s);
        }
        else if (gateName == "measure") {
            Gate measure(GateType::Measure, indices);
            measure.apply(s);
        }
        else {
            std::cerr << "Unknown gate: " << gateName << std::endl;
        }
    }
}


int main(int argc, char** argv){
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
        std::cerr << "Error: Initial state file is required!" << std::endl;
        printHelp();
        return 1;
    }

    State s{};
    if (!s.parseVector(vec_file)){
        std::cerr << "Error: Couldn't parse vector from file: " << vec_file << std::endl;
        printHelp();
        return 1;
    }

    std::cout << "\033[33mWelcome to my Quantum Circuit Simulator!\033[0m" << std::endl;
    std::cout << "Use 'list' to see all available commands." << std::endl;

    std::string command;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);
        lower(command, command);
        command = trim(command);
        handleCommand(command, s);
    }

    return 0;
}