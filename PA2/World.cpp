/*
1a. Rohm Tandon & Anna Harner
1b. ID: 2397105 and ID: 2397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA2
*/

#include <iostream>
#include "World.h"
#include <string>
#include <cstdlib>
using namespace std;

// default constructor
World::World()
{
}

// default destructor
World::~World()
{
    for (int i = 0; i < m_L; i++)
    {
        for (int j = 0; j < m_N; j++)
        {
            // delete[] m_world[i][j];
        }
        delete[] m_world[i];
    }
    delete[] m_world;
}

// getter for getting the number of levels
int World::get_levels()
{
    return m_L;
}

// setter for setting the number of levels
void World::set_levels(int level)
{
    m_L = level;
}

// getter for the size of our world
int World::get_size()
{
    return m_N;
}

// setter for setting the size
void World::set_size(int size)
{
    m_N = size;
}

// setter for coins
void World::set_coins(int coins)
{
    m_coins = coins;
}

// setter for mushrooms
void World::set_mushrooms(int mushrooms)
{
    m_mushrooms = mushrooms;
}

// setter for empty plots
void World::set_nothing(int nothing)
{
    m_nothing = nothing;
}

// setter for goombas
void World::set_goombas(int goombas)
{
    m_goombas = goombas;
}

// setter for koopas
void World::set_koopas(int koopas)
{
    m_koopas = koopas;
}

// getter for the item to place
char World::get_item(int level, int row, int col)
{
    char temp = '!';
    temp = m_world[level][row][col];
    return temp;
}

// setter for the item to place
void World::set_item(char item, int level, int row, int col)
{
    m_world[level][row][col] = item;
}

void World::initialize_world()
{
    m_world = new char **[m_L]; // This initalizes m_L levels
    for (int i = 0; i < m_L; i++)
    {
        m_world[i] = new char *[m_N]; // Will determine how many rows we want
        for (int j = 0; j < m_N; j++)
        {
            m_world[i][j] = new char[m_N];
            // m_world[i][j] = new char;
        }
    }
    for (int i = 0; i < m_L; i++)
    {
        for (int j = 0; j < m_N; j++)
        {
            for (int k = 0; k < m_N; k++)
            {
                m_world[i][j][k] = 'x';
            }
        }
    }
}

char **World::generate_level(int i)
{
    // temporary/location variables
    int boss_row = -1;
    int boss_col = -1;
    int warp_row = -1;
    int warp_col = -1;
    // holds the randomly generated number
    int rand_int = -1;
    if (i != (m_L - 1))
    {
        boss_col = rand() % m_N;
        boss_row = rand() % m_N;
        warp_col = rand() % m_N;
        warp_row = rand() % m_N;
        while (boss_row == warp_row && warp_col == boss_col)
        { // if the location for boss and warp are the same
            int rand_chance = -1;
            rand_chance = rand() % 100;
            if (rand_chance < 50)
            {
                boss_col = rand() % m_N;
                boss_row = rand() % m_N;
            }
            else
            {
                warp_col = rand() % m_N;
                warp_row = rand() % m_N;
            }
        }
    }
    else
    { // for the final level
        boss_col = rand() % m_N;
        boss_row = rand() % m_N;
    }
    for (int k = 0; k < m_N; k++)
    {
        for (int j = 0; j < m_N; j++)
        {
            if (k == boss_col && j == boss_row)
            {
                m_world[i][k][j] = 'b';
                continue;
            }
            if (i != (m_L - 1))
            {
                if (k == warp_col && j == warp_row)
                {
                    m_world[i][k][j] = 'w';
                    continue;
                }
            }
            rand_int = rand() % 100;
            int mushrooms = m_mushrooms + m_nothing;
            int coins = mushrooms + m_coins;
            int goombas = coins + m_goombas;
            if (rand_int < m_nothing)
            {
                m_world[i][k][j] = 'x';
                continue;
            }
            else if (m_nothing < rand_int && rand_int < mushrooms)
            {
                m_world[i][k][j] = 'm';
                continue;
            }
            else if (mushrooms < rand_int && rand_int < coins)
            {
                m_world[i][k][j] = 'c';
                continue;
            }
            else if (coins < rand_int && rand_int < goombas)
            {
                m_world[i][k][j] = 'g';
                continue;
            }
            else
            {
                m_world[i][k][j] = 'k';
                continue;
            }
        }
    }
    return m_world[i];
}

void World::set_world()
{
    for (int i = 0; i < m_L; i++)
    {
        m_world[i] = generate_level(i);
    }
}
