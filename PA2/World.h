/*
1a. Rohm Tandon & Anna Harner
1b. ID: 2397105 and ID: 2397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA2
*/

#ifndef WORLD_H
#define WORLD_H
#include <iostream>
#include <string>
using namespace std;

class World
{
public:
    World();
    ~World();
    int get_levels();
    void set_levels(int level);
    int get_size();
    void set_size(int size);
    void set_coins(int coins);
    void set_mushrooms(int mushrooms);
    void set_nothing(int nothing);
    void set_goombas(int goombas);
    void set_koopas(int koopas);
    char get_item(int level, int row, int col);
    void set_item(char item, int level, int row, int col);
    void initialize_world(); // initializes a 3d array
    char **generate_level(int i);
    void set_world();
    void print_world();

private:
    int m_L; // Number of levels
    int m_N; // Number of rows and columns
    char ***m_world;
    int m_coins;
    int m_nothing;
    int m_mushrooms;
    int m_goombas;
    int m_koopas;
};

#endif
