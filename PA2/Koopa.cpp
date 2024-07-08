/*
1a. Rohm Tandon & Anna Harner
1b. ID: 2397105 and ID: 2397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA2
*/

#include "Mario.h"
#include "Elements.h"
#include "Warp.h"
#include "Koopa.h"
#include <cstdlib>

// default constructor for Koopa
Koopa::Koopa()
{
    m_win = false;
}

// default destructor for Koopa
Koopa::~Koopa()
{
}

bool Koopa::get_result()
{
    return m_win;
}
// tells us whether mario won or not
void Koopa::set_result(bool result)
{
    m_win = result;
}

// has mario interact with the object/Koopa
string Koopa::interacts(Mario *mario)
{
    string mario_action = "";
    int rand_chance = -1;
    rand_chance = rand() % 100;
    // checks if the random chance is below 65 and Mario wins
    if (rand_chance < 65)
    {
        int enemy_count = mario->get_enemy_count();
        mario->set_enemy_count(enemy_count++);
        mario_action = "Mario won against the Koopa";
        mario_action += mario->extra_life();
        m_win = true;
    }
    // if the random chance is above 65 Mario loses a life
    else
    {
        mario->set_enemy_count(0);
        mario_action = "Mario loses to the Koopa. ";
        if (mario->get_power_level() > 0)
        {
            int power_level = mario->get_power_level() - 1;
            mario->set_power_level(power_level);
            m_win = false;
        }
        else if (mario->get_lives() > 0)
        {
            int life_count = mario->get_lives() - 1;
            mario->set_lives(life_count);
            m_win = false;
        }
        else
        {
            m_win = false;
            mario->set_death();
        }
    }
    return mario_action;
}
