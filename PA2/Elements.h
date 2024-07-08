/*
1a. Rohm Tandon & Anna Harner
1b. ID: 2397105 and ID: 2397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA2
*/

#ifndef ELEMENTS_H
#define ELEMENTS_H
#include <iostream>
#include "Mario.h"

class Elements {
    public:
        Elements();
        virtual ~Elements();
        string interacts(Mario* mario);
};
#endif
