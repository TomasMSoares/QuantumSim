# QuantumSim
Quantum circuit simulator in C++.
Given an inital quantum state vector ψ, simulates the successive application of unitary gates to ψ.

## Input
The Simulator expects the input file for the initial state in the following way:
- The first line specifies the qubit number as such: "qubits={number of qubits}"
- The second line contains the starting amplitude for each possible state.
    - The amplitudes are complex numbers given in decimal format (no support for fractions yet), e.g "2i", "0.443", "-0.4+1.5i".
    - The amplitudes are separated by spaces.
    - If the number of read amplitudes isn't equal to 2^{number of qubits}, the inout will fail.