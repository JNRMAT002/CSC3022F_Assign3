/*
    Matthew January JNRMAT002
    Executable for CSC3022F Assignment 3
*/

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
// #include "PGMProcessor.h"

int main(int argc, char* argv[]) {
    std::string inputPGMFile;
    unsigned char ** pixels; // inputPGMFile Binary Data
    unsigned int imgWidth, imgHeight, maxVal; // Used to read the inputPGMFile data
    unsigned int minCompSize = 3; // For "-s" option | sets minimum and maximum valid component size. Default minimum set to 3
    unsigned int maxCompSize =  imgWidth*imgHeight; // Default max is imgWidth*imgHeight
    unsigned char compThresh = 128; // For "-t" option | sets threshold for component detection. Default value set to 128
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
            if ( atoi(argv[i+1]) > 255 ) { compThresh = 255; }
            else if ( atoi(argv[i+1]) < 0 ) { compThresh = 0; }
            else { compThresh = static_cast<unsigned char>( atoi(argv[i+1]) ); }
        }

        if ( strcmp( argv[i], "-p" ) == 0 ) {
            std::cout << "Print component data" << std::endl;
        }

        if ( strcmp( argv[i], "-w" ) == 0 ) {
            outputPGMFile = argv[i+1];
        }
    }

    /*
        Reading the PGM File ***
    */
        
    std::ifstream inputFile(inputPGMFile, std::ios::binary);

    if (!inputFile.is_open()) {
        std::cerr << "Error: could not open PGM file" << std::endl;
        
    }

    std::string line;

    // Read/Discard header
    std::getline(inputFile, line);
    int line_count;

    while (std::getline(inputFile, line)) {
        if (line[0] == '#') { continue; }
        else { 
            line_count = 1;
            std::istringstream ss (line);
            ss >> imgWidth >> std::ws >> imgHeight;
            // std::cout << imgWidth << " " << imgHeight << std::endl;
            break; 
        }
    }

    while (std::getline(inputFile, line)) {

        if (line_count == 1) {
            // Get pgm image maxVal
            std::istringstream ss(line);                
            ss >> maxVal;
            line_count += 1;
            // std::cout << maxVal << std::endl;
        }

        if (line_count == 2) {
            // Store pixel data in array | imgHeight = numRows, imgWidth = numCols
            pixels = new unsigned char*[imgHeight];
            for (int i = 0; i < imgHeight; i++) {
                pixels[i] = new unsigned char[imgWidth];

                for (int j = 0; j < imgWidth; j++) {
                    inputFile >> pixels[i][j];
                }
            }
            // std::cout << "TEST" << std::endl;
        }            
        
    }

    inputFile.close();

    return 0;
}