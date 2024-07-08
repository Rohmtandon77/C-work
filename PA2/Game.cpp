/*
1a. Rohm Tandon & Anna Harner
1b. ID: 2397105 and ID: 2397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA2
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Mario.h"
#include "World.h"
#include "boss.h"
#include "Coins.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Mushroom.h"
#include "Warp.h"
#include "Game.h"
using namespace std;

Game::Game()
{
    game_world = new World();
    game_mario = new Mario();
    game_boss = new Boss();
    game_coins = new Coins();
    game_goomba = new Goomba();
    game_koopa = new Koopa();
    game_mushroom = new Mushroom();
    game_warp = new Warp();
}

Game::~Game()
{
    delete game_world;
    delete game_mario;
    delete game_boss;
    delete game_coins;
    delete game_goomba;
    delete game_koopa;
    delete game_mushroom;
    delete game_warp;
}

void Game::read_file(string input_file)
{
    ifstream file;
    file.open(input_file);
    if (file.is_open())
    {
        string text;
        int counter = 1;
        int line_value = -1;
        while (getline(file, text))
        {
            line_value = stoi(text);
            if (counter == 1)
            {
                game_world->set_levels(line_value);
            }
            else if (counter == 2)
            {
                game_world->set_size(line_value);
            }
            else if (counter == 3)
            {
                game_mario->set_lives(line_value);
            }
            else if (counter == 4)
            {
                game_world->set_coins(line_value);
            }
            else if (counter == 5)
            {
                game_world->set_nothing(line_value);
            }
            else if (counter == 6)
            {
                game_world->set_goombas(line_value);
            }
            else if (counter == 7)
            {
                game_world->set_koopas(line_value);
            }
            else if (counter == 8)
            {
                game_world->set_mushrooms(line_value);
            }
            counter++;
        }
    }
    file.close();
}

// print Mario's current level
string Game::print_level(int mario_level)
{
    string level = "";
    for (int i = 0; i < game_world->get_size(); i++)
    {
        for (int j = 0; j < game_world->get_size(); j++)
        {
            char current_item = game_world->get_item(mario_level, i, j);
            string s(1, current_item);
            level += s;
            level += " ";
        }
        level += "\n";
    }
    level += "\n";
    return level;
}

// print where mario will go
string Game::print_movement(string mario_direction)
{
    string mario_turn = "mario will move ";
    mario_turn += mario_direction;
    mario_turn += ".\n";
    return mario_turn;
}

// print what happened during turn
string Game::print_turns(string mario_action, int level)
{
    string output_text = "";
    // Print Mario's level
    output_text += "Level: ";
    output_text += to_string(level) + ". ";
    // Print Mario's location
    output_text += "Current Position: (";
    int mario_row = game_mario->get_mario_row();
    output_text += to_string(mario_row) + ", ";
    int mario_col = game_mario->get_mario_col();
    output_text += to_string(mario_col) + "). ";
    // Print mario's power level
    output_text += "Power level: ";
    char power_level = game_mario->get_power_level();
    output_text += to_string(power_level) + ". ";
    // Print mario's action
    output_text += mario_action;
    // Print mario's lives
    output_text += "Lives left: ";
    char lives = game_mario->get_lives();
    output_text += to_string(lives) + ". ";
    // Print's number of coins
    output_text += "Number of coins: ";
    char num_coins = game_mario->get_num_coins();
    output_text += to_string(num_coins) + ".\n";
    return output_text;
}

// runs the game simulation
void Game::game_method(string input_file, string output_file)
{
    read_file(input_file);  // first read input file
    ofstream exit;          // this is where our output text goes
    exit.open(output_file); // open the output file
    // set the world up
    if (exit.is_open())
    {
        game_world->initialize_world();
        game_world->set_world();
        string round1 = "";
        int current_round = 0;
        int current_level = -1;
        string mario_direction = "";
        string mario_action = "";
        int mario_row = -1;
        int mario_col = -1;
        // go through the levels
        for (int i = 0; i < game_world->get_levels(); i++)
        {
            current_level = i;
            mario_row = rand() % game_world->get_size();
            mario_col = rand() % game_world->get_size();
            // make world without mario
            game_mario->set_mario_row(mario_row);
            game_mario->set_mario_col(mario_col);
            exit << "\n";
            exit << "Level: " << i << " Before Mario's placement" << endl;
            exit << print_level(i);
            // place mario in world
            char current_item = game_world->get_item(i, mario_row, mario_col);
            game_world->set_item('H', i, game_mario->get_mario_row(), game_mario->get_mario_col());
            exit << "Level: " << i << " After Mario's placement" << endl;
            exit << print_level(i);
            exit << flush;
            // while loop around the level and if they get to final level end
            while (game_mario->get_mario_level() == current_level)
            {
                // action if there is nothing in the spot
                char mark_as = 'x';
                if (current_item == 'x')
                {
                    exit << print_turns("The position is empty. \n", current_level);
                }
                // action if there's a mushroom
                else if (current_item == 'm')
                {
                    mario_action = game_mushroom->interacts(game_mario);
                    exit << print_turns(mario_action, current_level);
                }
                // action if there's a coin
                else if (current_item == 'c')
                {
                    mario_action = game_coins->interacts(game_mario);
                    exit << print_turns(mario_action, current_level);
                }
                // action if there's a goomba
                else if (current_item == 'g')
                {
                    mario_action = game_goomba->interacts(game_mario);
                    exit << print_turns(mario_action, current_level);
                    if (!game_goomba->get_result())
                    {
                        mark_as = 'g';
                    }
                }
                // action if there's a koopa
                else if (current_item == 'k')
                {
                    mario_action = game_koopa->interacts(game_mario);
                    exit << print_turns(mario_action, current_level);
                    if (!game_koopa->get_result())
                    {
                        mark_as = 'k';
                    }
                }
                // action if there's a boss
                // if mario wins against the boss in the final level
                else if (current_item == 'b')
                {
                    // runs until mario defeats the boss or dies
                    while (game_boss->get_result() == false)
                    {
                        mario_action = game_boss->interacts(game_mario);
                        exit << print_turns(mario_action, current_level);
                        if (game_boss->get_result() == true)
                        {
                            break;
                        }
                    }
                    // if mario wins against the boss in the final level
                    if (game_boss->get_result() == true && i == (game_world->get_levels() - 1))
                    {
                        game_boss->set_result(false);
                        exit << "\n Mario won the game and Princess Peach was saved!";
                        break;
                    }
                    // if mario beats the boss, but is not on final level
                    else if (game_boss->get_result() == true && i != (game_world->get_levels() - 1))
                    {
                        game_boss->set_result(false);
                        break;
                    }
                }
                // if mario encounters a warp pipe
                else if (current_item == 'w')
                {
                    mario_action = game_warp->interacts(game_mario, game_world);
                    exit << print_turns(mario_action, current_level);
                    break;
                }
                // just in case something doesn't run correctly
                else
                {
                    exit << "Something went wrong" << endl;
                }
                // if mario is out of lives break
                if (game_mario->get_lives() == 0)
                {
                    break;
                }
                mario_direction = game_mario->movement(game_world, mark_as);
                exit << print_movement(mario_direction);
                exit << endl;
                current_item = game_world->get_item(i, game_mario->get_mario_row(), game_mario->get_mario_col());
                game_world->set_item('H', i, game_mario->get_mario_row(), game_mario->get_mario_col());
                // exit << "Level: " << i + 1 << " After Mario's placement" << endl;
                exit << print_level(i);
                exit << flush;
            }
            // when mario runs out of lives he loses and it breaks
            if (game_mario->get_lives() <= 0)
            {
                exit << "Mario lost";
                break;
            }
            // if mario makes it through all the levels he wins
            if (game_boss->get_result() == true && i == (game_world->get_levels() - 1))
            {
                exit << "Mario won and Princess Peach was saved!";
                break;
            }
        }
    }
}
