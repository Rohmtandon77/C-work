/*
1a. Anna Harner & Rohm Tandon
1b. ID: 002397569 and ID: 002397105
1c. harner@chapman.edu & rtandon@chapman.edu
1d. CPSC 350-03
1e. Assignment 2
*/

#include <iostream>
#include "LazyBST.h"
#include "TreeNode.h"
#include "Student.h"
#include "Faculty.h"
#include "Database.h"
#include <string>
using namespace std;
#include <fstream>

Database::Database()
{
}

// Destructor deleting Studet and Faculty objects
Database::~Database()
{
}

// 1.Print all students and their information (sorted by ascending id #)
void Database::printStudentFinal(ofstream &os)
{
    if (StudentLBBST.size() == 0)
    {
        cout << "Tree is empty!" << endl;
    }
    else
    {
        StudentLBBST.printInOrder(os);
    }
}

void Database::printStudent()
{
    if (StudentLBBST.size() == 0)
    {
        cout << "Tree is empty!" << endl;
    }
    else
    {
        StudentLBBST.printInOrder();
    }
}

// 2.Print all faculty and their information (sorted by ascending id #)
void Database::printFacultyFinal(ofstream &os)
{
    if (FacultyLBBST.size() == 0)
    { // if m_size no worky, make a getter for the size in the LBBST class
        cout << "Tree is empty!" << endl;
    }
    else
    {
        FacultyLBBST.printInOrder(os);
    }
}

void Database::printFaculty()
{
    if (FacultyLBBST.size() == 0)
    { // if m_size no worky, make a getter for the size in the LBBST class
        cout << "Tree is empty!" << endl;
    }
    else
    {
        FacultyLBBST.printInOrder();
    }
}

// 3.Find and display student information given the student id
Student *currStudent;
Student *Database::getStudentByID(int studentID)
{
    auto s = new Student(studentID);
    Student *currStudent = StudentLBBST.get(s);
    if (currStudent == NULL)
    {
        cout << "Student with that ID does not exist, please check!" << endl;
        return NULL;
    }
    else
    {
        cout << *currStudent << endl;
        return currStudent;
    }
}

Faculty *Database::getFacultyByID(int facID)
{
    auto f = new Faculty(facID);
    Faculty *currFac = FacultyLBBST.get(f);
    if (currFac == NULL)
    {
        cout << "Faculty with that ID does not exist, please check!" << endl;
        return NULL;
    }
    else
    {
        cout << *currFac << endl;
        return currFac;
    }
}

// 4.Find and display faculty information given the faculty id
void Database::printFacultyID(int FacultyID)
{
    Faculty *fac = getFacultyByID(FacultyID);
    cout << *fac << endl;
}

// 5.Add a new student
void Database::addStudentBatch(int studentID, string name, string grade, string major, double GPA, int advisor)
{
    auto s = new Student(studentID, name, grade, major, GPA, advisor);
    StudentLBBST.insert(s);
    StudentLBBST.rebalance();
}

void Database::addStudent()
{
    string studentName;
    string studentLevel;
    string Major;

    cout << "Student ID: " << endl;
    int studentID;
    cin >> studentID;
    cin.ignore ();

    cout << "Student name: " << endl;
    getline(cin, studentName);

    cout << "Student level: " << endl;
    getline(cin, studentLevel);

    cout << "Major: " << endl;
    getline(cin, Major);

    cout << "GPA: " << endl;
    double GPA;
    cin >> GPA;
    cin.ignore ();

    cout << "Advisor ID: " << endl;
    int advisorID;
    cin >> advisorID;
    cin.ignore ();

    auto s = new Student(studentID, studentName, studentLevel, Major, GPA, advisorID);

    // Link the faculty
    auto fac = getFacultyByID(advisorID);
    if (fac != NULL)
    {
        fac->addAdvisee(studentID);
    }

    StudentLBBST.insert(s);
}

// 6. Delete a student given the id
void Database::deleteStudent(int studentID)
{
    auto stu = getStudentByID(studentID);
    if (stu == NULL)
    {
        cout << "That student doesn't exist" << endl;
        return;
    }
    StudentLBBST.remove(stu);
}

// 7.Add a new faculty member
void Database::addFacultyBatch(int facultyID, string name,
                               string level, string department,
                               int *advisees, int num_advisees)
{
    auto fac = new Faculty(facultyID, name, level, department);
    for (int i = 0; i < num_advisees; i++)
    {
        auto stu = getStudentByID(advisees[i]);
        stu->setAdvisorID(fac->getFID());
        fac->addAdvisee(advisees[i]);
    }
    FacultyLBBST.insert(fac);
}

