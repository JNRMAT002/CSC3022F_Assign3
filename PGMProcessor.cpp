#include "PGMProcessor.h"
#include <vector>

namespace JNRMAT002 {
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

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if ( inputPGMData[i][j] < threshold ) {
                    floodfill(threshold, i, j);
                }
            }
        }

        return numComponents;
    }

    void PGMProcessor::floodfill(unsigned char threshold, int startRow, int startCol) {
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
                if ( isValid(currentRowCol.first + iterateRows[i], currentRowCol.second + iterateCols[i], threshold) ) {
                    inputPGMData[currentRowCol.first + iterateRows[i], currentRowCol.second + iterateCols[i]] = 0;
                    // Create/Add to connected component HERE
                    std::pair<int, int> p(currentRowCol.first + iterateRows[i], currentRowCol.second + iterateCols[i]);
                    queue.push_back(p);
                }
            }
        }
    }

    bool PGMProcessor::isValid(unsigned char threshold, unsigned int row, unsigned int col) {
        if ( (row < 1) || (row > rows) ) { return false; } //Error checking rows (within bounds)
        if ( (col < 1) || (col > cols) ) { return false; } //Error checking cols (within bounds)
        //If the pixel is less than the threshold value, return false
        if ( (inputPGMData[row][col] < threshold) ) {
            return false;
        }

        return true;
    }
}