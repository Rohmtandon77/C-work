/*
1a. Rohm Tandon & Anna Harner
1b. ID: 002397105 and ID: 002397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA4
*/

#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <cstdlib>
#include "ListQueue.h"

struct RouteStep{
    char office;
    int waitTicks;
};

class Customer{
public:
    Customer(int enterTick);
    ~Customer();

    // Add a step to the route queue
    void addRouteStep(RouteStep step);

    // Whether the route is finished
    bool finishedRouted();

    // Prepare to advance to the next window
    RouteStep prepareToAdvance();

    // Window there the customer came frame
    RouteStep currentStep();

    // When the customer arrived
    int enterTick();

    // Log the time the customer was queued to an office
    void logQueueTime(char office, int tick);

    // Log the time the customer finished at an office
    void logDoneTime(char office, int tick);

    // Get time time at office
    int getTimeAtOffice(char office);

    void debug();

private:
    Customer();
    int m_enterTick;
    RouteStep m_curStep;
    ListQueue<RouteStep> m_route;
    int m_queueTickCFR[3];
    int m_doneTickCFR[3];
};

#endif
