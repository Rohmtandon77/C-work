/*
1a. Rohm Tandon & Anna Harner
1b. ID: 002397105 and ID: 002397569
1c. rtandon@chapman.edu & harner@chapman.edu
1d. CPSC 350-03
1e. PA4
*/

#ifndef LIST_NODE_H
#define LIST_NODE_H
#include <cstdlib>

template<typename T>
class ListNode{
    public:
    ListNode(T data);
    virtual ~ListNode();
    T m_data;
    ListNode<T>* m_next; //recursive data structure b/c it points to instances of itself
    ListNode<T>* m_prev;
};

template<typename T>
ListNode<T>::ListNode(T data){
    m_data = data;
    m_next = NULL;
    m_prev = NULL;
}

template<typename T>
ListNode<T>::~ListNode(){
    m_next = NULL;
    m_prev = NULL;
}

#endif
