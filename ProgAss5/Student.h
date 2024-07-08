#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <iostream>

using namespace std;

class Student{
    public:
        Student(int id);
        Student(string name, string level, string major, int id, int advisorId, double gpa);
        virtual ~Student();
        bool operator<(const Student& s);
        bool operator==(const Student& s);
        bool operator!=(const Student& s);
        const int getId() const;
        int getAdvisorId();
        void setAdvisorId(int id);
        double getGPA();
        string getName();
        string getLevel();
        string getMajor();
        friend std::ostream& operator<<(std::ostream& output, Student& s);
    private:
        int m_id, m_advisorId;
        string m_name, m_level, m_major;
        double m_gpa;
};

std::ostream& operator<<(std::ostream& output, Student& s);

#endif