#ifndef MonoStack_H
#define MonoStack_H
#include <iostream>
template <typename T>
class MonoStack{
    public:
        MonoStack(int iSize, char o);
        ~MonoStack();
        void push(T c); //add to the top
        T pop(); //remove from the top
        T peek(); //return the top without removing
        bool isFull();
        bool isEmpty();
        int size();

    private:
        T* stackArr;
        int count; //number of items currently in the stack
        int maxSize; //max number of things in the stack
        int top; //index of the current top of the stack
};

template <typename T>
MonoStack<T>::MonoStack(int iSize, char o){
    stackArr = new T[iSize];
    maxSize = iSize;
    count = 0;
    top = -1;
}

template <typename T>
MonoStack<T>::~MonoStack(){
    std::cout << "deleting stackArr! " << std::endl;
     delete[] stackArr;
}

template <typename T>
bool MonoStack<T>::isFull(){
    return (count == maxSize);
}

template <typename T>
bool MonoStack<T>::isEmpty(){
    return (count == 0);
}

template <typename T>
int MonoStack<T>::size(){
    return count;
}

template <typename T>
void MonoStack<T>::push(T c){
    if(isFull()){
        T* temp = new T[2*maxSize];
        for(int i = 0; i < maxSize; ++i){
            temp[i] = stackArr[i];
        }
        maxSize *= 2;
        delete[] stackArr;
        stackArr = temp;
    }
    stackArr[++top] = c;
    ++count;
}

template <typename T>
T MonoStack<T>::pop(){
    --count;
    return stackArr[top--];
}

template <typename T>
T MonoStack<T>::peek(){
    return stackArr[top];
}

#endif
