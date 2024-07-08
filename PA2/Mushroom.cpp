/*
1a. Rohm Tandon & Anna Harner
1b. ID: 2397105 and ID: 2397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA2
*/

#include <iostream>
#include "Mushroom.h"
#include <string>
#include "Mario.h"

// default constructor
Mushroom::Mushroom()
{
}

// default destructor
Mushroom::~Mushroom()
{
}

// method to make mario level up if he encounters a mushroom
string Mushroom::interacts(Mario *mario)
{
    int power = mario->get_power_level();
    if (power < 3)
    {
        power++;
    }
    mario->set_power_level(power);
    string mario_action = "Mario got a mushroom so gained power. ";
    return mario_action;
}
