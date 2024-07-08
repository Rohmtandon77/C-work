/*
1a. Rohm Tandon & Anna Harner
1b. ID: 2397105 and ID: 2397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA2
*/

#include "Warp.h"
#include <iostream>
#include "Elements.h"
using namespace std;

Warp::Warp()
{
}

Warp::~Warp()
{
}

string Warp::interacts(Mario *mario, World *world)
{
    string mario_action = "Mario hit a warp pipe so will go to the next level";
    int mario_level = mario->get_mario_level() + 1;
    mario->set_mario_level(mario_level);
    return mario_action;
}
