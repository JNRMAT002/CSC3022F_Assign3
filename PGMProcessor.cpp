#include "PGMProcessor.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <iostream>

using namespace JNRMAT002;

// Constructor (Default)
PGMProcessor::PGMProcessor(std::string inputPGMFile) {
    inputPGMFile = inputPGMFile;
}

// Constructor (Copy)
PGMProcessor::PGMProcessor(const PGMProcessor &rhs) {
    inputPGMFile = rhs.inputPGMFile;
    for (size_t i = 0; i < rhs.compSharedPtr.size(); i++) {
        *(compSharedPtr[i]) = *(rhs.compSharedPtr[i]);
    }
}

// Constructor (Copy Assignment)
PGMProcessor &PGMProcessor::operator=(const PGMProcessor &rhs) {
    this->inputPGMFile = rhs.inputPGMFile;
    for (size_t i = 0; i < rhs.compSharedPtr.size(); i++) {
        *compSharedPtr[i] = *(rhs.compSharedPtr[i]);
    }
    return *this;
}

// Constructor (Move)
PGMProcessor::PGMProcessor(PGMProcessor &&rhs) {
    inputPGMFile = rhs.inputPGMFile;
    rhs.inputPGMFile = "";
    std::move(begin(rhs.compSharedPtr), end(rhs.compSharedPtr), std::inserter(compSharedPtr, end(compSharedPtr)));
}

// Constructor (Move Assignment)
PGMProcessor &PGMProcessor::operator=(PGMProcessor &&rhs) {
    if (this != &rhs) {
        inputPGMFile = rhs.inputPGMFile;
        compSharedPtr = rhs.compSharedPtr;
    }
    return *this;
}

// Destructor
PGMProcessor::~PGMProcessor() {
    for (size_t i = 0; i < compSharedPtr.size(); i++) {
        compSharedPtr[i] = nullptr;
    }
}


// Calls floodfill algorithm
int PGMProcessor::extractComponents(unsigned char threshold, int minValidSize) {
    int startRow = 0;
    int startCol = 0;
    int numComponents = 0;
    inputPGMData = readPGMData();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ( inputPGMData[i][j] < threshold ) {
                ConnectedComponent temp(numComponents);
                floodfill(inputPGMData, threshold, i, j);

                if (temp.getPixelNum() >= minValidSize) {
                    compSharedPtr.push_back(std::make_shared<ConnectedComponent>(temp));
                    numComponents++;
                }
            }
        }
    }

    return numComponents;
}

// Floodfill (BFS) algorithm implentation
void PGMProcessor::floodfill(unsigned char **inputPGMData, unsigned char threshold, int startRow, int startCol) {
    std::vector<std::pair<int,int>> queue;
    int iterateRows[] = {1, -1, 0, 0};
    int iterateCols[] = {0, 0, 1, -1};
    
    

    std::pair<int, int> p(startRow, startCol);
    queue.push_back(p);
    
    inputPGMData[startRow][startCol] = 0; // "Visited = true"

    while ( !queue.empty() ) {
        std::pair<int,int> currentRowCol = queue.front();
        queue.pop_back();
        // inputPGMData[currentRowCol.first][currentRowCol.second] = minIntensity; // Change to 0 since been visited

        for ( int i = 0; i < 4 ; i++ ) {
            if ( isValid(inputPGMData, currentRowCol.first + iterateRows[i], currentRowCol.second + iterateCols[i], threshold) ) {
                inputPGMData[currentRowCol.first + iterateRows[i], currentRowCol.second + iterateCols[i]] = 0;
                // Create/Add to connected component HERE
                std::pair<int, int> p(currentRowCol.first + iterateRows[i], currentRowCol.second + iterateCols[i]);
                queue.push_back(p);
            }
        }
    }
}

// Part of Floodfill Algo implementation
bool PGMProcessor::isValid(unsigned char **inputPGMData, unsigned char threshold, unsigned int row, unsigned int col) {
    if ( (row < 1) || (row > rows) ) { return false; } //Error checking rows (within bounds)
    if ( (col < 1) || (col > cols) ) { return false; } //Error checking cols (within bounds)
    //If the pixel is less than the threshold value, return false
    if ( (inputPGMData[row][col] < threshold) ) {
        return false;
    }

    return true;
}

// Read input PGM data from user's file
unsigned int imgWidth, imgHeight, maxVal = 0;
unsigned char** PGMProcessor::readPGMData() {
    unsigned char** pixels;
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
    return pixels;
}

// bool PGMProcessor::writeComponents(const std::string & outFileName) {

// }

int PGMProcessor::filterComponentsBySize(int minSize, int maxSize){
    compSharedPtr.erase(std::remove_if(compSharedPtr.begin(), compSharedPtr.end(), [minSize,maxSize](std::shared_ptr<ConnectedComponent> ConnCompTemp) -> bool {
        if(ConnCompTemp->getPixelNum()<minSize || ConnCompTemp->getPixelNum()>maxSize) {
        return true;
        }
    } ), compSharedPtr.end());
}

// return number of components
int PGMProcessor::getComponentCount(void) const {
    return compSharedPtr.size();
}

// return number of pixels in largest component
int PGMProcessor::getLargestSize(void) const {
    int largest = 0;

    for (int i = 0; i < compSharedPtr.size(); i++) {
        if (compSharedPtr[i]->getPixelNum() > largest) {
            largest = compSharedPtr[i]->getPixelNum();
        }
    }

    return largest;
}

// return number of pixels in smallest component
int PGMProcessor::getSmallestSize(void) const {
    int smallest = 0;

    for (int i = 0; i < compSharedPtr.size(); i++) {
        if (compSharedPtr[i]->getPixelNum() < smallest) {
            smallest = compSharedPtr[i]->getPixelNum();
        }
    }

    return smallest;
}

/* print the data for a component to std::cout
see ConnectedComponent class;
print out to std::cout: component ID, number of pixels
*/
void PGMProcessor::printComponentData(const ConnectedComponent &comp) const {
    std::cout << comp.getID() << " - Size: " << comp.getPixelNum() << std::endl;
}

/*
    print out all the component data as well as the total
    component number and the sizes of the smallest and largest components
    For "-p" invocation
*/
void PGMProcessor::print() {
    std::cout << "Components:" << std::endl;

    for (int i = 0; i < compSharedPtr.size(); i++) {
        printComponentData(*compSharedPtr[i]);
    }

    std::cout << "Total Components: " << sizeof(compSharedPtr) << std::endl;
    std::cout << "Smallest Component: " << getSmallestSize() << std::endl;
    std::cout << "Largest Component: " << getLargestSize() << std::endl;
}