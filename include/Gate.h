#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include "State.h"

enum class GateType {
    PauliX,
    PauliY,
    PauliZ,
    Hadamard,
    Custom
};

class Gate {
public:
    Gate(GateType type, std::vector<size_t>& qubitIndices) : _type(type), _indices(qubitIndices) {};

    void setIndices(std::vector<size_t> qubitIndices);

    bool apply(State& s);


private:
    GateType _type;
    std::vector<size_t> _indices;

    /*
    This attribute should only be initialized in the case of a custom matrix
    */
    std::vector<std::vector<double>> matrix;

    bool applyPauliX(State& s);
    bool applyPauliY(State& s);
    bool applyPauliZ(State& s);
    bool applyHadamard(State& s);
    bool applyCustomGate(State& s);
};