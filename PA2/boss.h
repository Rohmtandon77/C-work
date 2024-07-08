/*
1a. Rohm Tandon & Anna Harner
1b. ID: 2397105 and ID: 2397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA2
*/

#ifndef BOSS_H
#define BOSS_H
#include <iostream>
#include "Elements.h"
#include "Mario.h"
using namespace std;

class Boss {
public:
    Boss();
    virtual ~Boss();
    bool get_result();
    void set_result(bool result);
    // determines what happens when Mario interacts with the object
    string interacts(Mario* mario);
private:
    bool m_win;
};

#endif
