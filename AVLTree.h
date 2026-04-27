#ifndef AVLTREE_H
#define AVLTREE_H

#include "Task.h"
#include <iostream>
#include <algorithm>

class AVLTree {
private:
    struct AVLNode {
        Task task;
        AVLNode* left;
        AVLNode* right;
        int height;
        
        AVLNode(const Task& t) : task(t), left(nullptr), right(nullptr), height(1) {}
    };
    
    AVLNode* root;
    bool enableLogging;
    
    // Helper functions
    int getHeight(AVLNode* node);
    int getBalance(AVLNode* node);
    void updateHeight(AVLNode* node);
    
    // Rotation functions
    AVLNode* leftRotate(AVLNode* z);
    AVLNode* rightRotate(AVLNode* z);
    AVLNode* leftRightRotate(AVLNode* z);
    AVLNode* rightLeftRotate(AVLNode* z);
    
    // Insert/Delete/Search helpers
    AVLNode* insertHelper(AVLNode* node, const Task& task);
    AVLNode* deleteHelper(AVLNode* node, int taskID);
    AVLNode* findMin(AVLNode* node);
    AVLNode* searchHelper(AVLNode* node, int taskID);
    
    // Traversal helpers
    void inorderHelper(AVLNode* node);
    void prettyPrintHelper(AVLNode* node, int indent);
    void destroyTree(AVLNode* node);
    
public:
    AVLTree();
    ~AVLTree();
    
    void insert(const Task& task);
    bool deleteTask(int taskID);
    Task* search(int taskID);
    void inorderTraversal();
    void prettyPrint();
    void setLogging(bool enable);
};

#endif
