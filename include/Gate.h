#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <unordered_map>
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
    Sdg,
    Tdg,
    Rx,
    Ry,
    Rz,
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

    void setAngle(double angle);

private:
    GateType _type;

    /*
    Vector containing state indices that gate should be applied to.
    */
    std::vector<size_t> _indices;

    /*
    This attribute should only be initialized in the case of rotation gates.
    */
    double _angle = 0.0;

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
    bool applySdg(State& s);
    bool applyTdg(State& s);
    bool applySwap(State& s);
    bool applyFredkin(State& s);
    bool applyRx(State& s);
    bool applyRy(State& s);
    bool applyRz(State& s);
    bool applyCustom(State& s);

    /*
    Measurement of qubits/the whole state.
    */
    int measure(State& s);


    /*
    Before initializing the custom gates' matrices, we need to check that the
    columns/rows are orthonormal vectors. Therefore passing this monstrocity as a parameter...
    */
    bool isUnitary(std::vector<std::vector<std::complex<double>>>& matrix);
};

/*
Factored out string to GateType conversion.
*/
static const std::unordered_map<std::string, GateType> gateTypeMap = {
    {"paulix", GateType::PauliX},
    {"x", GateType::PauliX},
    {"y", GateType::PauliY},
    {"z", GateType::PauliZ},
    {"pauliy", GateType::PauliY},
    {"pauliz", GateType::PauliZ},
    {"hadamard", GateType::Hadamard},
    {"h", GateType::Hadamard},
    {"s", GateType::S},
    {"t", GateType::T},
    {"sdg", GateType::Sdg},
    {"tdg", GateType::Tdg},
    {"rx", GateType::Rx},
    {"ry", GateType::Ry},
    {"rz", GateType::Rz},
    {"cnot", GateType::CNot},
    {"cx", GateType::CNot},
    {"toffoli", GateType::Toffoli},
    {"ccnot", GateType::Toffoli},
    {"ccx", GateType::Toffoli},
    {"swap", GateType::Swap},
    {"fredkin", GateType::Fredkin},
    {"cswap", GateType::Fredkin},
    {"measure", GateType::Measure}
};

/*
Random engine for the state measurements.
Note: the engine is declared independent of the objects' lifetime to avoid reseeding.
*/
static std::default_random_engine randomEngine(std::random_device{}());