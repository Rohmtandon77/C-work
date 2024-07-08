/*
1a. Anna Harner & Rohm Tandon
1b. ID: 002397569 and ID: 002397105
1c. harner@chapman.edu & rtandon@chapman.edu
1d. CPSC 350-03
1e. Assignment 2
*/

#ifndef LazyBST_H
#define LazyBST_H

#include "TreeNode.h"
#include <vector>
using namespace std;

template <typename T>
class LazyBST
{
public:
    // lecture 17
    LazyBST();
    virtual ~LazyBST();
    bool iterContains(T d);
    bool contains(T d);              // recursive version that uses recContainsHelper
    void printInOrder(ofstream &os); // least to greatest
    void printTreePostOrder();
    void printInOrder();
    void printIOHelper(TreeNode<T> *n); // left tree then right tree then root
                                        // lecture 18
    void insert(T d);
    void deleteTree(TreeNode<T> *node);
    int size();
    void rebalance();
    T max();    // right most child
    T min();    // left most child
    T median(); // will only work if tree is balanced
    T get(T d);
    T getHelper(TreeNode<T> *subTreeRoot, TreeNode<T> *newNode);
    // lecture 19
    void remove(T d);
    int getMedian(vector<int> values);
    T createNode(int value, int leftDepth, int rightDepth, TreeNode<T> *node);
    void inorder_traversal(TreeNode<T> *node, T *arr);
    T *to_array();

private:
    // lecture 17
    TreeNode<T> *m_root;
    int m_size;
    bool recContainsHelper(TreeNode<T> *n, T d);
    void printIOHelper(ofstream &os, TreeNode<T> *n);
    void printTreePostOrderHelper(TreeNode<T> *subTreeRoot);
    // lecture 18
    void insertHelper(TreeNode<T> *&subTreeRoot, T &d);
    T getMaxHelper(TreeNode<T> *n);
    T getMinHelper(TreeNode<T> *n);
    // lecture 19
    void findTarget(T key, TreeNode<T> *&target, TreeNode<T> *&parent);
    TreeNode<T> *getSuccessor(TreeNode<T> *rightChild);
    TreeNode<T> *median_rebalance(T *arr, int len);

    int leftHeight;
    int rightHeight;
    int m_arrLen;
};

template <typename T>
LazyBST<T>::LazyBST()
{
    m_root = NULL;
    m_size = 0;
}

template <typename T>
LazyBST<T>::~LazyBST()
{
    // Don't delete
}

// how do we find whether or not a tree contains a key?
// navigate through the tree until we find it
// well it's not linear and each node has a left and right child potentially so...

// let's say we are at the root and we assume the root is not null
// how do we know if the tree contains "d"?
// let's try iteratively
template <typename T>
bool LazyBST<T>::iterContains(T d)
{
    if (m_root == NULL)
    { // tree is empty
        return false;
    }
    if (m_root->data == d)
    { // root is the key d
        return true;
    }

    // look for d
    bool found = false;
    TreeNode<T> *current = m_root;
    while (!found)
    {
        // check if d is greater than current go right
        if (d > current->m_data)
        {
            current = current->m_right;
        }
        else
        { // if d is less than/ == current go left
            current = current->m_left;
        }
        // check if current node is NULL -> we've reached a leaf and d was not found
        if (current == NULL)
        {
            found = false;
            break;
        }

        // check if the current node's data is d -> we found d
        if (current->m_data == d)
        {
            found = true;
        }
    }
    return found;
}

// RECURSIVE CONTAINS
template <typename T>
bool LazyBST<T>::contains(T d)
{
    return recContainsHelper(m_root, d);
}

// RECURSIVE CONTAINS HELPER
template <typename T>
bool LazyBST<T>::recContainsHelper(TreeNode<T> *n, T d)
{
    if (n == NULL)
    { // if it is null then d is not in tree
        return false;
    }
    if (n->m_data == d)
    { // if it is not null, is it here?
        return true;
    }
    if (d > n->m_data)
    { // it's not null but it's also not here, check if it is > or <
        return recContainsHelper(n->m_right, d);
    }
    else
    {
        return recContainsHelper(n->m_left, d);
    }
}

template <typename T>
void LazyBST<T>::printInOrder(ofstream &os)
{
    printIOHelper(os, m_root);
}

template <typename T>
void LazyBST<T>::printIOHelper(ofstream &os, TreeNode<T> *n)
{
    if (n != NULL)
    {                                 // is the node null?
        printIOHelper(os, n->m_left); // if not then print the left thing
        os << *n->m_data << std::endl;
        printIOHelper(os, n->m_right); // then print the right thing
    }
}

