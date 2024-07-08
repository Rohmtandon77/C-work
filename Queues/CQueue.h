// circular queue implementation
#ifndef CQueue_H
#define CQueue_H
#include <iostream>

template<typename T>
class CQueue{
    public:
        CQueue(int s);
        virtual ~CQueue();
        void add(T data); //add to the back
        T remove(); //remove from the front
        T peek();
        bool isEmpty();
        bool isFull();
        int size();

    private:
        int maxSize;
        int front;
        int back;
        T* arr; //where data is stored
        int count;

};

template<typename T>
CQueue<T>::CQueue(int s){
    maxSize = s;
    front = 0;
    back = -1;
    count = 0;
    arr = new T[maxSize];
}

template<typename T>
CQueue<T>::~CQueue(){
    std::cout << "I'm freeing up memory!" << std::endl;
    delete[] arr;
}

template<typename T>
bool CQueue<T>::isFull(){
    return (count == maxSize);
}

template<typename T>
bool CQueue<T>::isEmpty(){
    return (count == 0);
}

template<typename T>
int CQueue<T>::size(){
    return count;
}

template<typename T>
void CQueue<T>::add(T data){
    if(back == maxSize - 1){
        back = -1;
    }
    arr[++back] = data;
    ++count;
}

template<typename T>
T CQueue<T>::remove(){
    T ret = arr[front];
    ++front;
    --count;
    if(front == maxSize){
        front = 0;
    }
    return ret;
}

template<typename T>
T CQueue<T>::peek(){
    T ret = arr[front];
    return ret;
}

#endif
