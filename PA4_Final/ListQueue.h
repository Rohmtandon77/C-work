/*
1a. Rohm Tandon & Anna Harner
1b. ID: 002397105 and ID: 002397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA4
*/

#ifndef ListQueue_H
#define ListQueue_H
#include <iostream>
#include "DblList.h"

template<typename T>
class ListQueue{
    public:
        ListQueue();
        virtual ~ListQueue();
        void add(T data); //add to the back
        T remove(); //remove from the front
        T peek();
        bool isEmpty();
        int size();

    private:
        DblList<T>* m_list;

};

template<typename T>
ListQueue<T>::ListQueue(){
    m_list = new DblList<T>();
}

template<typename T>
ListQueue<T>::~ListQueue(){
    delete m_list;
}

template<typename T>
bool ListQueue<T>::isEmpty(){
    return (m_list->size() == 0);
}

template<typename T>
int ListQueue<T>::size(){
    return m_list->size();;
}

template<typename T>
void ListQueue<T>::add(T data){
    m_list->addBack(data);
}

template<typename T>
T ListQueue<T>::remove(){
    return m_list->removeFront();
}

template<typename T>
T ListQueue<T>::peek(){
    return m_list-> get(0);
}

#endif
