#include "State.h"

bool State::isValid(){
    double sum = 0;
    for (const auto& e : _state){
        sum += std::norm(e.second);
    }
    return std::abs(sum - 1.0) <= EPS;
}

void State::updateAmplitude(size_t idx, std::complex<double> value){
    if (idx >= _possibleStates){
        std::cerr << "Specified index out of range for vector amplitude distribution." << std::endl;
        return;
    }
    if (std::abs(value) < EPS) {
        _state.erase(idx);
    }
    else {
        _state[idx] = value;
    }
}

void State::printState(){
    std::cout << "TODO" << std::endl;
}