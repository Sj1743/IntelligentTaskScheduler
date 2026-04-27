#ifndef TWOTHREETREE_H
#define TWOTHREETREE_H

#include "Task.h"
#include <iostream>
#include <algorithm>

class TwoThreeTree {
private:
    struct Node23 {
        Task keys[2];
        Node23* children[3];
        int keyCount;
        Node23() : keyCount(0) {
            children[0] = children[1] = children[2] = nullptr;
        }
        bool isLeaf() const { return children[0] == nullptr; }
    };
    
    Node23* root;
    bool enableLogging;
    
    struct SplitResult {
        Task promotedKey;
        Node23* rightNode;
        bool isSplit;
        SplitResult() : rightNode(nullptr), isSplit(false) {}
    };

    SplitResult insertHelper(Node23* node, const Task& task);
    void sortKeys(Task keys[], int count);
    void inorderHelper(Node23* node);
    void prettyPrintHelper(Node23* node, int indent);
    Task* searchHelper(Node23* node, int taskID);
    void destroyTree(Node23* node);

public:
    TwoThreeTree();
    ~TwoThreeTree();
    void insert(const Task& task);
    Task* search(int taskID);
    void inorderTraversal();
    void prettyPrint();
    void setLogging(bool enable);
};

#endif