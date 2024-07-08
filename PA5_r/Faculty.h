#ifndef FACULTY_H
#define FACULTY_H
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;



class Faculty {
public:
    Faculty();
    ~Faculty();
    void printFaculty();
    void FacultyIDInfo();
    void newFaculty();
    void deleteFaculty();
    void removeAdvisee();
private:
    int studentID;
    string name;
    string grade;
    string major;
    double GPA;
    int advisor;
};

#endif
