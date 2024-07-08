#ifndef LISTQUEUE_H
#define LISTQUEUE_H

template <typename T>
class ListQueue{
  public:
    ListQueue(int s);
    ~ListQueue();
    void add(T data); // add to the back of the queue
    T remove(); // remove from the front of the queue
    T peek(); // look at front of the queue
    bool isEmpty();
    int size(); // how many elements we actually have in the queue

  private:
    int front;
    int back;
    int count; // how many elements we actually have
    T *arr; // where the data will be stored

};

template <typename T>
ListQueue<T>::ListQueue(){
  front = 0;
  back = -1;
  count =0;
  ll = new T[];
}

template<typename T>
ListQueue<T>::~ListQueue(){
  delete[] ll;
}
