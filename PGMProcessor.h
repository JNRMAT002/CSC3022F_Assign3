/*
    Matthew January JNRMAT002
    Header file for image processing assignment (Assignment 3)
    PGMProcessor Class definition
*/

#ifndef PGM_HDR
#define PGM_HDR

#include <string>
#include <memory>
#include "ConnectedComponent.h"

namespace JNRMAT002 {
    class PGMProcessor {
    public:
    // Constructor (Default)
    PGMProcessor(std::string inputPGMFile);

    // Constructor (Copy)
    PGMProcessor(const PGMProcessor &rhs);

    // Constructor (Copy Assignment)
    PGMProcessor &operator=(const PGMProcessor &rhs);

    // Constructor (Move)
    PGMProcessor(PGMProcessor &&rhs);

    // Constructor (Move Assignment)
    PGMProcessor &operator=(PGMProcessor &&rhs);

    // Destructor
    ~PGMProcessor();

    /* process the input image to extract all the connected components,
    based on the supplied threshold (0...255) and excluding any components
    of less than the minValidSize. The final number of components that
    you store in your container (after discarding undersized one)
    must be returned.
    */
    int extractComponents(unsigned char threshold, int minValidSize);

    /* iterate - with an iterator - though your container of connected
    components and filter out (remove) all the components which do not
    obey the size criteria pass as arguments. The number remaining
    after this operation should be returned.
    */
    int filterComponentsBySize(int minSize, int maxSize);

    /* create a new PGM file which contains all current components
    (255=component pixel, 0 otherwise) and write this to outFileName as a
    valid PGM. the return value indicates success of operation
    */
    bool writeComponents(const std::string & outFileName);

    // return number of components
    int getComponentCount(void) const;

    // return number of pixels in largest component
    int getLargestSize(void) const;

    // return number of pixels in smallest component
    int getSmallestSize(void) const;

    /* print the data for a component to std::cout
    see ConnectedComponent class;
    print out to std::cout: component ID, number of pixels
    */
    void printComponentData(const ConnectedComponent & theComponent) const;
    
/*
    print out all the component data as well as the total
    component number and the sizes of the smallest and largest components
*/
    void print();

    // Executes floodfill algo
    void floodfill(unsigned char **inputPGMData, ConnectedComponent &comp, unsigned char threshold, int startRow, int startCol);

    // Checks if a pixel exceeds the threshold value
    bool isValid (unsigned char **inputPGMData, unsigned char threshold, unsigned int row, unsigned int col);

    // Reads PGM Image Data
    unsigned char** readPGMData();

    private:
    std::string inputFile;
    std::vector<std::shared_ptr<ConnectedComponent>> compSharedPtr;
    // unsigned int rows, cols;
    int numComponents; //Final number of components stored in container | return value for extractComponents()
    const unsigned char maxIntensity = 255;
    const unsigned char minIntensity = 0;
    unsigned int cols, rows, maxVal = 0;

    };
}

#endif