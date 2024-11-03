#include "Gate.h"

void Gate::setIndices(std::vector<size_t>& indices){
    _indices = indices;
}

void Gate::setAngle(double angle){
    _angle = angle;
}

bool Gate::apply(State& s){
    int outcome = 0; // we need to declare the outcome here because cases are not treated as scopes...
    switch (_type){
        case GateType::PauliX:
            return applyPauliX(s);
        case GateType::PauliY:
            return applyPauliY(s);
        case GateType::PauliZ:
            return applyPauliZ(s);
        case GateType::Hadamard:
            return applyHadamard(s);
        case GateType::CNot:
            return applyCNot(s);
        case GateType::Toffoli:
            return applyToffoli(s);
        case GateType::S:
            return applyS(s);
        case GateType::T:
            return applyT(s);
        case GateType::Swap:
            return applySwap(s);
        case GateType::Fredkin:
            return applyFredkin(s);
        case GateType::Rx:
            return applyRx(s);
        case GateType::Ry:
            return applyRy(s);
        case GateType::Rz:
            return applyRz(s);
        case GateType::Custom:
            return applyCustom(s);
        case GateType::Measure:
            outcome = measure(s);
            if (outcome != -1){
                if (_indices.empty()){
                    std::cout << "\033[95mMeasured System: " << "\033[96m" << binary(outcome, s.getQubitNr()) << "\033[0m" << std::endl;
                }
                return true;
            }
            return false;
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

bool Gate::applyCNot(State& s){
    if (_indices.size() != 2) {
        std::cerr << "\033[31mError: \033[0mCNot Gate requires exactly two indices (control and target)." << std::endl;
        return false;
    }
    size_t ctrl = _indices[0];
    size_t target = _indices[1];
    size_t stateSize = 1 << s.getQubitNr();
    
    for (size_t i = 0; i < stateSize; ++i){
        if (i & (1 << ctrl)){
            size_t flipped = i ^ (1 << target);
            if (i < flipped){
                std::swap(s[i], s[flipped]);
            }
        }
    }
    return true;
}

bool Gate::applyToffoli(State& s){
    if (_indices.size() != 3) {
        std::cerr << "\033[31mError: \033[0mToffoli Gate requires exactly three indices (ctrl1, ctrl2 and target)." << std::endl;
        return false;
    }
    size_t ctrl1 = _indices[0];
    size_t ctrl2 = _indices[1];
    size_t target = _indices[2];
    size_t stateSize = 1 << s.getQubitNr();
    
    for (size_t i = 0; i < stateSize; ++i){
        if ((i & (1 << ctrl1)) && i & (1 << ctrl2)){
            size_t flipped = i ^ (1 << target);
            if (i < flipped){
                std::swap(s[i], s[flipped]);
            }
        }
    }
    return true;
}

bool Gate::applyS(State& s){
    if (_indices.size() != 1){
        std::cerr << "Invalid index: S Gate can only act on one qubit." << std::endl;
        return false;
    }
    size_t target = _indices[0];
    size_t stateSize = 1 << s.getQubitNr();

    std::complex<double> phase(0, 1);
    for (size_t i = 0; i < stateSize; ++i) {
        if (i & (1 << target)){
            s[i] *= phase;
        }
    }
    return true;
}

bool Gate::applyT(State& s){
    if (_indices.size() != 1){
        std::cerr << "Invalid index: T Gate can only act on one qubit." << std::endl;
        return false;
    }
    size_t target = _indices[0];
    size_t stateSize = 1 << s.getQubitNr();

    // We are using Euler's Formula for simplicity:
    // https://en.wikipedia.org/wiki/Euler%27s_formula
    // Since cos(pi/4) = sin(pi/4) = sqrt(2)/2, we can compute it directly.
    std::complex<double> phase(std::sqrt(2) / 2, std::sqrt(2) / 2);
    for (size_t i = 0; i < stateSize; ++i){
        if (i & (1 << target)){
            s[i] *= phase;
        }
    }
    return true;
}

bool Gate::applySwap(State& s){
    if (_indices.size() != 2){
        std::cerr << "Invalid index: Swap Gate requires exactly two qubits." << std::endl;
        return false;
    }
    size_t j = _indices[0];
    size_t k = _indices[1];
    if (j == k) {
        return true;
    }

    size_t stateSize = 1 << s.getQubitNr();
    for (size_t i = 0; i < stateSize; ++i){
        size_t flipped = swapBits(i, j, k, 1);
        if (i < flipped){
            std::swap(s[i], s[flipped]);
        }
    }
    return true;
}

bool Gate::applyFredkin(State& s){
    if (_indices.size() != 3){
        std::cerr << "Invalid index: Fredkin Gate requires exactly three qubits." << std::endl;
        return false;
    }
    size_t ctrl = _indices[0];
    size_t j = _indices[1];
    size_t k = _indices[2];
    if (j == k) {
        return true;
    }
    size_t stateSize = 1 << s.getQubitNr();
    for (size_t i = 0; i < stateSize; ++i){
        size_t flipped = swapBits(i, j, k, 1);
        if ((i < flipped) && (i & (1 << ctrl))){
            std::swap(s[i], s[flipped]);
        }
    }
    return true;
}

bool Gate::applyRx(State& s){
    if (_indices.size() != 1){
        std::cerr << "Invalid index: Rx Gate can only act on one qubit." << std::endl;
        return false;
    }
    size_t target = _indices[0];
    double cosAng = std::cos(_angle/2);
    double sinAng = std::sin(_angle/2);

    std::complex<double> imag(0,1);
    size_t stateSize = 1 << s.getQubitNr();
    for (size_t i = 0; i < stateSize; ++i){
        size_t flipped = i ^ (1 << target);
        if (i < flipped){
            auto orig =  s[i];
            auto origFlipped = s[flipped];
            s[i] = cosAng * orig - imag * sinAng * origFlipped;
            s[flipped] = -imag * sinAng * orig + cosAng * origFlipped;
        }
    }

    return true;
}

bool Gate::applyRy(State& s){
    if (_indices.size() != 1){
        std::cerr << "Invalid index: Ry Gate can only act on one qubit." << std::endl;
        return false;
    }
    size_t target = _indices[0];
    double cosAng = std::cos(_angle/2);
    double sinAng = std::sin(_angle/2);

    size_t stateSize = 1 << s.getQubitNr();
    for (size_t i = 0; i < stateSize; ++i){
        size_t flipped = i ^ (1 << target);
        if (i < flipped) {
            auto orig = s[i];
            auto origFlipped = s[flipped];
            s[i] = cosAng * orig - sinAng * origFlipped;
            s[flipped] = sinAng * orig + cosAng * origFlipped;
        }
    }
    return true;
}

bool Gate::applyRz(State& s){
    if (_indices.size() != 1){
        std::cerr << "Invalid index: Rz Gate can only act on one qubit." << std::endl;
        return false;
    }
    size_t target = _indices[0];
    std::complex<double> phasePos(std::cos(_angle/2), std::sin(_angle/2));
    std::complex<double> phaseNeg(std::cos(_angle/2), -std::sin(_angle/2));

    size_t stateSize = 1 << s.getQubitNr();
    for (size_t i = 0; i < stateSize; ++i){
        if (i & (1 << target)) {
            s[i] *= phaseNeg;
        }
        else {
            s[i] *= phasePos;
        }
    }
    return true;
}

bool Gate::applyCustom(State& s){
    if (_indices.size() != 1){
        std::cerr << "Sorry, only one-qubit custom gates are supported atm." << std::endl;
        return false; 
    }
    
    size_t target = _indices[0];
    size_t stateSize = 1 << s.getQubitNr();
    std::vector<std::complex<double>> newState(stateSize, 0);
    
    for (size_t i = 0; i < stateSize; ++i){
        size_t flipped = i ^ (1 << target);
        // check if target bit is set
        if (i & (1 << target)){
            newState[i] = s[flipped] * _matrix[1][0] + s[i] * _matrix[1][1];
        }
        else {
            newState[i] = s[flipped] * _matrix[0][1] + s[i] * _matrix[0][0];
        }
    }

    for (size_t i = 0; i < stateSize; ++i){
        s[i] = newState[i];
    }

    return true;
}

int Gate::measure(State& s){
    if (_indices.size() > s.getQubitNr()){
        std::cerr << "Too many qubits specified to measure!" << std::endl;
        return -1;
    }

    // generate random value between 0 and 1:
    // https://stackoverflow.com/questions/2704521/generate-random-double-numbers-in-c
    std::uniform_real_distribution<double> unif(0.0, 1.0);
    double rand = unif(randomEngine);
    size_t outcome = 0;
    size_t stateSize = 1 << s.getQubitNr();

    // we are dealing with a measurement of the whole state
    if (_indices.empty()) {
        double cumulative_prob = 0.0;
        for (size_t i = 0; i < stateSize; ++i) {
            // check if the random value falls within the current range
            cumulative_prob += std::norm(s[i]);
            if (rand < cumulative_prob) {
                outcome = i;
                break;
            }
        }
        // zero out all amplitudes, normalize the measured amplitude
        std::complex<double> measured_amplitude = s[outcome] / std::abs(s[outcome]);
        for (size_t i = 0; i < stateSize; ++i) {
            s[i] = (i == outcome) ? measured_amplitude : 0;
        }
    }

    else {
        std::cout << "\033[95mMeasuring qubits...\033[0m" << std::endl;
        for (size_t& target : _indices){
            double p1 = 0.0;
            double normFactor = 0.0;
            
            for (size_t i = 0; i < stateSize; ++i){
                if (i & (1 << target)){
                    p1 += std::norm(s[i]);
                }
            }
            if (rand < p1){
                outcome = 1;
            }
            else {
                outcome = 0;
            }
            std::cout << "Qubit " << target << ": \033[96m" << outcome << "\033[0m" << std::endl;
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
        }
    }
    return outcome;
}

bool Gate::loadGate(std::string& filename){
    std::ifstream matrixFile(filename);
    if (!matrixFile){
        std::cerr << "Couldn't open file to load matrix: " << filename << std::endl;
        return false;
    }

    std::string line;
    if (!std::getline(matrixFile, line)) {
        std::cerr << "Matrix dimensions can't be empty!" << std::endl;
        return false;
    }

    line = trim(line);
    std::string label;
    char equals;
    std::string dimStr;

    // Parse the "dim = n" line
    auto equalPos = line.find('=');
    if (equalPos == std::string::npos) {
        std::cerr << "Couldn't parse dimensions." << std::endl;
        return false;
    }
    label = line.substr(0, equalPos);
    label = trim(label);
    dimStr = line.substr(equalPos + 1, line.size() - equalPos);
    dimStr = trim(dimStr);
    
    if (label != "dim") {
        std::cerr << "Couldn't parse dimensions." << std::endl;
        return false;
    }

    size_t dim = std::stoul(dimStr);
    if (dim < 2) {
        std::cerr << "Matrix dimensions must be greater than 1." << std::endl;
        return false;
    }

    // taken from https://stackoverflow.com/questions/600293/how-to-check-if-a-number-is-a-power-of-2
    if ((dim & (dim - 1)) != 0) {
        std::cerr << "Matrix dimensions must be a power of 2." << std::endl;
        return false;
    }

    // Initialize the matrix for row insertion
    std::vector<std::vector<std::complex<double>>> matrix(dim);

    size_t rowIdx = 0;
    while(std::getline(matrixFile, line)){
        if (rowIdx >= dim){
            std::cerr << "Too many rows provided for matrix dimensions: " << dim << "x" << dim << std::endl;
            return false;
        }
        std::vector<std::complex<double>> row(dim);
        std::string valueStr;
        std::istringstream rowStream(line);
        size_t colIdx = 0;
        while (rowStream >> valueStr){
            if (colIdx >= dim){
                std::cerr << "Too many values provided for row " << rowIdx << std::endl;
                return false;
            }
            std::complex<double> value = readComplex(valueStr);
            row[colIdx] = value;
            ++colIdx;
        }
        matrix[rowIdx] = row;
        ++rowIdx;
    }

    if (!isUnitary(matrix)){
        std::cerr << "Provided matrix is not unitary!" << std::endl;
        return false;
    }

    // We only replace the old matrix here to not delete it in case of an error
    _matrix = matrix;
    return true;
}

bool Gate::isUnitary(std::vector<std::vector<std::complex<double>>>& matrix) {

    if (matrix.empty()){
        std::cerr << "Matrix for unitary check can't be empty!" << std::endl;
        return false;
    }
    
    // we iterate over the matrix row-wise in the outer and inner loop and multiply
    // the values against the complex conjugate
    size_t n = matrix.size();
    for (size_t i = 0; i < n; ++i){
        for (size_t j = 0; j < n; ++j) {
            std::complex<double> dotP = 0;
            for (size_t k = 0; k < n; ++k){
                dotP += matrix[i][k] * std::conj(matrix[j][k]);
            }
            // for the entries in the diagonal the value must be 1 (within tolerance EPS)
            if (i == j){
                if (std::abs(dotP - std::complex<double>(1, 0)) > EPS){
                    std::cout << "not equal to 1: " << toString(dotP) << std::endl;
                    return false;
                }
            }
            // for the non-diagonal entries the value must be 0 (within tolerance EPS)
            else {
                if (std::abs(dotP) > EPS) {
                    std::cout << "not equal to 0: " << toString(dotP) << std::endl;
                    return false;
                }
            }  
        }
    }
    return true;
}
