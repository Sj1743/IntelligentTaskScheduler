#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "Task.h"
using namespace std;

class RedBlackTree {
private:
    enum Color { RED, BLACK };
    
    struct RBNode {
        Task task;
        RBNode* left;
        RBNode* right;
        RBNode* parent;
        Color color;
        
        RBNode(Task t) {
            task = t;
            left = NULL;
            right = NULL;
            parent = NULL;
            color = RED;
        }
    };
    
    RBNode* root;
    RBNode* NIL;
    bool enableLogging;
    
    void leftRotate(RBNode* x);
    void rightRotate(RBNode* x);
    void insertFixup(RBNode* z);
    RBNode* searchHelper(RBNode* node, int taskID);
    void inorderHelper(RBNode* node);
    void prettyPrintHelper(RBNode* node, int indent);
    void destroyTree(RBNode* node);
    
public:
    RedBlackTree();
    ~RedBlackTree();
    
    void insert(Task task);
    Task* search(int taskID);
    void inorderTraversal();
    void prettyPrint();
    void setLogging(bool enable);
};

#endif