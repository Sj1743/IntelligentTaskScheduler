#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "Task.h"
#include <iostream>

class RedBlackTree {
private:
    enum Color { RED, BLACK };
    
    struct RBNode {
        Task task;
        RBNode* left;
        RBNode* right;
        RBNode* parent;
        Color color;
        
        RBNode(const Task& t) 
            : task(t), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
    };
    
    RBNode* root;
    RBNode* NIL; // Sentinel node
    bool enableLogging;
    
    // Helper functions
    void leftRotate(RBNode* x);
    void rightRotate(RBNode* x);
    void insertFixup(RBNode* z);
    RBNode* insertHelper(RBNode* root, RBNode* node);
    RBNode* searchHelper(RBNode* node, int taskID);
    
    // Traversal helpers
    void inorderHelper(RBNode* node);
    void prettyPrintHelper(RBNode* node, int indent);
    void destroyTree(RBNode* node);
    
public:
    RedBlackTree();
    ~RedBlackTree();
    
    void insert(const Task& task);
    Task* search(int taskID);
    void inorderTraversal();
    void prettyPrint();
    void setLogging(bool enable);
};

#endif
