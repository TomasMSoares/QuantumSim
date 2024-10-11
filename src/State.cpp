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