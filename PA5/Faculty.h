/*
1a. Anna Harner & Rohm Tandon
1b. ID: 002397569 and ID: 002397105
1c. harner@chapman.edu & rtandon@chapman.edu
1d. CPSC 350-03
1e. Assignment 2
*/

#ifndef FACULTY_H
#define FACULTY_H
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

class Faculty
{
public:
    Faculty();
    Faculty(int id);
    Faculty(int id, string name, string level, string department);
    // Faculty(int ID);
    ~Faculty();
    void removeAllAdvisees();
    int getFID() const;
    string getFName() const;
    string getDepartment() const;
    string getLevel() const;
    int getSize() const;
    int getAdvisee(int i) const;
    void addAdvisee(int sid);
    void removeAdvisee(int sid);
    friend ostream &operator<<(ostream &os, const Faculty &dt);
    bool operator<(const Faculty &f) const;
    bool operator>(const Faculty &s) const;
    bool operator==(const Faculty &f) const;
    bool operator!=(const Faculty &f) const;

private:
    int m_facultyID;
    string m_facultyName;
    string m_level;
    string m_department;
    int m_size;
    int m_max_advisees;
    int *m_advisees;
};

#endif
