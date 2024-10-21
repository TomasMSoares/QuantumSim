#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include "State.h"

enum class GateType {
    PauliX,
    PauliY,
    PauliZ,
    Hadamard,
    CNot,
    Measure,
    Custom
};

class Gate {
public:
    /*
    Quantum gate containing information on the type and what indices it should be applied to.
    */
    Gate(GateType type, std::vector<size_t>& qubitIndices) : _type(type), _indices(qubitIndices) {};

    /*
    Wrapper for application of a gate to the given state.
    */
    bool apply(State& s);

private:
    GateType _type;

    /*
    Vector containing state indices that gate should be applied to.
    */
    std::vector<size_t> _indices;

    /*
    This attribute should only be initialized in the case of a custom matrix.
    */
    std::vector<std::vector<double>> matrix;

    bool applyPauliX(State& s);
    bool applyPauliY(State& s);
    bool applyPauliZ(State& s);
    bool applyHadamard(State& s);
    bool applyCNot(State& s);
    bool applyCustomGate(State& s);
    int measure(State& s);
};