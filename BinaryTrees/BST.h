#ifndef BST_H
#define BST_H

#include "TreeNode.h"

template <typename T>
class BST{
    public:
				// lecture 17
        BST();
        virtual ~BST();
        bool iterContains(T d);
        bool contains(T d); // recursive version that uses recContainsHelper
        void printInOrder(); // least to greatest
        void printTreePostOrder(); // left tree then right tree then root
				// lecture 18
        void insert(T d);
        int size();
        T max(); // right most child
        T min(); // left most child
        T median(); // will only work if tree is balanced
        void remove (T d);

    private:
				// lecture 17
        TreeNode<T>* m_root;
        int m_size;
        bool recContainsHelper(TreeNode<T>* n, T d);
        void printIOHelper(TreeNode<T>* n);
        void printTreePostOrderHelper(TreeNode<T>* subTreeRoot);
				// lecture 18
        void insertHelper(TreeNode<T>*& subTreeRoot, T& d);
        T getMaxHelper(TreeNode<T>* n);
        T getMinHelper(TreeNode<T>* n);
        // lecture 19
        void findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent);
        TreeNode<T>* getSuccessor (TreeNode<T>* rightChild);

};



    // ***************************************************************** //
    // ****************** LECTURE  17 ********************************** //
    // ***************************************************************** //


   template <typename T>
        BST<T>::BST(){
        m_root = NULL;
        m_size = 0;
    }

    template <typename T>
    BST<T>::~BST(){
        // TO DO: free up all memory
    }


    // how do we find whether or not a tree contains a key?
        // navigate through the tree until we find it
        // well it's not linear and each node has a left and right child potentially so...

        // let's say we are at the root and we assume the root is not null
        // how do we know if the tree contains "d"?
        // let's try iteratively
    template <typename T>
    bool BST<T>::iterContains(T d){
        if (m_root == NULL){ // tree is empty
            return false;
        }
        if (m_root -> data == d){ // root is the key d
            return true;
        }

        // look for d
        bool found = false;
        TreeNode<T>* current = m_root;
        while (!found){
            // check if d is greater than current go right
            if (d > current -> m_data){
                current = current -> m_right;
            } else { // if d is less than/ == current go left
                current = current -> m_left;
            }
            // check if current node is NULL -> we've reached a leaf and d was not found
            if (current == NULL){
                found =  false;
                break;
            }

            // check if the current node's data is d -> we found d
            if (current -> m_data == d){
                found = true;
            }
        }
        return found;
    }

    // RECURSIVE CONTAINS
    template <typename T>
    bool BST<T>::contains(T d){
        return recContainsHelper(m_root, d);
    }

    // RECURSIVE CONTAINS HELPER
    template <typename T>
    bool BST<T>::recContainsHelper( TreeNode<T>* n, T d){
        if (n == NULL){ // if it is null then d is not in tree
            return false;
        }
        if (n -> m_data == d) { // if it is not null, is it here?
            return true;
        }
        if (d > n -> m_data){ // it's not null but it's also not here, check if it is > or <
            return recContainsHelper( n -> m_right, d);
        } else {
            return recContainsHelper( n -> m_left, d);
        }
    }

    template <typename T>
    void BST<T>::printInOrder(){
        printIOHelper(m_root);
    }

    template <typename T>
    void BST<T>::printIOHelper(TreeNode<T>* n){
        if (n != NULL){ // is the node null?
            printIOHelper(n -> m_left); // if not then print the left thing
            std::cout << n -> m_data << std::endl; // then print the key of the curr node
            printIOHelper(n -> m_right); // then print the right thing
        }
    }


    template <typename T>
    void BST<T>::printTreePostOrder(){
        printTreePostOrderHelper(m_root);
    }

    template <typename T>
    void BST<T>::printTreePostOrderHelper(TreeNode<T>* subTreeRoot){
        if(subTreeRoot != NULL){
            printTreePostOrderHelper(subTreeRoot->m_left);
            printTreePostOrderHelper(subTreeRoot->m_right);
            std::cout << subTreeRoot->m_data << std::endl;
        }
    }

    // ***************************************************************** //
    // ****************** LECTURE  18 ********************************** //
    // ***************************************************************** //

    // INSERT RECURSIVETY
    template <typename T>
    void BST<T>::insert(T d){
        insertHelper(m_root, d);
        ++m_size;

    }
    // INSERT HELPER SO WE DO NOT HAVE TO PASS IN ROOT
    // pass in by reference so that you don't have to manually mess with pointers (r & l children)
    template <typename T>
    void BST<T>::insertHelper(TreeNode<T>*& subTreeRoot, T& d){
        if(subTreeRoot == NULL){
            subTreeRoot =  new TreeNode<T>(d); // insert here  & stop recursive call

        } else if(d > subTreeRoot->m_data){
            insertHelper(subTreeRoot->m_left, d);

        } else{ // Less than or = to so we will have repeats in this tree.
								// Some say duplicates are not allowed in trees but you can alternatively
								// choose whether to put them to left or right as long as you're consistent
            insertHelper(subTreeRoot->m_right, d);
        }
    }

    // HELPER METHODS

    // GET SIZE
    template <typename T>
    int BST<T>::size(){
       return m_size;
    }


    // GET MAX
    template <typename T>
    T BST<T>::max(){
       return getMaxHelper(m_root);
    }

    template <typename T>
    T BST<T>::getMaxHelper(TreeNode<T>* n){
       if(n -> m_right == NULL){
        return n -> m_data;
       } else {
            return getMaxHelper(n -> m_right);
       }

    }

    // GET MIN
    template <typename T>
    T BST<T>::min(){
       return getMinHelper(m_root);
    }

    template <typename T>
    T BST<T>::getMinHelper(TreeNode<T>* n){
       if(n -> m_left == NULL){
            return n -> m_data;
       } else {
            return getMinHelper(n -> m_left);
       }

    }


    // GET MEDIAN - ONTY WORKS IF TREE IS BALANCED!
    template <typename T>
    T BST<T>::median(){
        //check if empty we assume it is a non-empty tree
        return m_root->m_data;
    }

    // ***************************************************************** //
    // ****************** LECTURE  19 ********************************** //
    // ***************************************************************** //

    template <typename T>
    void BST<T>::findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent){
        while (target != NULL && target -> m_data != key){
            parent = target;
            if (key < target -> m_data){
                target = target -> m_left;
            } else {
                target = target -> m_right;
            }
        }
    }

    template <typename T>
    TreeNode<T>* BST<T>::getSuccessor(TreeNode<T>* rightChild){
        while (rightChild -> m_left != NULL){
            rightChild = rightChild -> m_left;
        }
        return rightChild;
    }

    template <typename T>
    void BST<T>::remove(T d){
        // check if empty
        TreeNode<T>* target = NULL;
        TreeNode<T>* parent = NULL;
        target = m_root;

        // find the target
        findTarget(d, target, parent); // no need to save, target is re-defined within the method findTarget

        if (target == NULL){
            // the thing we tried to delete is not in the tree!
            return;
        }
        // check if target is a leaf (including root)
        if (target -> m_left == NULL && target -> m_right == NULL){ // no children, so leaf
            if (target == m_root){
                m_root = NULL;
            } else { // it's a leaf but it's not the root
                if (target == parent -> m_left){
                    parent -> m_left = NULL;
                } else {
                    parent -> m_right = NULL;
                }
            }
            delete target; // free up memory of the target node - calls the destructor of the TreeNode
        }

        // Scenario 3 -> target has two children
        else if (target -> m_left != NULL && target -> m_right != NULL){ // both children are not null
            TreeNode<T>* suc = getSuccessor(target -> m_right);
            T value = suc -> m_data;
            remove(value);  // remove the successor TreeNode
            target -> m_data = value;

        } else { // Scenario 2 -> target has 1 child
            TreeNode<T>* child;
            if (target -> m_left != NULL){ // the child is a left child
                child = target -> m_left;
            } else {                       // the child is a right child
                child = target -> m_right;
            }

            if (target == m_root){
                m_root = child;
            } else {
                if (target == parent -> m_left){ // if our target was the left child of its parent then
                    parent -> m_left = child; // make the parent's new left child the target's child
                } else {
                    parent -> m_right = child;
                }
            }
            delete target;

        }

        -- m_size;

    }





#endif
