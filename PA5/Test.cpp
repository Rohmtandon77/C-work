#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int value;
    int left_depth;
    int right_depth;
    Node* left_child;
    Node* right_child;
    Node(int v) : value(v), left_depth(0), right_depth(0), left_child(nullptr), right_child(nullptr) {}
};

class LazyBST {
private:
    Node* root;
    int size;

    void destroy(Node* n) {
        if (n != nullptr) {
            destroy(n->left_child);
            destroy(n->right_child);
            delete n;
        }
    }

    void traverse(Node* n, int* arr, int& index) {
        if (n != nullptr) {
            traverse(n->left_child, arr, index);
            arr[index++] = n->value;
            traverse(n->right_child, arr, index);
        }
    }

    Node* build_balanced_tree(int* arr, int start, int end) {
        if (start > end) {
            return nullptr;
        }
        int mid = (start + end) / 2;
        Node* n = new Node(arr[mid]);
        n->left_child = build_balanced_tree(arr, start, mid - 1);
        n->right_child = build_balanced_tree(arr, mid + 1, end);
        update_depths(n);
        return n;
    }

    void update_depths(Node* n) {
        int left_depth = n->left_child != nullptr ? max(n->left_child->left_depth, n->left_child->right_depth) + 1 : 0;
        int right_depth = n->right_child != nullptr ? max(n->right_child->left_depth, n->right_child->right_depth) + 1 : 0;
        n->left_depth = left_depth;
        n->right_depth = right_depth;
    }

    void rebalance() {
        if (root != nullptr && abs(root->left_depth - root->right_depth) > 1.5) {
            int* arr = new int[size];
            int index = 0;
            traverse(root, arr, index);
            destroy(root);
            root = build_balanced_tree(arr, 0, size - 1);
            delete[] arr;
        }
    }

public:
    LazyBST() : root(nullptr), size(0) {}

    ~LazyBST() {
        destroy(root);
    }

    void insert(int value) {
        Node* n = new Node(value);
        if (root == nullptr) {
            root = n;
        } else {
            Node* curr = root;
            while (true) {
                if (value < curr->value) {
                    if (curr->left_child == nullptr) {
                        curr->left_child = n;
                        update_depths(curr);
                        break;
                    } else {
                        curr = curr->left_child;
                    }
                } else {
                    if (curr->right_child == nullptr) {
                        curr->right_child = n;
                        update_depths(curr);
                        break;
                    } else {
                        curr = curr->right_child;
                    }
                }
            }
        }
        size++;
        rebalance();
    }

    bool search(int value) {
        Node* curr = root;
        while (curr != nullptr) {
            if (value == curr->value) {
                return true;
            } else if (value < curr->value) {
                curr = curr->left_child;
            } else {
                curr = curr->right_child;
            }
        }
        return false;
    }
};
