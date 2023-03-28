/*
    Matthew January JNRMAT002
    Header file for image processing assignment (Assignment 3)
    ConnectedComponent Class definition
*/

#include <vector>

#ifndef CONN_COMP_HDR
#define CONN_COMP_HDR

namespace JNRMAT002 {
    class ConnectedComponent {
        public:

        private:
            int numPixels;
            int compID;
            std::vector< std::pair<int, int> > compPairs;
    };
}

#endif CONN_COMP_HDR