/*
    Matthew January JNRMAT002
    Executable for CSC3022F Assignment 3
*/

#include <iostream>
#include <string>

int main(int argc, char** argv) {
    std::string inputPGMFile;
    int minCompSize, maxCompSize; // For "-s" option | sets minimum and maximum valid component size
    int compThresh; // For "-t" option | sets threshold for component detection
    std::string outputPGMFile; // For "-w" option | sets output PGM File name

    inputPGMFile = argv[argc-1]; // Input PGM File will always be the last argument in the invocation

    // Place each "option" argument in the vector "options"
    // Unnecessary to deallocate vector "options" as it is not instantiated using the "new" keyword
    //  - it will be automatically deallocated when it goes out of scope
    for (int i = 1; i < argc-1; i++) {
        if ( argv[i] == "-s" ) {
            minCompSize = std::stoi(argv[i+1]);
            maxCompSize = std::stoi(argv[i+2]);
        }

        if ( argv[i] == "-t" ) {
            compThresh = std::stoi(argv[i+1]);
        }

        if ( argv[i] = "-p" ) {
            std::cout << "Print component data";
        }

        if ( argv[i] = "-w" ) {
            outputPGMFile = argv[i+1];
        }
    }



    return 0;
}