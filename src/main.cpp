#include <unistd.h>

#include "utils.h"
#include "State.h"


int main(int argc, char** argv){
    std::cout << "Welcome to my Quantum Circuit Simulator!" << std::endl;
    
    // std::string vec_file;
    // int opt;

    // while ((opt = getopt(argc, argv, "s:")) != -1){
    //     switch(opt) {
    //         case 's':
    //             vec_file = optarg;
    //             break;
    //         case 'h':
    //             printHelp();
    //             break;
    //         default:
    //             std::cout << "Unknown argument: " << opt << std::endl;
    //             printHelp();
    //             return 1;
    //     }
    // }

    // if (vec_file.empty()){
    //     std::cerr << "Initial state file is required!" << std::endl;
    //     printHelp();
    //     return 1;
    // }



    // return 0;

    State init(2);
    init.updateAmplitude(0, {1.0/sqrt(6), 1.0/sqrt(6)});
    init.updateAmplitude(1, {1.0/std::sqrt(3), 0.0});
    init.updateAmplitude(3, {-1.0/sqrt(6), 1.0/sqrt(6)});

    if (init.isValid()) std::cout << "Valid state!" << std::endl;
    else {
        std::cout << "Invalid state." << std::endl;
        std::cout << "Sum of squares is: " << init.getSumOfSquares() << std::endl;
        return 1;
    }

    init.printState();

    return 0;
}