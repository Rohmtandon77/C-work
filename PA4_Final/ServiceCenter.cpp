/*
1a. Rohm Tandon & Anna Harner
1b. ID: 002397105 and ID: 002397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA4
*/

#include <iostream>
#include "ServiceCenter.h"
#include "DblList.h"
#include "ListNode.h"
#include "ListQueue.h"
#include "Customer.h"
#include "Office.h"
#include "Window.h"
#include <string>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <fstream>
using namespace std;

// constructor
ServiceCenter::ServiceCenter() : m_Registrar(NULL),
                                 m_FinancialAid(NULL),
                                 m_Cashier(NULL),
                                 m_RegW(0),
                                 m_CashW(0),
                                 m_FinW(0),
                                 m_clock(0)
{
}

ServiceCenter::~ServiceCenter(){
    delete m_Registrar;
    delete m_FinancialAid;
    delete m_Cashier;
}

void ServiceCenter::loadInitialState(string input_file){
    ifstream fin;
    string currentLine;
    // Open input file
    //    fin.open(inpFile[1], ios::in);
    fin.open(input_file);
    if (!fin.is_open())
    {
        cout << "File could not be opened" << endl;
        return;
    }

    // Initialize string
    // Determine what line the reader object is on
    int count = 1;
    int lineValue = -1;

    // Loop over the parameters to set up offices
    while (getline(fin, currentLine)){
        if (count == 1){ // Read the # of windows opened at registrar
            lineValue = stoi(currentLine);
            m_RegW = lineValue;
            ++count;
        }
        else if (count == 2){ // Read the # of windows opened at cashier
            lineValue = stoi(currentLine);
            m_CashW = lineValue;
            ++count;
        }
        else if (count == 3){ // Read the # of windows opened at financial aid
            lineValue = stoi(currentLine);
            m_FinW = lineValue;
            m_Registrar = new Office('R', m_RegW);
            m_FinancialAid = new Office('F', m_FinW);
            m_Cashier = new Office('C', m_CashW);
            break;
        }
    }
    // Once offices are set up, start reading ticks
    bool nextNumCust = false;
    int NumCust = 0;
    int arrivalTick = 0;
    int waitTimes[3];
    while (getline(fin, currentLine)){
        if (currentLine == "END"){
            break;
        }
        else if (nextNumCust){ // Get the number of students at the clock value
            lineValue = stoi(currentLine);
            NumCust = lineValue;
            nextNumCust = false;
        }
        else if (NumCust > 0){ // Process the customer
            Customer *newCust = new Customer(arrivalTick);
            int i = 0;

            // Parse 3 numbers and three chars
            char *p = strtok((char *)currentLine.c_str(), " ");

            while (p != NULL){
                if (i < 3){
                    waitTimes[i] = stoi(p);
                }
                else{
                    char v = *p;
                    RouteStep step;
                    step.office = *p;
                    step.waitTicks = waitTimes[i - 3];
                    newCust->addRouteStep(step);
                }
                p = strtok(NULL, " ");
                i++;
            }
            m_arrivalQueue.add(newCust);
            // Decrement each time we read a Customer
            --NumCust;
        }
        else{
            lineValue = stoi(currentLine);
            arrivalTick = lineValue;
            cout << "Arrival tick " << arrivalTick << endl;
            nextNumCust = true;
        }
    }
    // Done processing the file
    cout << "Done processing file" << endl
         << endl;
    fin.close();
}

void ServiceCenter::enqueueNewArrivals(int curTick){
    // for the current timestamp, add customers arriving
    // since that timestamp
    while (!m_arrivalQueue.isEmpty() &&
           m_arrivalQueue.peek()->enterTick() <= curTick)
    {
        enqueueCustomerToOffice(m_arrivalQueue.remove(), curTick);
    }
}

void ServiceCenter::enqueueCustomerToOffice(Customer *cust, int curTick){
    // Advance to the first window
    auto step = cust->prepareToAdvance();
    // If the wait is zero for an office, no need to wait
    if (step.waitTicks == 0){
        return;
    }
    // Add new Customer to next office
    switch (step.office){
    case 'R':
        cust->logQueueTime('R', curTick);
        m_Registrar->enqueueCustomer(cust);
        break;
    case 'F':
        cust->logQueueTime('F', curTick);
        m_FinancialAid->enqueueCustomer(cust);
        break;
    default:
        cust->logQueueTime('C', curTick);
        m_Cashier->enqueueCustomer(cust);
    }
}

void ServiceCenter::processWindow(Office *office, int curTick){
    for (int i = 0; i < office->numWindows(); i++){
        office->logWindowIdleTime(i);
        if (office->doneAtWindow(i)){
            auto cust = office->clearCustomerAtWindow(i);
            if (!cust->finishedRouted()){
                enqueueCustomerToOffice(cust, curTick);
            }
            else{
                m_exitQueue.add(cust);
            }
        }
    }
}

