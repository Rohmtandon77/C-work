/*
1a. Rohm Tandon & Anna Harner
1b. ID: 002397105 and ID: 002397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA4
*/

#include "Office.h"
#include "Window.h"
#include <iostream>
using namespace std;

Office::Office() : m_Windows(NULL), m_type('R'){
}

Office::Office(char type, int wCnt) : m_Windows(NULL), m_type(type), m_wCnt(wCnt){
    m_Windows = new Window[wCnt];
}

Office::~Office(){
    delete[] m_Windows;
}

char Office::getType(){
    return m_type;
}

void Office::logWindowIdleTime(int i){
    m_Windows[i].logWindowIdleTime();
}

int Office::windowIdleTime(int i){
    return m_Windows[i].windowIdleTime();
}

bool Office::allCustomersProcessed(){
    for (int i = 0; i < numWindows(); i++){
        // If any windows have an active customer
        if (m_Windows[i].hasActiveCustomer()){
            return false;
        }
    }
    return isEmpty();
}

int Office::numWindows(){
    return m_wCnt;
}

bool Office::doneAtWindow(int i){
    return m_Windows[i].isActiveCustomerDone();
}

void Office::advanceOneTick(int curTick){
    for (int i = 0; i < numWindows(); i++){
        m_Windows[i].advanceOneTick(this, curTick);
    }
}

void Office::enqueueCustomer(Customer *cust){
    m_queue.add(cust);
}

Customer *Office::dequeueCustomer(){
    return m_queue.remove();
}

int Office::waitTime(){
    return m_queue.size();
}

bool Office::isEmpty(){
    return m_queue.isEmpty();
}

Customer *Office::clearCustomerAtWindow(int i){
    auto cust = m_Windows[i].currentCustomer();
    m_Windows[i].clearCurrentCustomer();
    return cust;
}

void Office::debug(){
    for (int i = 0; i < m_wCnt; i++){
        m_Windows[i].debug();
    }
    if (m_queue.size() > 0){
        m_queue.peek()->debug();
    }
}
