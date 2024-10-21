#pragma once

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

    /*
    Access to the state's amplitudes.
    */
    std::complex<double>& operator[] (size_t idx);

    /*
    Returns the amount of qubits that the state contains.
    */
    size_t getQubitNr() const;

    /*
    Reads in vector of amplitudes from the given file. See README.md > Input for details.
    */
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
    Provides a representation of the system.
    */
    void printState() const;


private:
    std::vector<std::complex<double>> _state;
    size_t _qubitNr;
};