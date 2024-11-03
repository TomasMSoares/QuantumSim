# QuantumSim
Quantum circuit simulator in C++.
Given an inital quantum state vector ψ, simulates the successive application of unitary gates to ψ.

## Basic functionality
The Simulator can be initialized either with only one qubit in the zero state (no parameters),
with a specific number of qubits or an input file containing a quantum statevector.
Afterwards, the user can apply quantum (unitary) gates to the qubits to simulate a quantum circuit,
and measure the state of the individual qubits or even the whole system, with the associated simulated
state collapse. The Simulator provides commands to keep track of the amplitudes of the individual
states and the corresponding probability disrtribution.

## Input File
The Simulator expects the input file for the initial state in the following way:
- The first line specifies the qubit number as such: "qubits={number of qubits}"
- The second line contains the starting amplitude for each possible state.
    - The amplitudes are complex numbers given in decimal format (no support for fractions yet), e.g "2i", "0.443", "-0.4+1.5i".
    - The amplitudes are separated by spaces.
    - If the number of read amplitudes isn't equal to 2^{number of qubits}, the input will fail.

## Starting the program
Simulator arguments:
-s  :   Vector input file containing the number n of qubits for the simulation,
        specified in the first line of the file as qubits=<n>, and the 
        associated 2^n amplitudes for the possible states. The (complex)
        amplitudes must be given in decimal format, e.g. '0.5', '0.3+0.05i',
        'i', '-0.123'. If more (or less) than 2^n amplitudes are read, the
        simulator will throw an error.
-q  :   Number of qubits for the simulator, assuming the starting state is
        the zero state. Will be ignored if a vector input file is specified.
-h  :   Prints out this help message.

Usage:  ./QuantumSimulator -s "somefile.txt"

If no input file or qubit number are specified, the simulation will start with
only one qubit in the zero state.

## Available commands
    list                     :   Lists available commands.
    exit                     :   Exits the simulator.
    check                    :   Checks if the sum of the squared amplitudes is equal to 1 and
                                 shows the probability distribution associated with the classical states.
    show      state/gates    :   Lists classical states with corresponding amplitudes or loaded custom gates.
    measure   <x1> <...>     :   Measures the specified qubits, simulating state collapse.
    paulix    <x>            :   Applies the PauliX Gate to the given qubit.
    pauliy    <x>            :   Applies the PauliY Gate to the given qubit.
    pauliz    <x>            :   Applies the PauliZ Gate to the given qubit.
    hadamard  <x>            :   Applies the Hadamard Gate to the given qubit.
    s         <x>            :   Applies the S Gate to the given qubit.
    t         <x>            :   Applies the T Gate to the given qubit.
    swap      <a> <b>        :   Applies the Swap Gate to the specified qubits.
    cnot      <c> <x>        :   Applies the CNOT Gate to qubit x, with c as control.
    toffoli   <c1> <c2> <x>  :   Applies the Toffoli Gate to qubit x, with c1 and c2 as controls.
    fredkin   <c> <a> <b>    :   Applies the Fredkin Gate, i.e. swaps a and b if c is set.
    <custom>  <x>            :   Applies the given custom gate to the specified qubit(s).