template <typename T>
void LazyBST<T>::printInOrder()
{
    printIOHelper(m_root);
}

template <typename T>
void LazyBST<T>::printIOHelper(TreeNode<T> *n)
{
    if (n != NULL)
    {                             // is the node null?
        printIOHelper(n->m_left); // if not then print the left thing
        std::cout << *n->m_data << std::endl;
        printIOHelper(n->m_right); // then print the right thing
    }
}

template <typename T>
void LazyBST<T>::printTreePostOrder()
{
    printTreePostOrderHelper(m_root);
}

template <typename T>
void LazyBST<T>::printTreePostOrderHelper(TreeNode<T> *subTreeRoot)
{
    if (subTreeRoot != NULL)
    {
        printTreePostOrderHelper(subTreeRoot->m_left);
        printTreePostOrderHelper(subTreeRoot->m_right);
        std::cout << subTreeRoot->m_data << std::endl;
    }
}

// INSERT RECURSIVETY
template <typename T>
void LazyBST<T>::insert(T d)
{
    insertHelper(m_root, d);
    ++m_size;
}
// INSERT HELPER SO WE DO NOT HAVE TO PASS IN ROOT
// pass in by reference so that you don't have to manually mess with pointers (r & l children)

template <typename T>
void LazyBST<T>::insertHelper(TreeNode<T> *&subTreeRoot, T &d)
{
    if (subTreeRoot == NULL)
    {
        subTreeRoot = new TreeNode<T>(d); // insert here  & stop recursive call
    }
    else if (*d > *subTreeRoot->m_data)
    {
        insertHelper(subTreeRoot->m_right, d);
    }
    else
    { // Less than or = to so we will have repeats in this tree.
      // Some say duplicates are not allowed in trees but you can alternatively
      // choose whether to put them to left or right as long as you're consistent
        insertHelper(subTreeRoot->m_left, d);
    }
}

// HELPER METHODS

// GET SIZE
template <typename T>
int LazyBST<T>::size()
{
    return m_size;
}

// GET MAX
template <typename T>
T LazyBST<T>::max()
{
    return getMaxHelper(m_root);
}

template <typename T>
T LazyBST<T>::getMaxHelper(TreeNode<T> *n)
{
    if (n->m_right == NULL)
    {
        return n->m_data;
    }
    else
    {
        return getMaxHelper(n->m_right);
    }
}

// GET MIN
template <typename T>
T LazyBST<T>::min()
{
    return getMinHelper(m_root);
}

template <typename T>
T LazyBST<T>::getMinHelper(TreeNode<T> *n)
{
    if (n->m_left == NULL)
    {
        return n->m_data;
    }
    else
    {
        return getMinHelper(n->m_left);
    }
}

// GET MEDIAN - ONTY WORKS IF TREE IS BALANCED!
template <typename T>
T LazyBST<T>::median()
{
    // check if empty we assume it is a non-empty tree
    return m_root->m_data;
}

// HELPER METHODS
template <typename T>
void LazyBST<T>::findTarget(T key, TreeNode<T> *&target, TreeNode<T> *&parent)
{
    // FIND THE NODE WE WANT TO DELETE AND ITS PARENT NODE
    while (target != NULL && target->m_data != key)
    { // while target still has children and it is not our actual target
        parent = target;
        if (key < target->m_data)
        { // if the key is less than the current target node, keep going left
            target = target->m_left;
        }
        else
        {
            target = target->m_right;
        }
    }
}

template <typename T>
TreeNode<T> *LazyBST<T>::getSuccessor(TreeNode<T> *rightChild)
{
    while (rightChild->m_left != NULL)
    { // If the node coming in (rightChild) doesn't have a left child then this is our successor and we're done, else:
        rightChild = rightChild->m_left;
    }
    return rightChild; // not really (necessarily) a right child, this is the successor!
}