void ServiceCenter::advanceOneTick(int curTick){
    m_Cashier->advanceOneTick(curTick);
    m_FinancialAid->advanceOneTick(curTick);
    m_Registrar->advanceOneTick(curTick);
}


void ServiceCenter::printState(){
    m_Cashier->debug();
    m_FinancialAid->debug();
    m_Registrar->debug();
}

// Process customers through the queues until done
void ServiceCenter::processUntilDone(){
    while (true){
        cout << "Running tick " << m_clock << endl;
        printState();
        // Add new arrivals to the queue behind currently queued customers
        enqueueNewArrivals(m_clock);
        // Move currently queued to the windows
        advanceOneTick(m_clock);
        // Process is alphabetical order
        processWindow(m_Cashier, m_clock);
        processWindow(m_FinancialAid, m_clock);
        processWindow(m_Registrar, m_clock);
        // Check if we're done; this means no waiting arrivals
        // and nobody at any of the windows
        bool allDone = m_Registrar->allCustomersProcessed() &&
                       m_FinancialAid->allCustomersProcessed() &&
                       m_Cashier->allCustomersProcessed() &&
                       m_arrivalQueue.isEmpty();
        if (allDone){
            break;
        }
        m_clock++;
    }
}

void ServiceCenter::processCustomerStats(){
    const int C = 0, F = 1, R = 2;
    int numVisits[] = {0, 0, 0};
    int sumTicks[] = {0, 0, 0};
    int longestPerOffice[] = {0, 0, 0};
    int longWaits = 0;
    while (!m_exitQueue.isEmpty()){
        Customer *cust = m_exitQueue.remove();
        int totalTime = 0;
        // Accumulate wait times at each office
        int t = cust->getTimeAtOffice('C');
        numVisits[C]++;
        if (t > 0){
            sumTicks[C] += t;
            totalTime += t;
            if (t > longestPerOffice[C]){
                longestPerOffice[C] = t;
            }
        }
        t = cust->getTimeAtOffice('F');
        numVisits[F]++;
        if (t > 0){
            sumTicks[F] += t;
            totalTime += t;
            if (t > longestPerOffice[F]){
                longestPerOffice[F] = t;
            }
        }
        t = cust->getTimeAtOffice('R');
        numVisits[R]++;
        if (t > 0){
            sumTicks[R] += t;
            totalTime += t;
            if (t > longestPerOffice[R]){
                longestPerOffice[R] = t;
            }
        }
        // Accumulate the number of students waiting over 10 minutes
        // total across all offices.
        if (totalTime > 10){
            longWaits++;
        }
        // Release the Customers
        delete cust;
    }

    // And report the results
    cout << "Mean Student wait for Cashier " << float(sumTicks[C]) / numVisits[C] << endl;
    cout << "Mean Student  wait for Financial Aid " << float(sumTicks[F]) / numVisits[F] << endl;
    cout << "Mean Student wait for Registrar " << float(sumTicks[R]) / numVisits[R] << endl;
    cout << endl;
    cout << "Longest Student wait for Cashier " << longestPerOffice[C] << endl;
    cout << "Longest Student wait for Financial Aid " << longestPerOffice[F] << endl;
    cout << "Longest Student wait for Registrar " << longestPerOffice[R] << endl;
    cout << endl;
    cout << "Students waiting over 10 min " << longWaits << endl;
}

int ServiceCenter::windowStatsForOffice(Office *office){
    int idleTimeAcc = 0;
    int longestItemTime = 0;
    int longThanFive = 0;
    for (int i = 0; i < office->numWindows(); i++){
        int idleTime = office->windowIdleTime(i);
        if (idleTime > 5){
            longThanFive++;
        }
        if (idleTime > longestItemTime){
            longestItemTime = idleTime;
        }
        idleTimeAcc += idleTime;
    }
    cout << "    Mean idle time " << idleTimeAcc / office->numWindows() << endl;
    cout << "    Longest idle time " << longestItemTime << endl;
    cout << endl;
    return longThanFive;
}

void ServiceCenter::processWindowStats(){
    int longThanFive = 0;
    cout << "Stats for Office Cashier" << endl;
    longThanFive += windowStatsForOffice(m_Cashier);

    cout << "Stats for Office Financial Aid" << endl;
    longThanFive += windowStatsForOffice(m_FinancialAid);

    cout << "Stats for Office Registrar" << endl;
    longThanFive += windowStatsForOffice(m_Registrar);

    cout << "Number of windows idle for over 5 minutes: "
         << longThanFive << endl;
}
