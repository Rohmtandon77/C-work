#ifndef SCAPEGOATST_H
#define SCAPEGOATST_H
#include "TreeNode.h"
#include "Dbllist.h"
template <typename T>
class ScapegoatST{
public:
  ScapegoatST();
  virtual ~ScapegoatST();
  int getSize();
  void insert(T d);
  void remove(T d);
  bool contains(T d);
  void printTreeInOrder();
  void printTreePostOrder();
  T getMin();
  T getMax();
  T getMedian();
  T get(T d);
private:
  int m_size;
  TreeNode<T>* m_root;
  int getSizeFromNode(TreeNode<T>* subTreeRoot);
  int insertFindDepth(TreeNode<T>* newNode);
  int convertToList(TreeNode<T>* currNode, DblList<TreeNode<T>*>* nodeList, int index);
  void rebuildSubTree(TreeNode<T>* subTreeRoot);
  TreeNode<T>* buildBalancedTree(DblList<TreeNode<T>*>* nodeList, int index, int subTreeSize);
  double log3over2(int Val);
  T getMinHelper(TreeNode<T>* subTreeRoot);
  T getMaxHelper(TreeNode<T>* subTreeRoot);
  bool containsHelper(TreeNode<T>* subTreeRoot, TreeNode<T>* newNode);
  T getHelper(TreeNode<T>* subTreeRoot, TreeNode<T>* newNode);
  void printTreeInOrderHelper(TreeNode<T>* subTreeRoot);
  void printTreePostOrderHelper(TreeNode<T>* subTreeRoot);
  void findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent);
  TreeNode<T>* getSuccessor(TreeNode<T>* rightChild);
};
template <typename T>
ScapegoatST<T>::ScapegoatST(){
  m_root = NULL;
  m_size = 0;
}
template <typename T>
ScapegoatST<T>::~ScapegoatST(){
  if(m_root != NULL){
    delete m_root;
  }
}
template <typename T>
int ScapegoatST<T>::getSize(){
  return m_size;
}
template <typename T>
int ScapegoatST<T>::getSizeFromNode(TreeNode<T>* subTreeRoot) {
  if(subTreeRoot == NULL) {
    return 0;
  } else {
    return (getSizeFromNode(subTreeRoot->m_left) + 1 + getSizeFromNode(subTreeRoot->m_right));
  }
}
template <typename T>
double ScapegoatST<T>::log3over2(int val) {
  return log2(val) / log2(1.5);
}
template <typename T>
void ScapegoatST<T>::insert(T d){
  TreeNode<T>* newNode = new TreeNode<T>(d);
  int treeDepth = insertFindDepth(newNode);

  if(treeDepth > log3over2(m_size)) {
    TreeNode<T>* tempParent = newNode->m_parent;

    while(3*getSizeFromNode(tempParent) <= 2*getSizeFromNode(tempParent->m_parent)) {
      tempParent = tempParent->m_parent;
      rebuildSubTree(tempParent->m_parent);
    }
  }
}
template <typename T>
int ScapegoatST<T>::insertFindDepth(TreeNode<T>* newNode) {
  TreeNode<T>* tempRoot = m_root;
  int treeDepth = 0;

  if(tempRoot == NULL) {
    m_root = newNode;
    m_size++;
    return 0;
  } else {
    bool nodeInserted = false;

    while(!nodeInserted) {
      if(*newNode->m_data < *tempRoot->m_data) {
        if(tempRoot->m_left == NULL) {
          tempRoot->m_left = newNode;
          newNode->m_parent = tempRoot;
          nodeInserted = true;
        } else {
          tempRoot = tempRoot->m_left;
        }
      } else if(*newNode->m_data == *tempRoot->m_data) {
          return -1;
      } else {
          if(tempRoot->m_right == NULL) {
            tempRoot->m_right = newNode;
            newNode->m_parent = tempRoot;
            nodeInserted = true;
          } else {
            tempRoot = tempRoot->m_right;
          }
      }
      treeDepth++;
    }
  }

  m_size++;

  return treeDepth;
}
template <typename T>
void ScapegoatST<T>::rebuildSubTree(TreeNode<T>* subTreeRoot) {

  cout << "rebuilding subtree" << endl;

  int subTreeSize = getSizeFromNode(subTreeRoot);

  TreeNode<T>* tempParent = subTreeRoot->m_parent;

  DblList<TreeNode<T>*>* nodeList = new DblList<TreeNode<T>*>();

  convertToList(subTreeRoot, nodeList, 0);

  if(tempParent == NULL) {
    m_root = buildBalancedTree(nodeList, 0, subTreeSize);

    m_root->m_parent = NULL;
  } else if (*tempParent->m_right->m_data == *subTreeRoot->m_data) {
    tempParent->m_right = buildBalancedTree(nodeList, 0, subTreeSize);
  } else {
    tempParent->m_left = buildBalancedTree(nodeList, 0, subTreeSize);
  }
}
template <typename T>
int ScapegoatST<T>::convertToList(TreeNode<T>* currNode, DblList<TreeNode<T>*>* nodeList, int index) {
  if(currNode == NULL) {
    return index;
  } else {
    index = convertToList(currNode->m_left, nodeList, index);
    nodeList->add(index++, currNode);

    return convertToList(currNode->m_right, nodeList, index);
  }
}
template <typename T>
TreeNode<T>* ScapegoatST<T>::buildBalancedTree(DblList<TreeNode<T>*>* nodeList, int index, int subTreeSize) {

  cout << "building balanced tree" << endl;

  if(subTreeSize == 0) {
    return NULL;
  } else {
    int k = subTreeSize / 2;

    nodeList->get(index + k)->m_left = buildBalancedTree(nodeList, index, k);

    if(nodeList->get(index + k)->m_left != NULL) {
      nodeList->get(index+k)->m_left->m_parent = nodeList->get(index + k);
    }

    nodeList->get(index + k)->m_right = buildBalancedTree(nodeList, index + k + 1, subTreeSize - k - 1);

    if(nodeList->get(index + k)->m_right != NULL) {
      nodeList->get(index + k)->m_right->m_parent = nodeList->get(index + k);
    }

    return nodeList->get(index + k);
  }
}

