/*
1a. Anna Harner & Rohm Tandon
1b. ID: 002397569 and ID: 002397105
1c. harner@chapman.edu & rtandon@chapman.edu
1d. CPSC 350-03
1e. Assignment 2
*/

#ifndef TREE_NODE_H
#define TREE_NODE_H

#include <cstdlib>
#include <iostream>
using namespace std;

template <typename T>
class TreeNode
{
public:
  TreeNode();
  TreeNode(T d);
  virtual ~TreeNode();
  T getData();

  template <typename S>
  friend class BST;

  // private:
  T m_data;
  TreeNode<T> *m_left;
  TreeNode<T> *m_right;
};

template <typename T>
TreeNode<T>::TreeNode() : m_left(NULL), m_right(NULL)
{
}

template <typename T>
TreeNode<T>::TreeNode(T d) : m_left(NULL), m_right(NULL)
{
  m_data = d;
  m_left = NULL;
  m_right = NULL;
}

template <typename T>
TreeNode<T>::~TreeNode()
{
  if (m_left != NULL)
  {
    delete m_left;
  }
  if (m_right != NULL)
  {
    delete m_right;
  }
}

template <typename T>
T TreeNode<T>::getData()
{
  return m_data;
}

#endif