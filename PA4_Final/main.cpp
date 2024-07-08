/*
1a. Rohm Tandon & Anna Harner
1b. ID: 002397105 and ID: 002397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA4
*/

#include "ServiceCenter.h"
#include "DblList.h"
#include "ListNode.h"
#include "ListQueue.h"
#include "Customer.h"
#include "Office.h"
#include "Window.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

// as a customer comes in, you see the first office they need to go to and send them to that office's queue

int main(int argc, char *argv[]){
    ServiceCenter sc;
    // Load the input file and set the intial state
    sc.loadInitialState(argv[1]);
    sc.processUntilDone();
    sc.processCustomerStats();
    sc.processWindowStats();
    return 0;
}
