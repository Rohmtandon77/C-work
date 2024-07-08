/*
1a. Rohm Tandon & Anna Harner
1b. ID: 2397105 and ID: 2397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA2
*/

#ifndef MARIO_H
#define MARIO_H
#include <iostream>
#include <string>
#include "World.h"
using namespace std;

class Mario
{
public:
    Mario();
    virtual ~Mario();
    int get_lives();
    void set_lives(int lives);
    int get_power_level();
    void set_power_level(int power_level);
    int get_num_coins();
    void set_num_coins(int num_coins);
    int get_enemy_count();
    void set_enemy_count(int enemy_count);
    int get_mario_level();
    void set_mario_level(int mario_level);
    int get_mario_col();
    void set_mario_col(int mario_col);
    int get_mario_row();
    void set_mario_row(int mario_row);
    bool is_alive();
    void set_death();

    string extra_life();
    string movement(World *mario_world, char mark_as);

private:
    int m_power_level;
    int m_enemy_count;
    int m_num_coins;
    bool m_mario_status;
    int m_mario_col;
    int m_mario_row;
    int m_mario_level;
    int m_lives;
};
#endif
