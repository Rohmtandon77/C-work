/**
 * Full Name: Maxim Karpinsky
 * Student ID: 2405869
 * Chapman Email: karpinsky@chapman.edu
 * Course Number & Section: CPSC-350-01
 * Assignment: PA5 - The GOAT
 */

/**
 * @file Database.cpp
 * @brief Database class for holding student and faculty records in instituion
 */

#include "Database.h"
#include <iostream>
using namespace std;


/**
 * @brief Constructor for Database makes two Scapegoat Trees for students and faculty.
 * 
 */
Database::Database() {
    studentST = new ScapegoatST<Student*>();
    facultyST = new ScapegoatST<Faculty*>();
};

/**
 * @brief Destructor, deletes scapegoat trees when done
 * 
 */
Database::~Database() {
    delete studentST;
    delete facultyST;
};

/**
 * @brief printOptions - prints to console available commands to manipulate the database
 * 
 */
void Database::printOptions() {
    cout << endl;
    cout << " (1) - Print all students and their information (sorted by ascending id #)" << endl;
    cout << " (2) - Print all faculty and their information (sorted by ascending id #)" << endl;
    cout << " (3) - Print specific student information" << endl;
    cout << " (4) - Print specific faculty information" << endl;
    cout << " (5) - Add a new student" << endl;
    cout << " (6) - Delete a student" << endl;
    cout << " (7) - Add a new faculty member" << endl;
    cout << " (8) - Delete a faculty member" << endl;
    cout << " (9) - Change a student’s advisor" << endl;
    cout << " (10) - Remove an advisee from a faculty member" << endl;
    cout << " (11) - Exit" << endl;
}

/**
 * @brief convertInt - converts a string to int and prints an error if there is one, helpful for taking user input
 * 
 * @param input - stirng input
 * @return int - converted string as int
 */
int Database::convertInt(string input) {

    int convertedInt;

    try {
        convertedInt = stoi(input);
        return convertedInt;
    } catch(invalid_argument) {
        cout << "Type in an integer!" << endl;
        return -4309583;
    }
}

/**
 * @brief convertDouble - same as above but for doubles
 * 
 * @param input 
 * @return double 
 */
double Database::convertDouble(string input) {

    double convertedDouble;

    try {
        convertedDouble = stod(input);
        return convertedDouble;
    } catch(invalid_argument) {
        cout << "Type in a double!" << endl;
        return -4309583.0;
    }
}

/**
 * @brief saveToFile - outputs the current database registries to databaseLog.txt
 * 
 */
void Database::saveToFile() {
    outputFile.open("databaseLog.txt", ios::out); 

    outputFile << "Student DB" << endl;
    
    while(studentST->getSize() != 0) {
        Student* tempStudent = studentST->getMin();
        studentST->remove(tempStudent);
        outputFile << *tempStudent << endl;
    }

    outputFile << endl;

    outputFile << "Faculty DB" << endl;
    
    while(facultyST->getSize() != 0) {
        Faculty* tempFaculty = facultyST->getMin();
        facultyST->remove(tempFaculty);
        outputFile << *tempFaculty << endl;
    }

    outputFile.close();
}

/**
 * @brief handleChoice - handles a text input to initiate its attached command (numbers 1-11)
 * 
 * @param choice integer choice of a command
 */
