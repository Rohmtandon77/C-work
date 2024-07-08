/**
 * Full Name: Maxim Karpinsky
 * Student ID: 2405869
 * Chapman Email: karpinsky@chapman.edu
 * Course Number & Section: CPSC-350-01
 * Assignment: PA5 - The GOAT
 */

/**
 * @file Student.cpp
 * @brief - Student file for representation of student in the database
 */

#include "Student.h"
using namespace std;

/**
 * @brief Student Constructor
 * 
 * @param name - name of student
 * @param level - level of student
 * @param major - major of student
 * @param id - unique id of student
 * @param advisorId - id of advisor can be -1 to represent not having one
 * @param gpa - gpa of student
 */
Student::Student(string name, string level, string major, int id, int advisorId, double gpa) {
    m_id = id;
    m_advisorId = advisorId;
    m_name = name;
    m_level = level;
    m_major = major;
    m_gpa = gpa;

    if(advisorId == -1) {
        cout << "Warning: Student does not have advisor." << endl;
    }
};

/**
 * @brief constructor for creating ghost student for comparisons and searching in scape goat tree
 * 
 * @param id - id of student
 */
Student::Student(int id) {
    m_id = id;
}

/**
 * @brief destrcutor for student
 * 
 */
Student::~Student() {

};

/**
 * @brief get method to get id
 * 
 * @return const int 
 */
const int Student::getId() const {
    return m_id;
}

/**
 * @brief get method to get advisor id
 * 
 * @return int 
 */
int Student::getAdvisorId() {
    return m_advisorId;
}

/**
 * @brief setter method to set advisor id, can be set to none but warns
 * 
 * @param id 
 */
void Student::setAdvisorId(int id) {
    m_advisorId = id;

    if(id == -1) {
        cout << "Warning: Student does not have advisor." << endl;
    }
}

/**
 * @brief get method to get GPA
 * 
 * @return double 
 */
double Student::getGPA() {
    return m_gpa;
}

/**
 * @brief get method to get name
 * 
 * @return string 
 */
string Student::getName() {
    return m_name;
}

/**
 * @brief get method to get level
 * 
 * @return string 
 */
string Student::getLevel() {
    return m_level;
}

/**
 * @brief get method to get major
 * 
 * @return string 
 */
string Student::getMajor() {
    return m_major;
}

/**
 * @brief overload operator to compare student <
 * 
 * @param s - other student
 * @return true - if this students id is less than other
 * @return false - opposite case as above
 */
bool Student::operator<(const Student &s) {
    return(getId() < s.getId());
};

/**
 * @brief overload operator to compare student ==
 * 
 * @param s - other student
 * @return true - if this students id equals other
 * @return false - opposite case as above
 */
bool Student::operator==(const Student &s) {
    return(getId() == s.getId());
};

/**
 * @brief overload operator to compare student !=
 * 
 * @param s - other student
 * @return true - if this students id does not equal other
 * @return false - opposite case as above
 */
bool Student::operator!=(const Student &s) {
    return(getId() != s.getId());
};

/**
 * @brief overload print statement for printing this object
 * 
 * @param output 
 * @param s 
 * @return ostream& 
 */
ostream& operator<<(ostream& output, Student& s) 
{
   output << "ID: " + to_string(s.getId()) + " | Name: " + s.getName() + " | Level: " + s.getLevel() + " | Major: " + s.getMajor() + " | GPA: " + to_string(s.getGPA())  + " | Advisor ID: " + (s.getAdvisorId() == -1 ? "none" : to_string(s.getAdvisorId()));
   return output;  
}


