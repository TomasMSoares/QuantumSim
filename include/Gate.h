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
    Toffoli,
    S,
    T,
    Swap,
    Fredkin,
    Measure,
    Custom
};

class Gate {
public:

    Gate(GateType type) : _type(type) {}

    /*
    Wrapper for application of a gate to the given state.
    */
    bool apply(State& s);

    /*
    Loads a gate in matrix format from the given file.
    The first line must specify the matrix dimensions: assuming the matrix is square,
    it should be specified as "dim = <n>", meaning a nxn matrix will be read.
    The lines of the file are the rows of the matrix, and the entries in a single
    line should be separated by commas.
    Example:
    dim = 2
    0.5i, 0.3+0.4i
    -1, 0
    */
    bool loadGate(std::string& filename);

    void setIndices(std::vector<size_t>& indices);

private:
    GateType _type;

    /*
    Vector containing state indices that gate should be applied to.
    */
    std::vector<size_t> _indices;

    /*
    This attribute should only be initialized in the case of a custom matrix.
    */
    std::vector<std::vector<std::complex<double>>> _matrix;

    bool applyPauliX(State& s);
    bool applyPauliY(State& s);
    bool applyPauliZ(State& s);
    bool applyHadamard(State& s);
    bool applyCNot(State& s);
    bool applyToffoli(State& s);
    bool applyS(State& s);
    bool applyT(State& s);
    bool applySwap(State& s);
    bool applyFredkin(State& s);
    bool applyCustom(State& s);
    int measure(State& s);
};