template <typename T>
void LazyBST<T>::remove(T d)
{
    // check if tree is empty
    // we assume the tree is non-empty
    TreeNode<T> *target = NULL;
    TreeNode<T> *parent = NULL;
    target = m_root;

    // find the target
    findTarget(d, target, parent); // no need save under any variables, target and parent are redefined bc we passed them in by reference

    // target value was not found - it does not exist in our tree
    if (target == NULL)
    {
        return;
    }

    // SCENARIO 1: TARGET IS A LEAF (INCLUDING ROOT)
    if (target->m_left == NULL && target->m_right == NULL)
    {
        if (target == m_root)
        {
            m_root = NULL;
        }
        else
        { // if it's a leaf but not the root
            // check if target is its parent's left or right child
            if (target == parent->m_left)
            { // if target is a left child
                parent->m_left = NULL;
            }
            else
            { // target is a right child
                parent->m_right = NULL;
            }
        }
        delete target;
        --m_size;
    }

    // SCENARIO 3: TARGET HAS TWO CHILDREN
    else if (target->m_left != NULL && target->m_right != NULL)
    { // both children pointers are not null
        TreeNode<T> *suc = getSuccessor(target->m_right);
        T value = suc->m_data;
        remove(value); // goes in the LazyBST remove method and removes the node w/ d = value
        target->m_data = value;
    }

    // SCENARIO 2: TARGET HAS 1 CHILD
    else
    {
        TreeNode<T> *child;
        // check whether target has a left or right child
        if (target->m_left != NULL)
        { // target has a left child
            child = target->m_left;
        }
        else
        { // target has a right child
            child = target->m_right;
        }

        if (target == m_root)
        {
            m_root = child;
        }
        else
        {
            if (target == parent->m_left)
            {                           // our target is a left child
                parent->m_left = child; // make the parent's left child the target's child
            }
            else
            {                            // our target is a right child
                parent->m_right = child; // make the parent's right child the target's child
            }
        }
        delete target;
        --m_size;
    }
}

template <typename T>
T LazyBST<T>::get(T d)
{
    TreeNode<T> *newNode = new TreeNode<T>(d);
    return getHelper(m_root, newNode);
}

template <typename T>
T LazyBST<T>::getHelper(TreeNode<T> *subTreeRoot, TreeNode<T> *newNode)
{
    if (subTreeRoot != NULL)
    {
        if (*newNode->m_data == *subTreeRoot->m_data)
        {
            return subTreeRoot->m_data;
        }
        else if (*newNode->m_data < *subTreeRoot->m_data)
        {
            return getHelper(subTreeRoot->m_left, newNode);
        }
        else
        {
            return getHelper(subTreeRoot->m_right, newNode);
        }
    }
    else
    {
        return NULL;
    }
}

/*
// template <typename T>
// int LazyBST<T>::LazyBSTHeight(TreeNode<T>* node) {
//     if (node == NULL) {
//         return -1;
//     }
//     leftHeight = LazyBSTHeight(node->left);
//     rightHeight = LazyBSTHeight(node->right);
//     return 1 + max(leftHeight, rightHeight);
// }
*/

template <typename T>
void LazyBST<T>::deleteTree(TreeNode<T> *node)
{
    if (node != NULL)
    {
        deleteTree(node->m_left);
        deleteTree(node->m_right);
        delete node;
    }
}

template <typename T>
void LazyBST<T>::inorder_traversal(TreeNode<T> *node, T *arr)
{
    if (node != nullptr)
    {
        inorder_traversal(node->m_left, arr);
        arr[m_arrLen++] = node->m_data;
        inorder_traversal(node->m_right, arr);
    }
}

template <typename T>
T *LazyBST<T>::to_array()
{
    m_arrLen = 0; // use this to build the array
    T *arr = new T[m_size];
    inorder_traversal(m_root, arr);
    return arr;
}

template <typename T>
void LazyBST<T>::rebalance()
{
    auto arr = to_array();
    auto root_val = m_root->m_data;
    // find the location of the root
    int indx = 0;
    for (; indx < m_size; indx++)
    {
        if (arr[indx] == root_val)
            break;
    }
    float left_size = indx;
    float right_size = m_size - indx - 1;
    float m = (left_size < right_size) ? left_size : right_size;
    float M = (left_size > right_size) ? left_size : right_size;
    if ((m > 0 && M / m >= 1.5) || (m == 0 && M >= 2))
    {
        // deleteTree(m_root);
        m_root = median_rebalance(arr, m_size);
    }
    delete[] arr;
}

template <typename T>
TreeNode<T> *LazyBST<T>::median_rebalance(T *arr, int len)
{
    if (len <= 0)
    {
        return NULL;
    }
    int mid = len / 2;
    TreeNode<T> *root = new TreeNode<T>(arr[mid]);
    root->m_left = median_rebalance(arr, mid);
    root->m_right = median_rebalance(arr + mid + 1, len - mid - 1);
    return root;
}

#endif