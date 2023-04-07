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
    inputFile = inputPGMFile;

}

// Constructor (Copy)
PGMProcessor::PGMProcessor(const PGMProcessor &rhs) {
    inputFile = rhs.inputFile;
    for (int i = 0; i < rhs.compSharedPtr.size(); i++) {
        *(compSharedPtr[i]) = *(rhs.compSharedPtr[i]);
    }
}

// Constructor (Copy Assignment)
PGMProcessor &PGMProcessor::operator=(const PGMProcessor &rhs) {
    this->inputFile = rhs.inputFile;
    for (int i = 0; i < rhs.compSharedPtr.size(); i++) {
        *compSharedPtr[i] = *(rhs.compSharedPtr[i]);
    }
    return *this;
}

// Constructor (Move)
PGMProcessor::PGMProcessor(PGMProcessor &&rhs) {
    inputFile = rhs.inputFile;
    rhs.inputFile = "";
    std::move(begin(rhs.compSharedPtr), end(rhs.compSharedPtr), std::inserter(compSharedPtr, end(compSharedPtr)));
}

// Constructor (Move Assignment)
PGMProcessor &PGMProcessor::operator=(PGMProcessor &&rhs) {
    if (this != &rhs) {
        inputFile = rhs.inputFile;
        compSharedPtr = rhs.compSharedPtr;
    }
    return *this;
}

// Destructor
PGMProcessor::~PGMProcessor() {
    for (int i = 0; i < compSharedPtr.size(); i++) {
        compSharedPtr[i] = nullptr;
    }
}


// Calls floodfill algorithm
int PGMProcessor::extractComponents(unsigned char threshold, int minValidSize) {
    int numComponents = 0;
    unsigned char **inputPGMData = readPGMData();
    // int idCount = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if ( isValid(inputPGMData, threshold, i, j) ) {
                // std::shared_ptr<ConnectedComponent> newComp = std::make_shared<ConnectedComponent>(idCount);
                ConnectedComponent newComp(numComponents);
                // idCount++;

                floodfill(inputPGMData, newComp, threshold, i, j);

                if (newComp.getPixelNum() >= minValidSize) {
                                        std::cout << "test" << std::endl;

                    compSharedPtr.push_back(std::make_shared<ConnectedComponent>(std::move(newComp)));
                        std::cout << "test2" << std::endl;

                    numComponents++;
                    // std::cout << numComponents <<std::endl;
                }
            }
        }
    }
    // std::cout << numComponents <<std::endl;
    return numComponents;
}

// Floodfill (BFS) algorithm implentation
void PGMProcessor::floodfill(unsigned char **inputPGMData, ConnectedComponent &comp, unsigned char threshold, int startRow, int startCol) {
    std::vector<std::pair<int,int>> queue;
    int iterateRows[] = {1, -1, 0, 0};
    int iterateCols[] = {0, 0, 1, -1};
    std::pair<int, int> p(startRow, startCol);
    queue.push_back(p);
    inputPGMData[startRow][startCol] = 0; // "Visited = true"

    while ( !queue.empty() ) {
        std::pair<int,int> currentRowCol = queue.front();
        comp.addPixel(currentRowCol);
        queue.pop_back();

        for ( int i = 0; i < 4 ; i++ ) {
            if ( isValid(inputPGMData, threshold, currentRowCol.first + iterateRows[i], currentRowCol.second + iterateCols[i]) ) {
                // std::cout << currentRowCol.first << std::endl;
                std::pair<int, int> p(currentRowCol.first + iterateRows[i], currentRowCol.second + iterateCols[i]);
                queue.push_back(p);
                inputPGMData[currentRowCol.first + iterateRows[i]][currentRowCol.second + iterateCols[i]] = 0;
                // std::cout << "test" <<std::endl;
            }
                // std::cout << sizeof(queue) <<std::endl;

        }
    }
}

// Part of Floodfill Algo implementation
bool PGMProcessor::isValid(unsigned char **inputPGMData, unsigned char threshold, unsigned int row, unsigned int col) {
    // std::cout << cols << std::endl;
    if ( (row < 0) || (row > rows) ) { return false; } //Error checking rows (within bounds)
    if ( (col < 0) || (col > cols) ) { return false; } //Error checking cols (within bounds)
    //If the pixel is less than the threshold value, return false
    if ( (inputPGMData[row][col] < threshold) ) { return false; }

    return true;
}

// Read input PGM data from user's file
unsigned char** PGMProcessor::readPGMData() {
    unsigned char** pixels;
    std::ifstream file(inputFile, std::ios::binary);

    // std::cout << inputFile << std::endl;
    if (!file.is_open()) {
        std::cerr << "Error: could not open PGM file" << std::endl;
        
    }

    std::string line;

    // Read/Discard header
    std::getline(file, line);
    int line_count;

    while (std::getline(file, line)) {
        if (line[0] == '#') { continue; }
        else { 
            line_count = 1;
            std::istringstream ss (line);
            ss >> cols >> std::ws >> rows;
            // std::cout << imgWidth << " " << imgHeight << std::endl;
            break; 
        }
    }

    while (std::getline(file, line)) {

        if (line_count == 1) {
            // Get pgm image maxVal
            std::istringstream ss(line);                
            ss >> maxVal;
            line_count += 1;
            // std::cout << maxVal << std::endl;
        }

        if (line_count == 2) {
            // Store pixel data in array | imgHeight = numRows, imgWidth = numCols
            pixels = new unsigned char*[rows];
            for (int i = 0; i < rows; i++) {
                pixels[i] = new unsigned char[cols];

                for (int j = 0; j < cols; j++) {
                    file >> pixels[i][j];
                }
            }
            // std::cout << "TEST" << std::endl;
        }            
        
    }

    file.close();
    return pixels;
}

// bool PGMProcessor::writeComponents(const std::string & outFileName) {

// }

int PGMProcessor::filterComponentsBySize(int minSize, int maxSize){
    // Iterate through the vector

    // std::cout << "test" << std::endl;

    if (maxSize = 0){
        maxSize = rows*cols;
    }

    for (auto iter = compSharedPtr.begin(); iter != compSharedPtr.end(); ) {
        // If the number of pixels is less than minSize or greater than maxSize, remove the element
        if ((*iter)->getPixelNum() < minSize || (*iter)->getPixelNum() > maxSize) {
            iter = compSharedPtr.erase(iter); // Erase the current element and update the iterator
        } else {
            ++iter; // Move to the next element
        }
    }

    return compSharedPtr.size();
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
    std::cout << comp.getID() << " - " << comp.getPixelNum() << " pixels" << std::endl;
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

    std::cout << "Total Components: " << compSharedPtr.size() << std::endl;
    std::cout << "Smallest Component: " << getSmallestSize() << std::endl;
    std::cout << "Largest Component: " << getLargestSize() << std::endl;
}