#ifndef BTREE_H
#define BTREE_H

// C++ Program to Implement B-Tree
#include <iostream>

// class for the node present in a B-Tree
template <typename T, int ORDER>
class BTreeNode
{
public:
    // Array of keys
    T keys[ORDER - 1];
    // Array of child pointers
    BTreeNode *children[ORDER];
    // Current number of keys
    int n;
    // True if leaf node, false otherwise
    bool leaf;

    BTreeNode(bool isLeaf = true) : n(0), leaf(isLeaf);
};

// class for B-Tree
template <typename T, int ORDER>
class BTree
{
private:
    BTreeNode<T, ORDER> *root; // Pointer to root node

    // Function to split a full child node
    void splitChild(BTreeNode<T, ORDER> *x, int i);

    // Function to insert a key in a non-full node
    void insertNonFull(BTreeNode<T, ORDER> *x, T k);

    // Function to traverse the tree
    void traverse(BTreeNode<T, ORDER> *x);

    // Function to search a key in the tree
    BTreeNode<T, ORDER> *search(BTreeNode<T, ORDER> *x, T k);

    // Function to find the predecessor
    T getPredecessor(BTreeNode<T, ORDER> *node, int idx);

    // Function to find the successor
    T getSuccessor(BTreeNode<T, ORDER> *node, int idx);

    // Function to fill child node
    void fill(BTreeNode<T, ORDER> *node, int idx);

    // Function to borrow from previous sibling
    void borrowFromPrev(BTreeNode<T, ORDER> *node, int idx);

    // Function to borrow from next sibling
    void borrowFromNext(BTreeNode<T, ORDER> *node, int idx);

    // Function to merge two nodes
    void merge(BTreeNode<T, ORDER> *node, int idx);

    // Function to remove a key from a non-leaf node
    void removeFromNonLeaf(BTreeNode<T, ORDER> *node, int idx);

    // Function to remove a key from a leaf node
    void removeFromLeaf(BTreeNode<T, ORDER> *node, int idx);

    // Function to remove a key from the tree
    void remove(BTreeNode<T, ORDER> *node, T k);

    friend class Hospital;

public:
    BTree();

    // Function to insert a key in the tree
    void insert(T k);

    // Function to traverse the tree
    void traverse();

    // Function to search a key in the tree
    BTreeNode<T, ORDER> *search(T k);

    /* More project 4 fodder
    // Function to remove a key from the tree
    void remove(T k);
    */
};

#endif