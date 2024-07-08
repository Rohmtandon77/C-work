/*
1a. Rohm Tandon & Anna Harner
1b. ID: 2397105 and ID: 2397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA2
*/

#ifndef GOOMBA_H
#define GOOMBA_H
#include <iostream>
#include "Elements.h"
using namespace std;

class Goomba {
public:
    Goomba();
    virtual ~Goomba();
    bool get_result();
    void set_result(bool result);
    // determines what happens when Mario interacts with the object
    string interacts(Mario* mario);
private:
    bool m_win;
};

#endif
