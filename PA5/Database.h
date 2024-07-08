/*
1a. Anna Harner & Rohm Tandon
1b. ID: 002397569 and ID: 002397105
1c. harner@chapman.edu & rtandon@chapman.edu
1d. CPSC 350-03
1e. Assignment 2
*/

#ifndef DATABASE_H
#define DATABASE_H
#include <cstdlib>
#include <string>
#include <iostream>
#include "Student.h"
#include "Faculty.h"
#include "LazyBST.h"
using namespace std;

class Database
{
public:
    Database();
    ~Database();
    void printStudentFinal(ofstream &os);
    void printFacultyFinal(ofstream &os);
    void printStudent();
    void printFaculty();
    Student *getStudentByID(int StudentID);
    Faculty *getFacultyByID(int FacultyID);
    void printFacultyID(int FacultyID);
    void addStudent();
    void addStudentBatch(int studentID, string name,
                    string grade, string major, double GPA, int advisor);
    // void deleteStudent(int studentID);
    void addFaculty();
    void addFacultyBatch(int facultyID, string name, string level,
                    string department, int *advisees,
                    int num_advisees);
    void addAdvisee(int studentID, int facultyID);
    void deleteStudent(int studentID);
    void deleteFaculty(int facultyID);
    void changeAdvisor(int studentID, int facultyID);
    void removeAdvisee(int id);
    void Simulation(int option);

private:
    LazyBST<Student *> StudentLBBST;
    LazyBST<Faculty *> FacultyLBBST;
};

#endif