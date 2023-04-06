#include "ConnectedComponent.h"

using namespace JNRMAT002;
// Constructor (Default)
ConnectedComponent::ConnectedComponent(int ID) {
    compID = ID;
    numPixels = 0;
}

// Constructor (Copy)
ConnectedComponent::ConnectedComponent(const ConnectedComponent &rhs) {
    numPixels = rhs.numPixels;
    compID = rhs.compID;
    for (int i = 0; i < rhs.numPixels; i++) {
        compPairs[i] = rhs.compPairs[i];
    }
}

// Constructor (Copy Assignment)
ConnectedComponent &ConnectedComponent::operator=(const ConnectedComponent &rhs) {
    this->compID = rhs.compID;
    this->numPixels = rhs.numPixels;
    for (int i = 0; i < rhs.numPixels; i++) {
        this->compPairs[i] = rhs.compPairs[i];
    }
    return *this;
}

// Constructor (Move)
ConnectedComponent::ConnectedComponent(ConnectedComponent &&rhs) : numPixels{rhs.numPixels},compID{rhs.compID} {
    for (int i = 0; i < rhs.numPixels; i++) {
        compPairs[i] = rhs.compPairs[i];
    }
}

// Constructor (Move Assignment)
ConnectedComponent &ConnectedComponent::operator=(ConnectedComponent &&rhs) {
    if (this != &rhs) {
        compPairs = rhs.compPairs;
        compID = rhs.compID;
        numPixels = rhs.numPixels;
    }
    return *this;
}

// Destructor
ConnectedComponent::~ConnectedComponent() {
    numPixels = 0;
    compID = -1;
}

//Returns ID
int ConnectedComponent::getID() const {
    return compID;
}

//Returns amount of pixels
int ConnectedComponent::getPixelNum() const {
    return numPixels;
}

//Returns vector or coordinates of pixels
std::vector<std::pair<int, int>> ConnectedComponent::getPixels() const {
    return compPairs;
}

//Adds a pixel by coordinate to the vector
void ConnectedComponent::addPixel(std::pair<int, int> newPair) {
    compPairs.push_back(newPair);
    numPixels++;
}
