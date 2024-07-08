/*
1a. Rohm Tandon & Anna Harner
1b. ID: 002397105 and ID: 002397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA4
*/

#include "Customer.h"
using namespace std;
#include <iostream>

const int C = 0, F = 1, R = 2;

Customer::Customer() : m_enterTick(0){
}

Customer::Customer(int enterTick) : m_enterTick(enterTick){
}

Customer::~Customer() {}

int Customer::enterTick(){
    return m_enterTick;
}

void Customer::addRouteStep(RouteStep step){
    m_route.add(step);
}

bool Customer::finishedRouted(){
    return m_route.isEmpty();
}

RouteStep Customer::prepareToAdvance(){
    m_curStep = m_route.remove();
    return m_curStep;
}

RouteStep Customer::currentStep(){
    return m_curStep;
}

void Customer::logQueueTime(char office, int tick){
    switch (office){
    case 'R':
        m_queueTickCFR[R] = tick;
        break;
    case 'F':
        m_queueTickCFR[F] = tick;
        break;
    default:
        m_queueTickCFR[C] = tick;
    }
}

void Customer::logDoneTime(char office, int tick){
    switch (office){
    case 'R':
        m_doneTickCFR[R] = tick;
        break;
    case 'F':
        m_doneTickCFR[F] = tick;
        break;
    default:
        m_doneTickCFR[C] = tick;
    }
}

int Customer::getTimeAtOffice(char office){
    int waitTime = -1;
    switch (office){
    case 'R':
        waitTime = m_doneTickCFR[R] - m_queueTickCFR[R];
        break;
    case 'F':
        waitTime = m_doneTickCFR[F] - m_queueTickCFR[F];
        break;
    default:
        waitTime = m_doneTickCFR[C] - m_queueTickCFR[C];
    }
    return waitTime;
}

void debug_step(RouteStep step){
}

void Customer::debug(){
    debug_step(m_curStep);
    if (!m_route.isEmpty()){
      debug_step(m_route.peek());
    }
}
