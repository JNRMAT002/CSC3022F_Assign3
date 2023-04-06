#include "ConnectedComponent.h"

using namespace JNRMAT002;
// Constructor
ConnectedComponent::ConnectedComponent(int ID)
{
    compID = ID;
    numPixels = 0;
}

//Returns ID
int ConnectedComponent::getID() const
{
    return compID;
}

//Returns amount of pixels
int ConnectedComponent::getPixelNum() const
{
    return numPixels;
}

//Returns vector or coordinates of pixels
std::vector<std::pair<int, int>> ConnectedComponent::getPixels() const
{
    return compPairs;
}

//Adds a pixel by coordinate to the vector
void ConnectedComponent::addPixel(std::pair<int, int> newPixel)
{
    compPairs.push_back(newPixel);
    numPixels++;
}
