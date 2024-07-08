#ifndef FACULTY_H
#define FACULTY_H
#include <string>
#include <iostream>
#include "Dbllist.h"

using namespace std;

class Faculty{
    public:
        Faculty(int id);
        Faculty(string name, string level, string department, int id);
        virtual ~Faculty();
        bool operator<(const Faculty& f);
        bool operator==(const Faculty& f);
        bool operator!=(const Faculty& f);
        int getId();
        string getName();
        string getLevel();
        void addAdvisee(int id);
        void removeAdvisee(int id);
        DblList<int>* getAdviseeIds();

        friend std::ostream& operator<<(std::ostream& output, Faculty& f);
    private:
        int m_id;
        string m_name, m_level, m_department;
        DblList<int> *m_adviseeIds;        
};

std::ostream& operator<<(std::ostream& output, Faculty& f);

#endif