/*
1a. Rohm Tandon & Anna Harner
1b. ID: 2397105 and ID: 2397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA2
*/

#ifndef WARP_H
#define WARP_H
#include <iostream>
#include "Elements.h"
using namespace std;

class Warp {
public:
    Warp();
    virtual ~Warp();
    // determines what happens when Mario interacts with the object
    string interacts(Mario* mario, World* world);
};

#endif
