#include "State.h"

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

void State::updateAmplitude(size_t idx, std::complex<double> value){
    if (idx >= (1 << _qubitNr)){
        std::cerr << "Specified index out of range." << std::endl;
        return;
    }
    _state[idx] = value;
}

void State::printState(){
    const size_t possibleStates = 1 << _qubitNr;
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

bool State::parseVector(const std::string& filename){
    std::ifstream file(filename);
    if (!file){
        std::cerr << "Couldn't open file: " << filename << std::endl;
        return false;
    }

    std::string line;
    if (!std::getline(file, line)){
        std::cerr << "Qubit number can't be empty!" << std::endl;
    }
    line = trim(line);
    std::istringstream qubitstream(line);
    size_t qubits;
    std::string label;
    char equals;

    if (!(qubitstream >> label >> equals >> qubits)
    || label != "qubits" || equals != '=') {
        std::cerr << "Couldn't parse qubit number." << std::endl;
        return false;
    }
    _qubitNr = qubits;

    if (!std::getline(file, line)){
        std::cerr << "Amplitudes can't be empty!" << std::endl;
    }
    std::istringstream amplitudestream(line);
    std::string ampStr;
    size_t idx = 0;
    while (std::getline(amplitudestream, ampStr)){
        _state[idx] = readComplex(ampStr);
        ++idx;
    }

    if(idx != (1 << qubits) - 1){
        std::cerr << "Amplitude count mismatch: expected " << qubits <<
        " but got " << (idx + 1) << std::endl;
        return false;
    }
    return true;
}