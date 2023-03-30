#include "PGMProcessor.h"
#include <string>
#include <iostream>

namespace JNRMAT002 {
    PGMProcessor::PGMProcessor(unsigned char **pixels, unsigned int imgWidth, unsigned int imgHeight) {
        inputPGMData = pixels;
        rows = imgHeight;
        cols = imgWidth;
    }
}