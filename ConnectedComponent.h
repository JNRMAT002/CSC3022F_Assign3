/*
    Matthew January JNRMAT002
    Header file for image processing assignment (Assignment 3)
    ConnectedComponent Class definition
*/

#ifndef CONN_COMP_HDR
#define CONN_COMP_HDR

#include <vector>

namespace JNRMAT002 {
    class ConnectedComponent {
        public:
        ConnectedComponent(int compID);

        int getID() const;

        int getPixelNum() const;

        std::vector<std::pair<int,int>> getPixels() const;

        void addPixel(std::pair<int,int> newPixel);

        private:
            int numPixels;
            int compID;
            std::vector< std::pair<int, int> > compPairs;
    };
}

#endif