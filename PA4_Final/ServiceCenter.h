/*
1a. Rohm Tandon & Anna Harner
1b. ID: 002397105 and ID: 002397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA4
*/

#ifndef SERVICECENTER_H
#define SERVICECENTER_H
#include <iostream>
#include <string>
#include "ListQueue.h"
#include "Customer.h"
#include "Window.h"
#include "Office.h"
using namespace std;

class ServiceCenter
{
public:
  ServiceCenter();
  ~ServiceCenter();

  // Main methods
  void loadInitialState(string input_file);
  void processUntilDone();

  // Analytics methods
  void processCustomerStats();
  void processWindowStats();

private:
  // Some diagnostic functions
  void printState();
  void enqueueCustomerToOffice(Customer *cust, int curTick);
  void enqueueNewArrivals(int curTick);
  void processWindow(Office *office, int curTick);
  int windowStatsForOffice(Office *office);

  void advanceOneTick(int curTick);
  int m_RegW;
  int m_CashW;
  int m_FinW;
  int m_clock;
  Office *m_Registrar;
  Office *m_FinancialAid;
  Office *m_Cashier;
  ListQueue<Customer *> m_arrivalQueue;
  ListQueue<Customer *> m_exitQueue;
};

#endif

// within overloaded constructor intialize the list queues, windows array, customers array, and member variables and read the file
//