void Database::handleChoice(int choice) {

    string inputtedString;

    if(choice == 1) {
        printAllStudents();
    } else if (choice == 2) {
        printAllFaculty();
    } else if (choice == 3) {
        int id = -4309583;

        while(id == -4309583) {
            cout << "Enter Student ID: ";
            getline (cin, inputtedString);
            id = convertInt(inputtedString);
        }

        printStudent(id);
    } else if (choice == 4) {
        int id = -4309583;

        while(id == -4309583) {
            cout << "Enter Faculty ID: ";
            getline (cin, inputtedString);
            id = convertInt(inputtedString);
        }

        printFaculty(id);
    } else if (choice == 5) {
        cout << "Enter Student Name: ";
        getline (cin, inputtedString);
        string name = inputtedString;

        cout << "Enter Student Level: ";
        getline (cin, inputtedString);
        string level = inputtedString;

        cout << "Enter Student Major: ";
        getline (cin, inputtedString);
        string major = inputtedString;
        
        int id = -4309583;
        int idInDB = false;

        while(id == -4309583 || !idInDB) {
            cout << "Enter Student ID: ";
            getline (cin, inputtedString);
            id = convertInt(inputtedString);

            idInDB = (getStudent(id, false) == NULL);

            if(!idInDB) {
                cout << "ID already exists in database!" << endl;
            }
        }

        int advisorId = -4309583;

        while(advisorId == -4309583) {
            cout << "Enter Advisor ID (enter -1 for none): ";
            getline (cin, inputtedString);
            advisorId = convertInt(inputtedString);
        }

        double gpa = -4309583.0;

        while(gpa == -4309583.0) {
            cout << "Enter GPA: ";
            getline (cin, inputtedString);
            gpa = convertDouble(inputtedString);
        }

        addStudent(name, level, major, id, advisorId, gpa);
    } else if(choice == 6) {
        int id = -4309583;

        while(id == -4309583) {
            cout << "Enter Student ID to delete: ";
            getline (cin, inputtedString);
            id = convertInt(inputtedString);
        }

        removeStudent(id);
    } else if (choice == 7) {
        cout << "Enter Faculty Name: ";
        getline (cin, inputtedString);
        string name = inputtedString;

        cout << "Enter Faculty Level: ";
        getline (cin, inputtedString);
        string level = inputtedString;

        cout << "Enter Faculty Department: ";
        getline (cin, inputtedString);
        string department = inputtedString;
        
        int id = -4309583;
        int idInDB = false;

        while(id == -4309583 || !idInDB) {
            cout << "Enter Faculty ID: ";
            getline (cin, inputtedString);
            id = convertInt(inputtedString);
            idInDB = (getFaculty(id, false) == NULL);

            if(!idInDB) {
                cout << "ID already exists in database!" << endl;
            }
        }

        addFaculty(name, level, department, id);
    } else if (choice == 8) {
        int id = -4309583;

        while(id == -4309583) {
            cout << "Enter Faculty ID to delete: ";
            getline (cin, inputtedString);
            id = convertInt(inputtedString);
        }

        removeFaculty(id);
    } else if (choice == 9) {
        int id = -4309583;

        while(id == -4309583) {
            cout << "Enter Student ID to update: ";
            getline (cin, inputtedString);
            id = convertInt(inputtedString);
        }

        int newAdvisorID = -4309583;

        while(newAdvisorID == -4309583) {
            cout << "Enter new Advisor ID: ";
            getline (cin, inputtedString);
            newAdvisorID = convertInt(inputtedString);
        }

        updateStudentAdvisor(id, newAdvisorID);
    } else if (choice == 10) {
        int id = -4309583;

        while(id == -4309583) {
            cout << "Enter Faculty ID to update: ";
            getline (cin, inputtedString);
            id = convertInt(inputtedString);
        }

        int studentIdToRemove = -4309583;

        while(studentIdToRemove == -4309583) {
            cout << "Enter Student ID to remove: ";
            getline (cin, inputtedString);
            studentIdToRemove = convertInt(inputtedString);
        }

        getFaculty(id, true)->removeAdvisee(studentIdToRemove);
        getStudent(studentIdToRemove, true)->setAdvisorId(-1);
    } else if (choice == 11) {
        saveToFile();
    }
}

/**
 * @brief getStudent - returns a student in the database
 * 
 * @param id - id of student to retrieve
 * @return Student* - pointer object of student
 */
Student* Database::getStudent(int id, bool printError) {
    Student* currStudent = new Student(id);

    currStudent = studentST->get(currStudent);

    if(currStudent == NULL && printError) {
        cout << "Error: Student not Found!" << endl;
    }
    
    return currStudent;
}

/**
 * @brief getFaculty - same as above but for faculty registries
 * 
 * @param id 
 * @return Faculty* 
 */
Faculty* Database::getFaculty(int id, bool printError) {
    Faculty* currFaculty = new Faculty(id);

    currFaculty = facultyST->get(currFaculty);

    if(currFaculty == NULL && id != -1 && printError) {
        cout << "Error: Faculty not Found!" << endl;
    }
    
    return currFaculty;
}

