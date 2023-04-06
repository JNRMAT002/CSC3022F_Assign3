#include "PGMProcessor.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <iostream>

namespace JNRMAT002 {
    PGMProcessor::PGMProcessor(std::string inputPGMFile) {
        inputPGMFile = inputPGMFile;
    }

    // Constructor
    PGMProcessor::PGMProcessor(unsigned char **pixels, unsigned int imgWidth, unsigned int imgHeight) {
        inputPGMData = pixels;
        rows = imgHeight;
        cols = imgWidth;
        numComponents = 0;

    }

    // Implements floodfill algorithm
    int PGMProcessor::extractComponents(unsigned char threshold, int minValidSize) {
        int startRow = 0;
        int startCol = 0;
        int numComponents = 0;
        inputPGMData = readPGMData();

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if ( inputPGMData[i][j] < threshold ) {
                    // JNRMAT002::ConnectedComponent temp(numComponents);
                    floodfill(inputPGMData, threshold, i, j);

                    // if (temp.getPixelNum() >= minValidSize)
                    // {
                    //     numComponents.push_back(std::make_shared<JNRMAT002::ConnectedComponent>(temp));
                    //     numComponents++;
                    // }
                }
            }
        }

        return numComponents;
    }

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

    bool PGMProcessor::isValid(unsigned char **inputPGMData, unsigned char threshold, unsigned int row, unsigned int col) {
        if ( (row < 1) || (row > rows) ) { return false; } //Error checking rows (within bounds)
        if ( (col < 1) || (col > cols) ) { return false; } //Error checking cols (within bounds)
        //If the pixel is less than the threshold value, return false
        if ( (inputPGMData[row][col] < threshold) ) {
            return false;
        }

        return true;
    }

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
}