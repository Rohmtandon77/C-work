/*
1a. Rohm Tandon & Anna Harner
1b. ID: 2397105 and ID: 2397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA2
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include "Mario.h"
#include "World.h"
using namespace std;

// deafault constructor - initially sets everything to 0
Mario::Mario()
{
    m_lives = 0;
    m_power_level = 0;
    m_num_coins = 0;
    m_enemy_count = 0;
    m_mario_level = 0;
    m_mario_row = 0;
    m_mario_col = 0;
    m_mario_status = true;
}

// default destructor
Mario::~Mario()
{
}

// accessor and mutator for amount of lives
int Mario::get_lives()
{
    return m_lives;
}

void Mario::set_lives(int lives)
{
    m_lives = lives;
}

// accessor and mutator for Mario's power level
int Mario::get_power_level()
{
    return m_power_level;
}

void Mario::set_power_level(int power_level)
{
    m_power_level = power_level;
}

// accessor and mutator for the amount of coins Mario has
int Mario::get_num_coins()
{
    return m_num_coins;
}

void Mario::set_num_coins(int num_coins)
{
    m_num_coins = num_coins;
}

// accessor and mutator for enemy count
int Mario::get_enemy_count()
{
    return m_enemy_count;
}

void Mario::set_enemy_count(int enemy_count)
{
    m_enemy_count = enemy_count;
}

// accessor and mutator for Mario's level
int Mario::get_mario_level()
{
    return m_mario_level;
}

void Mario::set_mario_level(int mario_level)
{
    m_mario_level = mario_level;
}

// accessor and mutator for the column Mario is in
int Mario::get_mario_col()
{
    return m_mario_col;
}

void Mario::set_mario_col(int mario_col)
{
    m_mario_col = mario_col;
}

// accessor and mutator for the row Mario is in
int Mario::get_mario_row()
{
    return m_mario_row;
}

void Mario::set_mario_row(int mario_row)
{
    m_mario_row = mario_row;
}

// returns whether mario is still alive
bool Mario::is_alive()
{
    return m_mario_status;
}

// If he lost the game
void Mario::set_death()
{
    m_mario_status = false;
}

// Method if mario has 20 coins so he gets another life
string Mario::extra_life()
{
    string mario_action = "";
    if (m_num_coins == 20)
    {
        m_num_coins = 0;
        m_lives++;
        mario_action += "Mario has 20 coins and gets another life";
        mario_action += m_lives;
    }
    if (m_enemy_count == 7)
    {
        m_lives++;
        mario_action += "Mario defeated 7 enemies on the same life so gets another life";
        m_enemy_count = 0;
    }
    else
    {
        mario_action += "\n";
    }
    return mario_action;
}

// check where mario is going to go and assign number 1,2,3
// check where mario is going to go and assign number 1,2,3
string Mario::movement(World *m_world, char mark_as)
{
    string mario_direction = "Mario will go ";
    int direction = -1;
    direction = rand() % 4;
    if (direction == 0)
    {
        if (m_mario_row == 0)
        {
            mario_direction = "Up";
            m_world->set_item(mark_as, m_mario_level, m_mario_row, m_mario_col);
            set_mario_row(m_world->get_size() - 1);
        }
        else
        {
            mario_direction = "Up";
            m_world->set_item(mark_as, m_mario_level, m_mario_row, m_mario_col);
            set_mario_row(get_mario_row() - 1);
        }
    }
    else if (direction == 1)
    {
        if (m_mario_row == (m_world->get_size() - 1))
        {
            mario_direction = "Down";
            m_world->set_item(mark_as, m_mario_level, m_mario_row, m_mario_col);
            set_mario_row(0);
        }
        else
        {
            mario_direction = "Down";
            m_world->set_item(mark_as, m_mario_level, m_mario_row, m_mario_col);
            set_mario_row(get_mario_row() + 1);
        }
    }
    else if (direction == 2)
    {
        if (m_mario_col == 0)
        {
            mario_direction = "Left";
            m_world->set_item(mark_as, m_mario_level, m_mario_row, m_mario_col);
            set_mario_col(m_world->get_size() - 1);
        }
        else
        {
            mario_direction = "Left";
            m_world->set_item(mark_as, m_mario_level, m_mario_row, m_mario_col);
            set_mario_col(get_mario_col() - 1);
        }
    }
    else if (direction == 3)
    {
        if (m_mario_col == (m_world->get_size() - 1))
        {
            mario_direction = "Right";
            m_world->set_item(mark_as, m_mario_level, m_mario_row, m_mario_col);
            set_mario_col(0);
        }
        else
        {
            mario_direction = "Right";
            m_world->set_item(mark_as, m_mario_level, m_mario_row, m_mario_col);
            set_mario_col(get_mario_col() + 1);
        }
    }
    return mario_direction;
}
