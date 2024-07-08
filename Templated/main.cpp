#include "TStack.h"
#include <iostream>
#include <string>
using namespace std;

int main(){
    // statically allocated
    TStack<int> myStackInt(10);
    myStackInt.push(2);
    myStackInt.push(4);
    myStackInt.push(6);
    myStackInt.push(8);
    myStackInt.push(10);

    TStack<string> myStackString(10);
    myStackString.push("sense?");
    myStackString.push("make");
    myStackString.push("this");
    myStackString.push("does");

    cout << "printing contents of myStackInt:" << endl;
    while(!myStackInt.isEmpty()){
            cout << myStackInt.pop() << endl;
    }
    cout << "printing contents of myStackString:" << endl;
    while(!myStackString.isEmpty()){
            cout << myStackString.pop() << endl;
    }

    // dynamically allocated
    TStack<int>* heapIntStack = new TStack<int>(10);
    heapIntStack -> push(12345);
    cout << heapIntStack -> pop() << endl;
    cout << "delete heapIntStack" << endl;
    delete heapIntStack;

    TStack<string>* heapStrStack = new TStack<string>(10);
    heapStrStack -> push("heappppp");
    cout << heapStrStack -> pop() << endl;
    cout << "delete heapStrStack" << endl;
    delete heapStrStack;

    cout << "clear call stack " << endl;


    return 0;
}
