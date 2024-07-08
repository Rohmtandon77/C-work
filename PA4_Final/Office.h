/*
1a. Rohm Tandon & Anna Harner
1b. ID: 002397105 and ID: 002397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA4
*/

#ifndef OFFICE_H
#define OFFICE_H
#include "ListQueue.h"
#include "Customer.h"
#include "Window.h"
#include <iostream>
using namespace std;

class Office{
public:
    Office(char type, int wCnt);
    void addToBestWindow(Customer *cust);
    char getType();
    bool allCustomersProcessed();
    int numWindows();
    bool doneAtWindow(int i);
    void advanceOneTick(int curTick);
    void logWindowIdleTime(int i);
    int windowIdleTime(int i);
    Customer *clearCustomerAtWindow(int i);
    bool isEmpty();
    int waitTime();
    void enqueueCustomer(Customer *cust);
    Customer *dequeueCustomer();
    void debug();
    ~Office();

private:
    Office();
    Window *m_Windows;
    ListQueue<Customer *> m_queue;
    int m_wCnt;
    char m_type;
};
#endif
