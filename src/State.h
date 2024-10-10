#include <unordered_map>
#include <complex>
#include <cmath>
#include <iostream>
#include <bitset>


// not sure if we should go lower, using this threshold for most computations
static constexpr double EPS = 1e-8;

class State {
public:
    
    /*
    Initializes quantum state vector with one qubit.
    */
    State() : _qubitNr(1), _possibleStates(2) {}

    /*
    Initializes quantum state vector with the specified amount of qubits.
    */
    State(size_t qubits) : _qubitNr(qubits), _possibleStates(1 << qubits) {}

    /*
    Returns true if the set of amplitudes in the statevector is valid.
    */
    bool isValid();

    /*
    Sets the amplitude at a specific index.
    */
    void updateAmplitude(size_t idx, std::complex<double> value);

    /*
    Provides a representation of the system.
    */
    void printState();


private:
    // might want to add a non sparse representation later, as a vector
    std::unordered_map<int, std::complex<double>> _state;
    const size_t _qubitNr;
    const size_t _possibleStates;
};