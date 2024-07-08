#include "BST_InClass.h"
#include <iostream>

int main(){
  BST<int> tree;

  tree.insert(4);
  tree.insert(10);
  tree.insert(2);
  tree.insert(3);
  tree.insert(1);
  tree.insert(12);
  tree.insert(8);

  std:cout << "Least to Greatest: " << std::endl;
  tree.printInOrder();
  std::cout << std::endl;

  std:cout << "Post Order Notation: " << std::endl;
  tree.printTreePostOrder();
  std::cout << std::endl;

  std::cout << "Contains 10?" << tree.contains(10) << std::endl;
  std::cout << "Contains 5?" << tree.contains(5) << std::endl;

}
