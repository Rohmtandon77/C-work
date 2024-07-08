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
        // lecture 19
        void remove (T d);
        int LdepthTrack(T node);
        int RdepthTrack(T node);
        int BSTHeight(T node);
        void rebuild();
        T LBtoArr(T node);
        T LeftMedianInsert(T Arr);
        T RightMedianInsert(T Arr);
        T FinMedianInsert();
        T BSTtoArray(Node *root,int A[]);
        T BSTtoArraySort();

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
            insertHelper(subTreeRoot->m_right, d);

        } else{ // Less than or = to so we will have repeats in this tree.
								// Some say duplicates are not allowed in trees but you can alternatively
								// choose whether to put them to left or right as long as you're consistent
            insertHelper(subTreeRoot->m_left, d);
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

    // HELPER METHODS
    template <typename T>
    void BST<T>::findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent){
        // FIND THE NODE WE WANT TO DELETE AND ITS PARENT NODE
        while (target != NULL && target -> m_data != key){ // while target still has children and it is not our actual target
            parent = target;
            if (key < target -> m_data){ // if the key is less than the current target node, keep going left
                target = target -> m_left;
            } else {
                target = target -> m_right;
            }
        }
    }

    template <typename T>
    TreeNode<T>* BST<T>::getSuccessor (TreeNode<T>* rightChild){
        while (rightChild -> m_left != NULL){ // If the node coming in (rightChild) doesn't have a left child then this is our successor and we're done, else:
            rightChild = rightChild -> m_left;
        }
        return rightChild; // not really (necessarily) a right child, this is the successor!
    }

    template <typename T>
    void BST<T>::remove(T d){
        // check if tree is empty
        // we assume the tree is non-empty
        TreeNode<T>* target = NULL;
        TreeNode<T>* parent = NULL;
        target = m_root;

        // find the target
        findTarget(d, target, parent); // no need save under any variables, target and parent are redefined bc we passed them in by reference

        // target value was not found - it does not exist in our tree
        if (target == NULL){
            return;
        }

        // SCENARIO 1: TARGET IS A LEAF (INCLUDING ROOT)
        if (target -> m_left == NULL && target -> m_right == NULL){
            if (target == m_root){
                m_root = NULL;
            } else { // if it's a leaf but not the root
                // check if target is its parent's left or right child
                if (target == parent -> m_left){ // if target is a left child
                    parent -> m_left = NULL;
                } else { // target is a right child
                    parent -> m_right = NULL;
                }
            }
            delete target;
						-- m_size;
        }

        // SCENARIO 3: TARGET HAS TWO CHILDREN
        else if (target -> m_left != NULL && target -> m_right != NULL){  // both children pointers are not null
            TreeNode<T>* suc = getSuccessor(target -> m_right);
            T value = suc -> m_data;
            remove(value); // goes in the BST remove method and removes the node w/ d = value
            target -> m_data = value;
        }

        // SCENARIO 2: TARGET HAS 1 CHILD
        else {
            TreeNode<T>* child;
            // check whether target has a left or right child
            if (target -> m_left != NULL){ // target has a left child
                child = target -> m_left;
            } else{                        // target has a right child
                child = target -> m_right;
            }

            if (target == m_root){
                m_root = child;
            } else {
                if (target == parent -> left){ // our target is a left child
                    parent -> m_left = child; // make the parent's left child the target's child
                } else {                       // our target is a right child
                    parent -> m_right = child; // make the parent's right child the target's child
                }
            }
            delete target;
						-- m_size;
        }

    }
    template <typename T>
    int BST<T>::BSTHeight(T node) {
        if (node is null) {
            return -1;
        }
        leftHeight = BSTHeight(TreeNode<T>* node->left);
        rightHeight = BSTHeight(node->right);
        return 1 + max(leftHeight, rightHeight);
    }

    template <typename T>
    int BST<T>::LdepthTrack(T node) {
        int leftTrack=BSTHeight(TreeNode->m_left);
        return leftTrack;
    }

    template <typename T>
    int BST<T>::RdepthTrack(T node) {
        int rightTrack=BSTHeight(TreeNode->m_right);
        return rightTrack;
    }

    template <typename T>
    T BST<T>::rebuild(T node){
        int Arr[]= BSTtoArraySort();
        // uses both leftmedianinsert and right to run recursively through all parts of the array


    }


    template <typename T>
    T BST<T>::FinMedianInsert(){

    }


    template <typename T>
    T BSTtoArray(Node *root, int A[]){
      int pos = 0;
      if(root == NULL) {
        return;
      }

      BSTtoArray(root->left, A);
      A[pos++] = root->data;
      BSTtoArray(root->right, A);
      return A;
    }

    template <typename T>
    T BST<T>::BSTtoArraySort(){
      int N = m_size;
      int Arr[N]=BSTtoArray(Node *root, int A[]);
      for(int i=0;i<N;i++){
        for(int j=i+1; j<N;j++){
          if(Arr[i]>Arr[j]){
            int c=Arr[i];
            Arr[i]=Arr[j];
            Arr[j]=c;
          }
        }
      }
      return Arr;
    }

    template <typename T>
    T BST<T>::LeftMedianInsert(T Arr){
        N=Arr.size();
        if(Array==NULL){
            return 0;
        }
        else if(N%2==0){
            int median=Arr[N/2];
        }
        else{
            int median = Arr[(N-1)/2];
        }
        NewTree.insert(median);
        if (NewTree.size()==0){
            NewTree->m_root=median;
        }
        //maybe put an else statement that sets it as the left child of the previous node
        int NewArr[N/2]={};
        for (int i=0; i<N/2;i++){
            NewArr[i]=Arr[i];
        }
        return LeftMedianInsert(NewArr);

    }

    template <typename T>
    T BST<T>::RightMedianInsert(T Arr){
        N=Arr.size();
        if(Array==NULL){
            return 0;
        }
        int medPos =floor(N/2); //position of the median
        int median = Arr[medPos];
        NewTree.insert(median);
        if (NewTree.size()==0){
            NewTree->m_root=median;
        }
        // maybe put an else statement that sets it as the right child of the previous node
        int NewArr[]={};
        for (int i=medPos; i<N;i++){
            NewArr[i]=Arr[i];
        }
        // Needs to be recalled with this new array
        return RightMedianInsert(NewArr);

    }




#endif
