#include <unistd.h>

#include "utils.h"
#include "State.h"
#include <vector>


int main(int argc, char** argv){
    // std::cout << "Welcome to my Quantum Circuit Simulator!" << std::endl;
    
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
    std::vector<std::string> complexTest(4);

    complexTest[0] = "2i";
    complexTest[1] = "1-0.443i";
    complexTest[2] = "0.4254+i";
    complexTest[3] = "0.333";
    
    for (auto &e : complexTest){
        auto z = readComplex(e);
        std::cout << toString(z) << std::endl;
    }
}