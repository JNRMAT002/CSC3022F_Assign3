/*
    Matthew January JNRMAT002
    Executable for CSC3022F Assignment 3
*/

#include <iostream>
#include <string>
#include <cstring>

int main(int argc, char* argv[]) {
    std::string inputPGMFile;
    int minCompSize, maxCompSize; // For "-s" option | sets minimum and maximum valid component size
    unsigned char compThresh; // For "-t" option | sets threshold for component detection
    std::string outputPGMFile; // For "-w" option | sets output PGM File name

    inputPGMFile = argv[argc-1]; // Input PGM File will always be the last argument in the invocation

    // Place each "option" argument in the vector "options"
    // Unnecessary to deallocate vector "options" as it is not instantiated using the "new" keyword
    //  - it will be automatically deallocated when it goes out of scope
    for (int i = 0; i < argc-1; i++) {
        if ( strcmp( argv[i], "-s" ) == 0 ) {
            minCompSize = atoi(argv[i+1]);
            maxCompSize = atoi(argv[i+2]);
        }

        if ( strcmp( argv[i], "-t" ) == 0 ) {
            compThresh = static_cast<unsigned char>( atoi(argv[i+1]) );
        }

        if ( strcmp( argv[i], "-p" ) == 0 ) {
            std::cout << "Print component data" << std::endl;
        }

        if ( strcmp( argv[i], "-w" ) == 0 ) {
            outputPGMFile = argv[i+1];
        }
    }

    return 0;
}