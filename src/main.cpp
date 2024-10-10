#include "State.h"


int main(int argc, char** argv){
    std::cout << "Welcome to my Quantum Circuit Simulator!" << std::endl;
    State init{};
    
    init.updateAmplitude(0, std::complex<double>(1/sqrt(2), 0));
    init.updateAmplitude(1, std::complex<double>(1/sqrt(2), 0));
    
    if (init.isValid()){
        std::cout << "Valid state!" << std::endl;
    }

    return 0;
}