template <typename T>
T ScapegoatST<T>::get(T d){
  TreeNode<T>* newNode = new TreeNode<T>(d);
  return getHelper(m_root, newNode);
}
template <typename T>
T ScapegoatST<T>::getHelper(TreeNode<T>* subTreeRoot, TreeNode<T>* newNode){
  if(subTreeRoot != NULL){
    if(*newNode->m_data == *subTreeRoot->m_data){
        return subTreeRoot->m_data;
    } else if(*newNode->m_data < *subTreeRoot->m_data){
        return getHelper(subTreeRoot->m_left,newNode);
    } else{
        return getHelper(subTreeRoot->m_right,newNode);
    }
  } else {
    return NULL;
  }
}
template <typename T>
bool ScapegoatST<T>::contains(T d){
  TreeNode<T>* newNode = new TreeNode<T>(d);
  return containsHelper(m_root, newNode);
}
template <typename T>
bool ScapegoatST<T>::containsHelper(TreeNode<T>* subTreeRoot, TreeNode<T>* newNode){
  if(subTreeRoot == NULL){
      return false;
  } else if(*newNode->m_data == *subTreeRoot->m_data){
      return true;
  } else if(*newNode->m_data < *subTreeRoot->m_data){
      return containsHelper(subTreeRoot->m_left,newNode);
  } else{
      return containsHelper(subTreeRoot->m_right,newNode);
  }
}
template <typename T>
void ScapegoatST<T>::printTreeInOrder(){
  printTreeInOrderHelper(m_root);
}
template <typename T>
void ScapegoatST<T>::printTreeInOrderHelper(TreeNode<T>* subTreeRoot){
  if(subTreeRoot != NULL){
    printTreeInOrderHelper(subTreeRoot->m_left);
    cout << *subTreeRoot->m_data << endl;
    printTreeInOrderHelper(subTreeRoot->m_right);
  }
}
template <typename T>
void ScapegoatST<T>::printTreePostOrder(){
  printTreePostOrderHelper(m_root);
}
template <typename T>
void ScapegoatST<T>::printTreePostOrderHelper(TreeNode<T>* subTreeRoot){
  if(subTreeRoot != NULL){
    printTreeInOrderHelper(subTreeRoot->m_left);
    printTreeInOrderHelper(subTreeRoot->m_right);
    cout << *subTreeRoot->m_data << endl;
  }
}
template <typename T>
T ScapegoatST<T>::getMin(){
  //check if empty
  return getMinHelper(m_root);
}
template <typename T>
T ScapegoatST<T>::getMinHelper(TreeNode<T>* subTreeRoot){
  if(subTreeRoot->m_left==NULL){
    return subTreeRoot->m_data;
  } else{
    return getMinHelper(subTreeRoot->m_left);
  }
}
template <typename T>
T ScapegoatST<T>::getMax(){
  //check if empty
  return getMaxHelper(m_root);
}
template <typename T>
T ScapegoatST<T>::getMaxHelper(TreeNode<T>* subTreeRoot){
  if(subTreeRoot->m_right==NULL){
    return subTreeRoot->m_data;
  } else{
    return getMaxHelper(subTreeRoot->m_right);
  }
}
template <typename T>
T ScapegoatST<T>::getMedian(){
  //check if empty
  return m_root->m_data;
}
template <typename T>
void ScapegoatST<T>::findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent){
  while(target != NULL && *target->m_data != *key){
    parent = target;
    if(*key < *target->m_data){
      target = target->m_left;
    } else{
      target = target->m_right;
    }
  }
}
template <typename T>
TreeNode<T>* ScapegoatST<T>::getSuccessor(TreeNode<T>* rightChild){
  while(rightChild->m_left != NULL){
    rightChild = rightChild->m_left;
  }
  return rightChild;
}
template <typename T>
void ScapegoatST<T>::remove(T d){
  //check if empty
  TreeNode<T>* target = NULL;
  TreeNode<T>* parent = NULL;
  target = m_root;
  findTarget(d,target,parent);
  if(target == NULL){ //value wasn't in tree, othing to do
    return;
  }
  //check if leaf (including the root)
  if(target->m_left == NULL && target->m_right == NULL){ //no children, it's a leaf
    if(*target->m_data == *m_root->m_data){ //leaf is the root of tree
      m_root = NULL;
    } else{ //it's not the root
      if(*target->m_data == *parent->m_left->m_data){
        parent->m_left = NULL;
      } else{
        parent->m_right = NULL;
      }
    }
    //delete target; //free the memory
  } else if(target->m_left != NULL && target->m_right != NULL){ //2 child case
    TreeNode<T>* suc = getSuccessor(target->m_right);
    T value = suc->m_data;
    remove(value); //remove successor treenode
    target->m_data = value;
  } else{ //1 child
    TreeNode<T>* child;
    if(target->m_left != NULL){
      child = target->m_left;
    } else{
      child = target->m_right;
    }
    if(*target->m_data == *m_root->m_data){
      m_root = child;
    } else{
      if(*target->m_data == *parent->m_left->m_data){
        //cout << "I'm here!" << endl;
        parent->m_left = child;
      } else{
        parent->m_right = child;
      }
    }
      //delete target;
  }
  --m_size;
}
#endif
