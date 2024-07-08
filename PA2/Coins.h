/*
1a. Rohm Tandon & Anna Harner
1b. ID: 2397105 and ID: 2397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA2
*/

#ifndef COINS_H
#define COINS_H
#include <iostream>
#include "Mario.h"
#include "Elements.h"
using namespace std;

class Coins {
public:
    Coins();
    virtual ~Coins();
    string interacts(Mario* mario);
};
#endif
