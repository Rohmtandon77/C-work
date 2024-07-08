/*
1a. Anna Harner & Rohm Tandon
1b. ID: 002397569 and ID: 002397105
1c. harner@chapman.edu & rtandon@chapman.edu
1d. CPSC 350-03
1e. Assignment 2
*/


#ifndef STUDENT_H
#define STUDENT_H
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

class Student
{
public:
    Student();
    Student(int ID, string n, string g, string m, double gpaGrade, int ad);
    Student(int ID);
    ~Student();
    int getSID() const;
    string getSName() const;
    string getMajor() const;
    string getGrade() const;
    double getGPA() const;
    void setAdvisorID(int AdvisorID);
    int getAdvisorID() const;
    void removeAdvisor();
    friend ostream &operator<<(ostream &os, const Student &dt);
    bool operator<(const Student &s) const;
    bool operator>(const Student &s) const;
    bool operator==(const Student &s) const;
    bool operator!=(const Student &s) const;

private:
    int m_studentID;
    string m_studentName;
    string m_grade;
    string m_major;
    double m_GPA;
    int m_advisorID;
};

#endif