void Database::addFaculty()
{
    int max_advisees = 2;
    cout << "Faculty ID: ";
    int facultyID;
    cin >> facultyID;
    cin.ignore ();

    cout << "Faculty name: ";
    string facultyName;
    getline(cin,facultyName);

    cout << "Faculty level: ";
    string facultyLevel;
    getline(cin,facultyLevel);

    cout << "Department: ";
    string Department;
    cin >> Department;
    getline(cin,Department);

    int nextId = -1;
    auto fac = new Faculty(facultyID, facultyName, facultyLevel, Department);
    // Find all students with this faculty advisor
    auto allStudents = StudentLBBST.to_array();
    for (int i = 0; i < StudentLBBST.size(); i++)
    {
        auto stu = allStudents[i];
        if (facultyID == stu->getAdvisorID())
        {
            fac->addAdvisee(stu->getSID());
        }
    }
    FacultyLBBST.insert(fac);
}

// 8.Delete a faculty member given the id.
void Database::deleteFaculty(int facultyID)
{
    auto fac = getFacultyByID(facultyID);
    if (fac == NULL)
    {
        cout << "That faculty doesn't exist" << endl;
        return;
    }
    if (fac->getSize() > 0)
    {
        cout << "Refusing to delete faculty with advisees" << endl;
        return;
    }
    FacultyLBBST.remove(fac);
}

// 9.Change a student’s advisor given the student id and the new faculty id.
void Database::changeAdvisor(int studentID, int facultyID)
{
    removeAdvisee(studentID);
    addAdvisee(studentID, facultyID);
}

void Database::addAdvisee(int studentID, int facultyID)
{
    Faculty *new_fac = getFacultyByID(facultyID);
    Student *stu = getStudentByID(studentID);
    new_fac->addAdvisee(studentID);
    stu->setAdvisorID(new_fac->getFID());
}

// 10.Remove an advisee from a faculty member given the ids
void Database::removeAdvisee(int studentID)
{
    Student *stu = getStudentByID(studentID);
    Faculty *old_fac = getFacultyByID(stu->getAdvisorID());
    old_fac->removeAdvisee(studentID);
    stu->removeAdvisor();
}

// 11. exit

// Simulation
void Database::Simulation(int option)
{
    while (option != 11)
    {
        cout << "1) Print all students and their information" << endl;
        cout << "2) Print all faculty and their information" << endl;
        cout << "3) Print a Students information by their ID" << endl;
        cout << "4) Print a Faculty members information by their ID" << endl;
        cout << "5) Add a student" << endl;
        cout << "6) Delete a student given their ID" << endl;
        cout << "7) Add a faculty member" << endl;
        cout << "8) Delete a faculty member given their ID" << endl;
        cout << "9) Change a students advisor given both the student and faculty ID" << endl;
        cout << "10) Remove an advisee from a faculty member given the student ID" << endl;
        cout << "11) Exit" << endl;

        cout << "Choose your option: " << endl;
        cin >> option;

        if (option == 1)
        {
            printStudent();
        }
        else if (option == 2)
        {
            printFaculty();
        }
        else if (option == 3)
        {
            int studID;
            cout << "Enter student ID you want to find: " << endl;
            cin >> studID;
            try{
              getStudentByID(studID);
            }
            catch(invalid_argument){
              cout<<"Please try again by typing a valid ID"<<endl;
              return Simulation(3);

            }
            cout << currStudent << endl;
        }
        else if (option == 4)
        {
            int facID;
            cout << "Enter Faculty ID you want to find: " << endl;
            cin >> facID;
            try{
              getFacultyByID(facID);
            }
            catch(invalid_argument){
              cout<<"Please try again by typing a valid ID"<<endl;
              return Simulation(4);

            }
        }
        else if (option == 5)
        {
            addStudent();
        }
        else if (option == 6)
        {
            int stuID;
            cout << "Enter student ID you want to remove: " << endl;
            cin >> stuID;
            deleteStudent(stuID);
        }
        else if (option == 7)
        {
            addFaculty();
        }
        else if (option == 8)
        {
            int facID;
            cout << "Enter faculty ID you want to remove: " << endl;
            cin >> facID;
            deleteFaculty(facID);
        }
        else if (option == 9)
        {
            int studentID;
            int facultyID;
            cout << "Enter the studentID whose advisor you want to change: " << endl;
            cin >> studentID;
            cout << "Enter the facultyID who will be the new advisor: " << endl;
            cin >> facultyID;
            changeAdvisor(studentID, facultyID);
            addAdvisee(studentID, facultyID);
        }
        else if (option == 10)
        {
            int studentID;
            cout << "Enter the studentID for the advisee you'd like to remove" << endl;
            cin >> studentID;
            Student *stu = getStudentByID(studentID);
            Faculty *old_fac = getFacultyByID(stu->getAdvisorID());
            try{
              old_fac->removeAdvisee(studentID);
              stu->removeAdvisor();
            }
            catch(...){
              return Simulation(10);
            }
        }
        else if (option == 11)
        {
            ofstream myfile;
            myfile.open("example.txt");
            myfile << "Exiting this simulation and writing to a file..." << endl;
            printStudentFinal(myfile);
            printFacultyFinal(myfile);
            myfile.close();
        }
        else
        {
            cout << "That is not a valid option, pick another" << endl;
        }
    }
}
