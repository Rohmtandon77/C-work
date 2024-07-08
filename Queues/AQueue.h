#ifndef AQUEUE_H
#define AQUEUE_H
using namespace std;

template <typename T>
class AQueue{
  public:
    AQueue(int s);
    ~AQueue();
    void add(T data); // add to the back of the queue
    T remove(); // remove from the front of the queue
    T peek(); // look at front of the queue
    bool isEmpty();
    bool isFull();
    int size(); // how many elements we actually have in the queue

  private:
    int maxSize;
    int front;
    int back;
    int count; // how many elements we actually have
    T *arr; // where the data will be stored

};

template <typename T>
AQueue<T>::AQueue(int s){
  maxSize=s;
  front = 0;
  back = -1;
  count =0;
  arr = new T[maxSize];
}

template<typename T>
AQueue<T>::~AQueue(){
  delete[] arr;
}

template<typename T>
bool AQueue<T>::isFull(){
  return(count ==maxSize);
}

template<typename T>
bool AQueue<T>::isEmpty(){
  return(count ==0);
}

template<typename T>
int AQueue<T>::size(){
  return count;
}

template<typename T>
void AQueue<T>::add(T data){
  arr[++back]= data;
  ++count;
}

template<typename T>
T AQueue<T>::remove(){
  T ret = arr[front];
  ++front;
  --count;
  return ret;
}

template<typename T>
T AQueue<T>::peek(){
  T ret = arr[front];
  return ret;
}

#endif
