#include <iostream>
#include "LazyBST.h"
#include "TreeNode.h"

int main(){
    // ***************************************************************** // 
    // ****************** LECTURE  18 ********************************** // 
    // ***************************************************************** // 
    BST<int> tree;

    tree.insert(4);
    tree.insert(10);
    tree.insert(2);
    tree.insert(3);
    tree.insert(1);
    tree.insert(12);
    tree.insert(8);
    std::cout << "The size is: " << tree.size() << std::endl;
    std::cout << "Greatest to least: " << std::endl;
    tree.printInOrder();
    std::cout << std::endl;
    std::cout << "PostOrder: " << std::endl;
    tree.printTreePostOrder();
    std::cout << std::endl;

    std::cout << "Contains 10: " << tree.contains(10) << std::endl;
    std::cout << "Contains 5: " << tree.contains(5) << std::endl;
    std::cout << std::endl;
    std::cout << "Testing extrema..." << std::endl;
    std::cout << "Max: " ;
    std::cout << tree.max() << std::endl;
    std::cout << "Min: " ;
    std::cout << tree.min() << std::endl;

    tree.insert(9);
    tree.insert(13);
    tree.insert(7);
    std::cout << "Print in order after some inserts: " << std::endl; 
    tree.printInOrder();
    std::cout << std::endl;

    // ***************************************************************** // 
    // ****************** LECTURE  19 ********************************** // 
    // ***************************************************************** //
    tree.remove(4);
    std::cout << "Result of remove" << std::endl;
    tree.printInOrder();
    std::cout << std::endl;
    std::cout <<  "median: " << tree.median() << std::endl;

    tree.RdepthTrack(8);

    return 0;

}