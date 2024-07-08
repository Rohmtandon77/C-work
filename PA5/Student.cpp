/*
1a. Anna Harner & Rohm Tandon
1b. ID: 002397569 and ID: 002397105
1c. harner@chapman.edu & rtandon@chapman.edu
1d. CPSC 350-03
1e. Assignment 2
*/

#include "student.h"
#include <iostream>
#include <string>
using namespace std;

Student::Student()
{
    m_studentID = -1;
    m_studentName = "";
    m_grade = "";
    m_major = "";
    m_GPA = -1;
    m_advisorID = -1;
}

Student::Student(int ID, string n, string g, string m, double gpaGrade, int ad)
{
    m_studentID = ID;
    m_studentName = n;
    m_grade = g;
    m_major = m;
    m_GPA = gpaGrade;
    m_advisorID = ad;
    if (m_advisorID == -1)
    {
        cout << "Student doesn't have an advisor" << endl;
    }
}

Student::~Student()
{
}

Student::Student(int ID)
{
    m_studentID = ID;
}

int Student::getSID() const
{
    return m_studentID;
}

int Student::getAdvisorID() const
{
    return m_advisorID;
}

void Student::removeAdvisor()
{
    m_advisorID = -1;
}

void Student::setAdvisorID(int id)
{
    if (m_advisorID != -1)
    {
        cout << "Warning: Student already has an advisor" << endl;
    }
    m_advisorID = id;
    if (m_advisorID == -1)
    {
        cout << "Warning: Student does not have advisor." << endl;
    }
}

double Student::getGPA() const
{
    return m_GPA;
}

string Student::getSName() const
{
    return m_studentName;
}

string Student::getGrade() const
{
    return m_grade;
}

string Student::getMajor() const
{
    return m_major;
}

bool Student::operator<(const Student &s) const
{
    return (getSID() < s.getSID());
}

bool Student::operator>(const Student &s) const
{
    return (getSID() > s.getSID());
}

bool Student::operator==(const Student &s) const
{
    return (getSID() == s.getSID());
}

bool Student::operator!=(const Student &s) const
{
    return (getSID() != s.getSID());
}

ostream &operator<<(ostream &output, const Student &s)
{
    output << "ID: " + to_string(s.getSID()) +
                  " | Name: " + s.getSName() + " | Level: " + s.getGrade() +
                  " | Major: " + s.getMajor() + " | GPA: " + to_string(s.getGPA()) +
                  " | Advisor ID: " + (s.getAdvisorID() == -1 ? "none" : to_string(s.getAdvisorID()));
    output << endl;
    return output;
}
