/*
1a. Rohm Tandon & Anna Harner
1b. ID: 2397105 and ID: 2397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA2
*/

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <string>
#include "Mario.h"
#include "World.h"
#include "boss.h"
#include "Coins.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Mushroom.h"
#include "Warp.h"
using namespace std;

class Game
{
public:
    Game();
    virtual ~Game();
    void read_file(string input_file);
    string print_level(int mario_level);                     // print Mario's current level
    string print_movement(string mario_direction);           // print where mario will go
    string print_turns(string mario_action, int level);      // print what happened during turn
    void game_method(string input_file, string output_file); // runs the game simulation
private:
    World *game_world;
    Mario *game_mario;
    Boss *game_boss;
    Coins *game_coins;
    Goomba *game_goomba;
    Koopa *game_koopa;
    Mushroom *game_mushroom;
    Warp *game_warp;
};

#endif
