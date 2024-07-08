/*
1a. Rohm Tandon & Anna Harner
1b. ID: 002397105 and ID: 002397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA4
*/

#ifndef WINDOW_H
#define WINDOW_H

#include "Customer.h"
#include "ListQueue.h"

class Office;

class Window
{
public:
    Window();
    virtual ~Window();
    bool isActiveCustomerDone();
    bool hasActiveCustomer();
    void logWindowIdleTime();
    int windowIdleTime();
    Customer *currentCustomer();
    void clearCurrentCustomer();
    void advanceOneTick(Office *office, int curTick);
    void debug();

private:
    bool m_activeCustomer;
    Customer *m_currentCustomer;
    int m_ticksRemaining;
    int m_idleTime;
};
#endif
