/**
 * Full Name: Maxim Karpinsky
 * Student ID: 2405869
 * Chapman Email: karpinsky@chapman.edu
 * Course Number & Section: CPSC-350-01
 * Assignment: PA5 - The GOAT
 */

/**
 * @file Faculty.cpp
 * @brief faculty file for creating an object representing a faculty in the database
 */

#include "Faculty.h"
using namespace std;

/**
 * @brief Constrcutor for Faculty
 * 
 * @param name - name of faculty
 * @param level - level of faculty
 * @param department - department teaching
 * @param id - id of faculty
 */
Faculty::Faculty(string name, string level, string department, int id) {
    m_id = id;
    m_adviseeIds = new DblList<int>();
    m_name = name;
    m_level = level;
};

/**
 * @brief construcotr for a ghost Faculty to do comparisons in scape goat tree
 * 
 * @param id - id of faculty
 */
Faculty::Faculty(int id) {
    m_id = id; 
}

/**
 * @brief destrcutor removes the advisee list
 * 
 */
Faculty::~Faculty() {
    delete m_adviseeIds;
};

/**
 * @brief getID - gets the Id of faculty
 * 
 * @return int - faculty id
 */
int Faculty::getId() {
    return m_id;
}

/**
 * @brief getName - gets name of faculty
 * 
 * @return string - name of faculty
 */
string Faculty::getName() {
    return m_name;
}

/**
 * @brief getLevel - gets level of faculty
 * 
 * @return string - level
 */
string Faculty::getLevel() {
    return m_level;
}

/**
 * @brief getADviseeIds - returns pointer of advisee doubly llinked list
 * 
 * @return DblList<int>* double linked list of advisee ids
 */
DblList<int>* Faculty::getAdviseeIds() {
    return m_adviseeIds;
}

/**
 * @brief addAdvisee - adds advisee to advisee list
 * 
 * @param id - id to add
 */
void Faculty::addAdvisee(int id) {
    m_adviseeIds->addBack(id);
}

/**
 * @brief removeAdvisee - removes an id from the advisee list
 * 
 * @param id - id to remove
 */
void Faculty::removeAdvisee(int id) {
    int adviseeSize = m_adviseeIds->size();

    for(int i = 0; i < adviseeSize; i++) {
        if(m_adviseeIds->get(i) == id) {
            m_adviseeIds->remove(i);
            return;
        }
    }
}

/**
 * @brief overload oeprator for <
 * 
 * @param f - other faculty to compare to
 * @return true - this faculty's id is less than other faculty's id
 * @return false - opposite case as above
 */
bool Faculty::operator<(const Faculty &f) {
    return(getId() < f.m_id);
};

/**
 * @brief overload operator for ==
 * 
 * @param f - other faculty
 * @return true - if both faculty ids are equal
 * @return false - opposite case as above
 */
bool Faculty::operator==(const Faculty &f) {
    return(getId() == f.m_id);
};

/**
 * @brief overload operator for !=
 * 
 * @param f - other faculty
 * @return true - if both faculty do not have same id
 * @return false - opposite case as above
 */
bool Faculty::operator!=(const Faculty &f) {
    return(getId() != f.m_id);
};

/**
 * @brief overload operator for printing this object
 * 
 * @param output - ouput stream
 * @param f - faculty 
 * @return ostream& 
 */
ostream& operator<<(ostream& output, Faculty& f) 
{
   output << "ID: " + to_string(f.getId()) + " | Name: " + f.getName() + " | Level: " + f.getLevel() + " | Advisee ID's: ";

    int adviseeSize = f.getAdviseeIds()->size();

    for(int i = 0; i < adviseeSize; i++) {
        output << to_string(f.getAdviseeIds()->get(i)) + " ";
    }

   return output;  
}

