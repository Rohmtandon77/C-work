/*
1a. Rohm Tandon & Anna Harner
1b. ID: 2397105 and ID: 2397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA2
*/

#include <iostream>
#include "Coins.h"
#include "Elements.h"
#include "Mario.h"
using namespace std;

// default constructor
Coins::Coins(){
}

// default destructor
Coins::~Coins(){
}

// Every time he runs into a coin
string Coins::interacts(Mario* mario) {
    string mario_action = "Mario collect a coin. \n";
    int Coins = mario->get_num_coins() + 1;
    mario->set_num_coins(Coins);
    string Coins1 = to_string(Coins); // puts coins to string so we can add it to mario's action
    // mario_action +=  "Mario has " + Coins1;
    mario->extra_life();
    return mario_action; // return marios action this round
}
