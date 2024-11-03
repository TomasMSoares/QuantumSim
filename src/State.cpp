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
        entry += "\033[96m|" + binary(i, _qubitNr) + ">\033[0m";
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
    std::string amountStr;
    std::string label;
    char equals;

    // Parse the "qubits = <number>" line
    auto equalPos = line.find('=');
    if (equalPos == std::string::npos) {
        std::cerr << "Couldn't parse qubit number." << std::endl;
        return false;
    }
    label = line.substr(0, equalPos);
    label = trim(label);
    amountStr = line.substr(equalPos + 1, line.size() - equalPos);
    amountStr = trim(amountStr);
    
    if (label != "qubits") {
        std::cerr << "Couldn't parse qubit number." << std::endl;
        return false;
    }

    _qubitNr = std::stoul(amountStr);
    if (!_qubitNr) {
        std::cerr << "Qubit number can't be 0." << std::endl;
        return false;
    }

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

    // Parse each amplitude separated by commas
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

void State::printDistribution() const{
    const size_t possibleStates = 1 << _qubitNr;
    std::cout << "\033[33mDistribution:\033[0m" << std::endl;
    bool printed = false; // just to separate the probabilities by commas

    for (size_t i = 0; i < possibleStates; ++i){
        std::string entry = "\033[96m|" + binary(i, _qubitNr) + ">\033[0m" + ":";
        double prob = std::norm(_state[i]);
        if (std::abs(prob) < EPS){
             continue;
        }
        if (printed) {
            std::cout << ", ";
        }
        printed = true;
        std::string probString = std::to_string(prob);
        entry += removeTrailingZeros(probString);
        std::cout << entry;
    }
    std::cout << std::endl;
}