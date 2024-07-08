#include <iostream>
#include "AQueue.h"

using namespace std;

int main(){
  AQueue<char>* theQ = new AQueue<char>(10); // in the heap
  theQ -> add('P');
  theQ -> add('e');
  theQ -> add('t');
  theQ -> add('e');

  cout<< theQ -> size() << endl;

  while(!theQ-> isEmpty()){
    cout<< theQ->remove()<<" ";
  }

  cout<< endl;
  cout<< theQ->size()<<endl;


  return 0;
}
