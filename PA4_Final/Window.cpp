/*
1a. Rohm Tandon & Anna Harner
1b. ID: 002397105 and ID: 002397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA4
*/

#include "Window.h"
#include "Office.h"

using namespace std;

Window::Window() : m_ticksRemaining(0),
                   m_activeCustomer(false),
                   m_currentCustomer(NULL),
                   m_idleTime(0)
{
}

Window::~Window(){};

bool Window::isActiveCustomerDone(){
    if (m_activeCustomer)
    {
        return m_ticksRemaining == 0;
    }
    return false;
}

bool Window::hasActiveCustomer(){
    return m_activeCustomer;
}

void Window::logWindowIdleTime(){
    if (!hasActiveCustomer())
    {
        m_idleTime++;
    }
}

int Window::windowIdleTime(){
    return m_idleTime;
}

Customer *Window::currentCustomer(){
    return m_currentCustomer;
}

void Window::clearCurrentCustomer(){
    m_currentCustomer = NULL;
    m_activeCustomer = false;
}

void Window::advanceOneTick(Office *office, int curTick){
    if (m_activeCustomer)
    { // If we have an active student, decrement their count
        if (m_ticksRemaining == 0)
        {
            cout << "Problem advancing tick: m_ticksRemaining is zero" << endl;
        }
        m_ticksRemaining--;
    }
    else
    {
        // If there is a customer on the queue,
        // they can go to the window
        if (!office->isEmpty())
        {
            // Get the next student from the Queue
            m_currentCustomer = office->dequeueCustomer();
            m_ticksRemaining = m_currentCustomer->currentStep().waitTicks;
            m_activeCustomer = true;
            // Log the end of the time spent waiting
            // since customer is now at the window
            m_currentCustomer->logDoneTime(office->getType(), curTick);
        }
    }
}


void Window::debug(){
    if (m_activeCustomer){
        m_currentCustomer->debug();
    }
}
