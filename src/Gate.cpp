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
        case GateType::Measure:
            std::cout << "Measured Qubit " << _indices[0] <<
            ": " << measure(s) << std::endl;
            return true;
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
    size_t target = _indices[0];
    size_t stateSize = (1 << s.getQubitNr());
    for (size_t i = 0; i < stateSize; ++i) {
        size_t flipped = i ^ (1 << target);
        if (i < flipped){
            std::swap(s[i], s[flipped]);
            s[i] *= std::complex<double>(0, 1);
            s[flipped] *= std::complex<double>(0, -1);
        }
    }
    return true;
}

bool Gate::applyPauliZ(State& s){
    if (_indices.size() != 1){
        std::cerr << "Invalid index: Pauli-Z Gate can only act on one qubit." << std::endl;
        return false;   
    }
    size_t target = _indices[0];
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
    size_t target = _indices[0];
    std::complex<double> fac(1/std::sqrt(2), 0);
    size_t stateSize = (1 << s.getQubitNr());

    for (size_t i = 0; i < stateSize; ++i){
        size_t flipped = i ^ (1 << target);
        if (i < flipped){
            std::complex<double> z1(s[i]);
            std::complex<double> z2(s[flipped]);
            s[i] = (z1 + z2) * fac;
            s[flipped] = (z1 - z2) * fac;
        }
    }
    return true;
}

bool Gate::applyCustomGate(State& s){
    //TODO
    return true;
}

int Gate::measure(State& s){
    if (_indices.size() != 1){
        std::cerr << "Invalid index: Hadamard Gate can only act on one qubit." << std::endl;
        return false;
    }

    // generate random value between 0 and 1:
    // https://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c
    std::uniform_real_distribution<double> unif(0.0, 1.0);
    std::default_random_engine re(std::random_device{}());
    double rand = unif(re);
    double p1 = 0.0; // probability for outcome 1

    size_t target = _indices[0];
    size_t stateSize = 1 << s.getQubitNr();
    for (size_t i = 0; i < stateSize; ++i){
        if (i & (1 << target)){
            p1 += std::norm(s[i]);
        }
    }

    // outcome is determined by where on the distribution the random number falls
    int outcome = 0;
    if (rand < p1){
        outcome = 1;
    }

    double normf = 0.0;
    for (size_t i = 0; i < stateSize; ++i){
        // we iterate over the state and check if the target bit of the index
        // of the current iteration is equal to the outcome; if not, we set the
        // amplitude to 0 (collapse of state)
        if ((i & (1 << target)) != outcome << target) {
            s[i] = 0;
        }
        else {
            // we can add up the norms of the amplitudes that didn't get set
            // to 0 here, this way we save iterations
            normf += std::norm(s[i]);
        }
    }

    // normalize the nonzero amplitudes
    normf = std::sqrt(normf);
    if (normf > 0) {
        for (size_t i = 0; i < stateSize; ++i){
            s[i] /= normf;
        }
    }

    return outcome;
}