/*
1a. Anna Harner & Rohm Tandon
1b. ID: 002397569 and ID: 002397105
1c. harner@chapman.edu & rtandon@chapman.edu
1d. CPSC 350-03
1e. Assignment 2
*/

#include "Faculty.h"
#include <iostream>
#include <string>
using namespace std;

Faculty::Faculty()
{
    m_facultyID = -1;
    m_facultyName = "";
    m_level = "";
    m_department = "";
    m_size = -1;
    m_advisees = NULL;
}

Faculty::Faculty(int id)
{
    m_facultyID = id;
    m_facultyName = "";
    m_level = "";
    m_department = "";
    m_size = -1;
    m_advisees = NULL;
}

const int ADVISEE_BLOCK = 10;

Faculty::Faculty(int id, string name, string level, string department) : m_facultyID(id),
                                                                         m_facultyName(name), m_level(level),
                                                                         m_department(department),
                                                                         m_max_advisees(0)
{
}

// Faculty::Faculty(int ID){
//     m_facultyID=ID;
// }

Faculty::~Faculty()
{
    delete[] m_advisees;
}

int Faculty::getFID() const
{
    return m_facultyID;
}

string Faculty::getFName() const
{
    return m_facultyName;
}

string Faculty::getLevel() const
{
    return m_level;
}

int Faculty::getSize() const
{
    return m_size;
}

void Faculty::addAdvisee(int sid)
{
    // Allocate more if needed
    if (m_size >= m_max_advisees)
    {
        m_max_advisees += ADVISEE_BLOCK;
        auto tmp = new int[m_max_advisees];
        for (int i = 0; i < m_size; i++)
        {
            tmp[i] = m_advisees[i];
        }
        delete[] m_advisees;
        m_advisees = tmp;
    }
    m_advisees[m_size++] = sid;
}

void Faculty::removeAdvisee(int sid)
{
    int adv = -1, j = 0;
    auto tmp = new int[m_size - 1];
    for (int i = 0; i < m_size; i++)
    {
        adv = m_advisees[i];
        if (sid != adv)
        {
            tmp[j++] = adv;
        }
    }
    m_size--;
    for (int i = 0; i < m_size; i++)
    {
        m_advisees[i] = tmp[i];
    }
    delete[] tmp;
}

string Faculty::getDepartment() const
{
    return m_department;
}

int Faculty::getAdvisee(int i) const
{
    return m_advisees[i];
}

void Faculty::removeAllAdvisees()
{
    delete[] m_advisees;
    m_advisees = NULL;
    m_size = 0;
}

bool Faculty::operator>(const Faculty &f) const
{
    return (getFID() > f.m_facultyID);
}

bool Faculty::operator<(const Faculty &f) const
{
    return (getFID() < f.m_facultyID);
}

bool Faculty::operator==(const Faculty &f) const
{
    return (getFID() == f.m_facultyID);
}

bool Faculty::operator!=(const Faculty &f) const
{
    return (getFID() != f.m_facultyID);
}

ostream &operator<<(ostream &output, const Faculty &f)
{
    output << "ID: " + to_string(f.getFID()) +
                  " | Name: " + f.getFName() + " | Level: " + f.getLevel() +
                  " | Department: " + f.getDepartment();
    output << " Advisee IDs: ";
    for (int i = 0; i < f.getSize(); i++)
    {
        output << f.getAdvisee(i) << " ";
    }
    output << endl;
    return output;
}