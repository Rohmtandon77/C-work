/**
 * Full Name: Maxim Karpinsky
 * Student ID: 2405869
 * Chapman Email: karpinsky@chapman.edu
 * Course Number & Section: CPSC-350-01
 * Assignment: PA5 - The GOAT
 */

/**
 * @file main.cpp
 * @brief main file for running program
 */

#include <fstream>
#include <iostream>
#include <string>

#include "Faculty.h"
#include "Student.h"
#include "Database.h"

using namespace std;

/**
 * @brief runs program, creates database, and initializes the interface
 * 
 */
int main(int argc, char** argv) {

    Database localDB;

    int choice = 0;

    cout << "Welcome to the Institution Database." << endl;

    while(choice != 11) {
        
        string mystr;

        localDB.printOptions();
        cout << "Select a command number (1-11): ";
        getline (cin, mystr);

        cout << endl;

        try {
            choice = stoi(mystr);

            if(choice < 1 || choice > 11) {
                throw invalid_argument("received out of bounds option");
            } else {
                localDB.handleChoice(choice);
            }
        } catch(invalid_argument) {
            cout << "Select a valid option!" << endl;
        }
    }



    return 0;

}
