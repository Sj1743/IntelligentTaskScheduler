#ifndef AVLTREE_H
#define AVLTREE_H

#include "Task.h"
using namespace std;

class AVLTree {
private:
    struct AVLNode {
        Task task;
        AVLNode* left;
        AVLNode* right;
        int height;
        
        AVLNode(Task t) {
            task = t;
            left = NULL;
            right = NULL;
            height = 1;
        }
    };
    
    AVLNode* root;
    bool enableLogging;
    
    int getHeight(AVLNode* node);
    int getBalance(AVLNode* node);
    int maxVal(int a, int b);
    void updateHeight(AVLNode* node);
    
    AVLNode* leftRotate(AVLNode* z);
    AVLNode* rightRotate(AVLNode* z);
    AVLNode* leftRightRotate(AVLNode* z);
    AVLNode* rightLeftRotate(AVLNode* z);
    
    AVLNode* insertHelper(AVLNode* node, Task task);
    AVLNode* deleteHelper(AVLNode* node, int taskID);
    AVLNode* findMin(AVLNode* node);
    AVLNode* searchHelper(AVLNode* node, int taskID);
    
    void inorderHelper(AVLNode* node);
    void prettyPrintHelper(AVLNode* node, int indent);
    void destroyTree(AVLNode* node);
    
public:
    AVLTree();
    ~AVLTree();
    
    void insert(Task task);
    bool deleteTask(int taskID);
    Task* search(int taskID);
    void inorderTraversal();
    void prettyPrint();
    void setLogging(bool enable);
};

#endif