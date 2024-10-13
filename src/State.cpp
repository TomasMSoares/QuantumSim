#include "State.h"

size_t State::getQubitNr() const{
    return _qubitNr;
}

double State::getSumOfSquares(){
    double sum = 0;
    for (const auto& a : _state){
        sum += std::norm(a);
    }
    return sum;
}

bool State::isValid(){
    return std::abs(getSumOfSquares() - 1.0) <= EPS;
}

std::complex<double>& State::operator[] (size_t idx){
    return _state[idx];
}

void State::printState() const{
    const size_t possibleStates = 1 << _qubitNr;
    std::cout << "\033[33mState:\033[0m" << std::endl;
    for (size_t i = 0; i < possibleStates; ++i){
        std::string entry = toString(_state[i]) + "*";
        entry += "\033[36m|" + binary(i, _qubitNr) + ">\033[0m";
        if (i < possibleStates - 1){
             entry += " + ";
        }
        std::cout << entry;
    }
    std::cout << std::endl;
}

bool State::parseVector(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Couldn't open file: " << filename << std::endl;
        return false;
    }

    std::string line;
    if (!std::getline(file, line)) {
        std::cerr << "Qubit number can't be empty!" << std::endl;
        return false;
    }

    line = trim(line);
    std::istringstream qubitstream(line);
    size_t qubits;
    std::string label;
    char equals;

    // Parse the "qubits = <number>" line
    if (!(qubitstream >> label >> equals >> qubits) || label != "qubits" || equals != '=') {
        std::cerr << "Couldn't parse qubit number." << std::endl;
        return false;
    }
    _qubitNr = qubits;

    // Read the line containing the amplitudes
    if (!std::getline(file, line)) {
        std::cerr << "Amplitudes can't be empty!" << std::endl;
        return false; // Return false here to handle the error case
    }
    line = trim(line);
    std::istringstream amplitudestream(line);
    std::string ampStr;
    size_t idx = 0;

    _state.resize(1 << _qubitNr);

    // Parse each amplitude separated by spaces
    while (amplitudestream >> ampStr) {
        if (idx >= _state.size()) {
            std::cerr << "Too many amplitudes provided." << std::endl;
            return false;
        }
        _state[idx] = readComplex(ampStr);
        ++idx;
    }

    // Check that the correct number of amplitudes were provided
    if (idx != (1 << _qubitNr)) {
        std::cerr << "Amplitude count mismatch: expected " << (1 << _qubitNr) 
                  << " but got " << idx << std::endl;
        return false;
    }

    return true;
}