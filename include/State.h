#include <vector>  
#include <complex>
#include <cmath>
#include <iostream>
#include <fstream>

#include "utils.h"

class State {
public:
    
    /*
    Initializes quantum state vector with one qubit.
    */
    State() : _state(2, 0.0), _qubitNr(1) {}

    /*
    Initializes quantum state vector with the specified amount of qubits.
    */
    State(size_t qubits) : _state(1 << qubits, 0.0), _qubitNr(qubits) {}

    bool parseVector(const std::string& filename);

    /*
    Returns the sum of all amplitudes squared.
    */
    double getSumOfSquares();

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
    std::vector<std::complex<double>> _state;
    size_t _qubitNr;
};