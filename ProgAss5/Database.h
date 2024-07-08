#ifndef DATABASE_H
#define DATABASE_H
#include "ScapegoatST.h"
#include "Student.h"
#include "Faculty.h"
#include <fstream>


using namespace std;

class Database{
    public:
        Database();
        virtual ~Database();
        void printOptions();
        void handleChoice(int choice);
        void addStudent(string name, string level, string major, int id, int advisorId, double gpa);
        void updateStudentAdvisor(int id, int advisorId);
        void removeStudent(int id);
        void addFaculty(string name, string level, string department, int id);
        void removeFaculty(int id);
        Student* getStudent(int id, bool printError);
        Faculty* getFaculty(int id, bool printError);
        void printAllStudents();
        void printStudent(int id);
        void printAllFaculty();
        void printFaculty(int id);
        void saveToFile();
    private:
        ScapegoatST<Student*> *studentST;
        ScapegoatST<Faculty*> *facultyST;
        int convertInt(string input);
        double convertDouble(string input);
        fstream outputFile;
        
};

#endif