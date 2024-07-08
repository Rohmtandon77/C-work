#ifndef STUDENT_H
#define STUDENT_H
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;



class Student {
public:
    Student();
    ~Student();
    void printStudent();
    void studentIDInfo();
    void newStudent();
    void deleteStudent();
    void changeAdvisor();
private:
    int studentID;
    string name;
    string grade;
    string major;
    double GPA;
    int advisor;
};

#endif