/**
 * @brief adds a new student to the database
 * 
 * @param name - name of student
 * @param level - school level, freshmen, sophomore, etc.
 * @param major - major of student
 * @param id  - student unique id
 * @param advisorId - id of advisor
 * @param gpa - gpa of student
 */
void Database::addStudent(string name, string level, string major, int id, int advisorId, double gpa) {
    Student* student = new Student(name, level, major, id, advisorId, gpa);

    Faculty* currFaculty = getFaculty(advisorId, true);

    if(currFaculty != NULL || advisorId == -1) {
        studentST->insert(student);

        if(currFaculty != NULL) {
            currFaculty->addAdvisee(id);
        }
    }
}

/**
 * @brief updateStudentAdvisor - update the advisor of a student in db
 * 
 * @param id - id of student
 * @param advisorId - id of new advisor
 */
void Database::updateStudentAdvisor(int id, int advisorId) {
    Student* currStudent = getStudent(id, true);

    if(currStudent != NULL) {
        Faculty* oldFaculty = getFaculty(currStudent->getAdvisorId(), true);
        Faculty* newFaculty = getFaculty(advisorId, true);

        if(newFaculty != NULL || advisorId == -1) {
            if(currStudent->getAdvisorId() != -1) {
                oldFaculty->removeAdvisee(id);
            }
            currStudent->setAdvisorId(advisorId);
            if(newFaculty != NULL) {
                newFaculty->addAdvisee(id);
            }
        }
    }
}

/**
 * @brief removeStudent - removes student from DB
 * 
 * @param id - id of student to remove
 */
void Database::removeStudent(int id) {
    Student* currStudent = getStudent(id, true);

    if(currStudent != NULL) {
         int advisorId = currStudent->getAdvisorId();

        Faculty* currFaculty = new Faculty(advisorId);

        currFaculty = facultyST->get(currFaculty);

        currFaculty->removeAdvisee(id);

        studentST->remove(currStudent);
    }
}

/**
 * @brief addFaculty - adds a faculty to the DB
 * 
 * @param name - name of faculty
 * @param level - ranking of faculty
 * @param department - department they teach in
 * @param id - their unique id
 */
void Database::addFaculty(string name, string level, string department, int id) {
    Faculty* faculty = new Faculty(name, level, department, id);
    facultyST->insert(faculty);
}

/**
 * @brief removeFaculty - removes faculty from the DB
 * 
 * @param id - id to remove
 */
void Database::removeFaculty(int id) {
    Faculty* currFaculty = getFaculty(id, true);

    if(currFaculty != NULL) {
        if(currFaculty->getAdviseeIds()->size() > 0) {
            cout << "Warning: Deleting a Faculty that has Advisees. Advisees will no longer have an advisor." << endl;

            DblList<int>* adviseeList = currFaculty->getAdviseeIds();

            while(!adviseeList->isEmpty()) {
                int studentId = adviseeList->removeFront();

                updateStudentAdvisor(studentId, -1);
            }
        }

        facultyST->remove(currFaculty);
    }
}

/**
 * @brief printAllStudents - prints all students to console in ascending order by id
 * 
 */
void Database::printAllStudents() {
    if(studentST->getSize() == 0) {
        cout << "Student Database is Empty!" << endl;
    } else {
        cout << "Student Database:" << endl;
        studentST->printTreeInOrder();
    }   
}

/**
 * @brief printStudent - prints a specific student given an id
 * 
 * @param id - id of student
 */
void Database::printStudent(int id) {
    Student* currStudent = getStudent(id, true);

    if(currStudent != NULL) {
        cout << *currStudent << endl;
    }
}

/**
 * @brief printAllFaculty - prints all faculty in DB
 * 
 */
void Database::printAllFaculty() {
    if(facultyST->getSize() == 0) {
        cout << "Faculty Database is Empty!" << endl;
    } else {
        cout << "Faculty Database:" << endl;
        facultyST->printTreeInOrder();
    }   
}

/**
 * @brief printFaculty - prints a specific faculty given an id
 * 
 */
void Database::printFaculty(int id) {
    Faculty* currFaculty = getFaculty(id, true);

    if(currFaculty != NULL) {
        cout << *currFaculty << endl;
    }  
}
