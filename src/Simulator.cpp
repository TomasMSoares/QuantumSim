#include "Simulator.h"

bool Simulator::loadState(std::string& filename){
    return s.parseVector(filename);
}

void Simulator::parseCommand(const std::string& command){
    std::istringstream iss(command);
    std::string commandStart;
    
    iss >> commandStart;

    if (commandStart == "list"){
        listCommands();
        return;
    }
    else if (commandStart == "show") {
        std::string toShow;
        if (!(iss >> toShow)){
            std::cerr << "Argument for show can't be empty!" << std::endl;
        }
        else if (toShow == "state"){
            s.printState();
        }
        else if (toShow == "gates"){
            printCustomGates();
        }
        else {
            std::cerr << "Invalid argument for show. Please specify \"state\" or \"gates\"." << std::endl;
        }
        return;
    }
    else if (commandStart == "check") {
        if (s.isValid()){
            std::cout << "State is valid!" << std::endl;
        }
        else {
            std::cout << "State is invalid! Sum of norms is: " << s.getSumOfSquares() << std::endl;
        }
        return;
    }
    else if (commandStart == "exit") {
        std::cout << "Exiting the simulator. Bye!" << std::endl;
        exit(0);
    }
    else if (commandStart == "load") {
        handleLoad(iss);
        return;
    }
    else {
        handleGateCommand(commandStart, iss);
    }
}

void Simulator::handleLoad(std::istringstream& iss){
    std::string gateName, filename;
    if (iss >> gateName >> filename) {
        Gate custom(GateType::Custom);
        if (custom.loadGate(filename)){
            customGates.insert({gateName, custom});
            std::cout << "Loaded custom Gate: " << gateName << " from " << filename << std::endl;
        }
        else {
            std::cerr << "Error: Custom Gate load from " << filename << " failed." << std::endl; 
        }
    }
    else {
        std::cerr << "Error: Invalid arguments to load gate. Use load \"gatename\" \"filename\"." << std::endl;
    }
}

void Simulator::handleGateCommand(std::string& gateName, std::istringstream& iss){
    size_t idx;
    std::vector<size_t> indices;

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
        Gate pauliX(GateType::PauliX);
        pauliX.setIndices(indices);
        pauliX.apply(s);
    }
    else if (gateName == "pauliy") {
        Gate pauliY(GateType::PauliY);
        pauliY.setIndices(indices);
        pauliY.apply(s);
    }
    else if (gateName == "pauliz"){
        Gate pauliZ(GateType::PauliZ);
        pauliZ.setIndices(indices);
        pauliZ.apply(s);
    }
    else if (gateName == "hadamard") {
        Gate hadamard(GateType::Hadamard);
        hadamard.setIndices(indices);
        hadamard.apply(s);
    }
    else if (gateName == "cnot") {
        Gate cnot(GateType::CNot);
        cnot.setIndices(indices);
        cnot.apply(s);
    }
    else if (gateName == "toffoli") {
        Gate toffoli(GateType::Toffoli);
        toffoli.setIndices(indices);
        toffoli.apply(s);
    }
    else if (gateName == "s"){
        Gate sg(GateType::S);
        sg.setIndices(indices);
        sg.apply(s);
    }
    else if (gateName == "t"){
        Gate t(GateType::T);
        t.setIndices(indices);
        t.apply(s);
    }
    else if (gateName == "swap"){
        Gate swap(GateType::Swap);
        swap.setIndices(indices);
        swap.apply(s);
    }
    else if (gateName == "measure") {
        Gate measure(GateType::Measure);
        measure.setIndices(indices);
        measure.apply(s);
    }
    else if (customGates.find(gateName) != customGates.end()){
        customGates.at(gateName).setIndices(indices);
        customGates.at(gateName).apply(s); // we can't use the [] operator because Gate does not have a default constructor
    }
    else {
        std::cerr << "Unknown gate: " << gateName << std::endl;
    }
}

void Simulator::printCustomGates(){
    std::cout << "\033[33mCustom Gates:\033[0m" << std::endl;
    for (const auto& gate : customGates){
        std::cout << gate.first << std::endl;
    }
}

void Simulator::listCommands(){
    std::cout << "Available commands:" << std::endl;
    std::cout << "list                    :   Lists available commands." << std::endl;
    std::cout << "check                   :   Checks if the sum of the squared amplitudes is equal to 1." << std::endl;
    std::cout << "show state/gates        :   Lists classical states with corresponding amplitudes or loaded custom gates." << std::endl;
    std::cout << "exit                    :   Exits the simulator." << std::endl;
    std::cout << "measure   <idx>         :   Measures the specified qubit, simulating state collapse." << std::endl;
    std::cout << "paulix    <idx>         :   Applies the PauliX Gate to the given qubit." << std::endl;
    std::cout << "pauliy    <idx>         :   Applies the PauliY Gate to the given qubit." << std::endl;
    std::cout << "pauliz    <idx>         :   Applies the PauliZ Gate to the given qubit." << std::endl;
    std::cout << "hadamard  <idx>         :   Applies the Hadamard Gate to the given qubit." << std::endl;
    std::cout << "s         <idx>         :   Applies the S Gate to the given qubit." << std::endl;
    std::cout << "t         <idx>         :   Applies the T Gate to the given qubit." << std::endl;
    std::cout << "swap <idx1> <idx2>      :   Applies the Swap Gate to the specified qubits." << std::endl;
    std::cout << "cnot <ctrl> <tgt>       :   Applies the CNOT Gate to qubit tgt, with ctrl as control." << std::endl;
    std::cout << "toffoli <c1> <c2> <tgt> :   Applies the Toffoli Gate to qubit tgt, with c1 and c2 as controls." << std::endl;
    std::cout << "<gatename> <idx>        :   Applies the given custom gate to the specified qubits" << std::endl;
}

void Simulator::printHelp(){
    std::cout << helpMessage << std::endl;
}

const std::string helpMessage = R"(
Simulator arguments:
-s  :   Text file containing the number n of qubits for the simulation,
        specified in the first line of the file as qubits=<n>, and the 
        associated 2^n amplitudes for the possible states. The (complex)
        amplitudes must be given in decimal format, e.g. '0.5', '0.3+0.05i',
        'i', '-0.123'. If more (or less) than 2^n amplitudes are read, the
        simulator will throw an error.
-h  :   Prints out this help message.

Usage:  ./QuantumSimulator -s <file containing starting state>

To see the possible operations in the simulator, run the program and type 'list'.
)";