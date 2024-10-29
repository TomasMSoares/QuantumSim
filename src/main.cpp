    #include <unistd.h>

    #include "Simulator.h"
    #include "State.h"
    #include "Gate.h"
    #include "utils.h"

    int main(int argc, char** argv){
        std::string vec_file;
        size_t qubitNr = 1;
        int opt;

        while ((opt = getopt(argc, argv, "hs:q:")) != -1){
            switch(opt) {
                case 's':
                    vec_file = optarg;
                    break;
                case 'q':
                try {
                    qubitNr = std::stoul(optarg);
                }
                catch (std::invalid_argument&){
                    std::cerr << "Invalid number of qubits: " << optarg << std::endl;
                    return 1;
                }
                    break;
                case 'h':
                    printHelp();
                    return 0;
                default:
                    std::cout << "Unknown argument: " << opt << std::endl;
                    printHelp();
                    return 1;
            }
        }

        Simulator sim(qubitNr);

        if (!vec_file.empty()){
            if (!sim.loadState(vec_file)){
                std::cerr << "\033[31mError: \033[0mCouldn't parse vector from file: " << vec_file << std::endl;
                printHelp();
                return 1;
            }
        }

        std::cout << "\033[33mWelcome to my Quantum Circuit Simulator!\033[0m" << std::endl;
        std::cout << "Use '\033[96mlist\033[0m' to see all available commands." << std::endl;

        std::string command;
        while (!sim.exitCmd) {
            std::cout << "> ";
            std::getline(std::cin, command);
            lower(command, command);
            command = trim(command);
            sim.parseCommand(command);
        }

        return 0;
    }