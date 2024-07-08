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
#include "boss.h"
#include <cstdlib>

// default constructor for Koopa
Boss::Boss() {
    m_win = false;
}

// default destructor for Koopa
Boss::~Boss(){
}

bool Boss::get_result() {
    return m_win;
}

// tells us whether mario won or not
void Boss::set_result(bool result){
    m_win = result;
}

// Mario's interaction with the boss
string Boss::interacts(Mario* mario){
    string mario_action = "Mario fought the boss and ";
    int rand_chance = -1;
    rand_chance = rand() % 100;
    // 50% chance mario wins the fight with the boss
    if(rand_chance < 50) {
        int enemy_count = mario->get_enemy_count();
        mario->set_enemy_count(enemy_count++); // his enemy count goes up
        mario_action += "won! ";
        mario_action += mario->extra_life(); // he gets an extra life
        mario->set_mario_level(mario->get_mario_level() + 1);
        m_win = true;
    }
    // if mario loses against the boss
    else {
        mario->set_enemy_count(0);
        if(mario->get_power_level() ==2) {
            mario->set_power_level(0);
            int life_count = mario->get_lives();
            mario->set_lives(life_count--);
        }
        else if(mario->get_lives() != 0) {
            mario->set_power_level(0);
            int life_count = mario->get_lives() - 1;
            mario->set_lives(life_count);
        }
        mario_action += "lost! ";
        if(mario->get_lives() != 0) {
            mario_action += "Will try again.\n";
        }
        else {
            mario_action = "Mario failed fighting the boss.";
            m_win = false;
        }
    }
    return mario_action;
}
