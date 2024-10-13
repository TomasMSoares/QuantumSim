#include "Gate.h"

void Gate::setIndices(std::vector<size_t> qubitIndices){
    _indices = qubitIndices;
}

bool Gate::apply(State& s){
    switch (_type){
        case GateType::PauliX:
            return applyPauliX(s);
        case GateType::PauliY:
            return applyPauliY(s);
        case GateType::PauliZ:
            return applyPauliZ(s);
        case GateType::Hadamard:
            return applyHadamard(s);
        default:
            std::cerr << "Unknown operation." << std::endl;
            return false;
    }
}

bool Gate::applyPauliX(State& s){
    if (_indices.size() != 1){
        std::cerr << "Invalid indices: Pauli-X Gate can only act on one qubit." << std::endl;
        return false;
    }
    size_t target = _indices[0];
    if (target >= s.getQubitNr()){
        std::cerr << "Error: Index out of range." << std::endl;
        return false;
    }
    size_t stateSize = 1 << s.getQubitNr();
    for (int i = 0; i < stateSize; ++i){
        size_t flipped = i ^ (1 << target);
        if (i < flipped){
            std::swap(s[i], s[flipped]);
        }
    }
    return true;
}

bool Gate::applyPauliY(State& s){
    if (_indices.size() != 1){
        std::cerr << "Invalid index: Pauli-Y Gate can only act on one qubit." << std::endl;
        return false;
    }
    std::cout << "Work in progress..." << std::endl;
    return true;
}

bool Gate::applyPauliZ(State& s){
    if (_indices.size() != 1){
        std::cerr << "Invalid index: Pauli-Z Gate can only act on one qubit." << std::endl;
        return false;   
    }
    size_t target = _indices[0];
    if (target >= s.getQubitNr()){
        std::cerr << "Error: Index out of range." << std::endl;
        return false;
    }
    size_t stateSize = 1 << s.getQubitNr();
    for (int i = 0; i < stateSize; ++i){
        if (i & (1 << target)){
            s[i] = -s[i];
        }
    }
    return true;
}

bool Gate::applyHadamard(State& s){
    if (_indices.size() != 1){
        std::cerr << "Invalid index: Hadamard Gate can only act on one qubit." << std::endl;
        return false;
    }
    std::cout << "Work in progress..." << std::endl;
    return true;
}

bool Gate::applyCustomGate(State& s){
    //TODO
    return true;
}