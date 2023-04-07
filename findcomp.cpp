/*
    Matthew January JNRMAT002
    Executable for CSC3022F Assignment 3
*/

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include "PGMProcessor.h"

using namespace JNRMAT002;

int main(int argc, char* argv[]) {
    std::string inputPGMFile;
    unsigned int imgWidth, imgHeight; // Used to read the inputPGMFile data
    unsigned int minCompSize = 3; // For "-s" option | sets minimum and maximum valid component size. Default minimum set to 3
    unsigned int maxCompSize =  0; // Default max is imgWidth*imgHeight
    unsigned char compThresh = 128; // For "-t" option | sets threshold for component detection. Default value set to 128
    std::string outputPGMFile; // For "-w" option | sets output PGM File name
    bool print_ = false;

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
            if ( atoi(argv[i+1]) > 255 ) { compThresh = 255; }
            else if ( atoi(argv[i+1]) < 0 ) { compThresh = 0; }
            else { compThresh = static_cast<unsigned char>( atoi(argv[i+1]) ); }
        }

        if ( strcmp( argv[i], "-p" ) == 0 ) {
            print_ = true;
            // std::cout << "Print component data" << std::endl;
        }

        if ( strcmp( argv[i], "-w" ) == 0 ) {
            outputPGMFile = argv[i+1];
        }
    }
    

    // Set default size if no maxSize was entered in the cmd invocation
    // if (maxCompSize == 0) {
    //     maxCompSize = 0;
    // }

    PGMProcessor p(inputPGMFile);
    p.extractComponents(compThresh,minCompSize);
    p.filterComponentsBySize(minCompSize, maxCompSize);
    if (print_) {
        p.print();
    }
    

    return 0;
}