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
            height = 1;
            task = t;
            left = NULL;
            right = NULL;
        }
    };
    
    AVLNode* root;
    bool enableLogging;
    int getHeight(AVLNode* node);
    int getBalance(AVLNode* node);

    void updateHeight(AVLNode* node);
    void inorderHelper(AVLNode* node);
    void prettyPrintHelper(AVLNode* node, int indent);
    void destroyTree(AVLNode* node);
    
    AVLNode* leftRotate(AVLNode* z);
    AVLNode* rightRotate(AVLNode* z);
    AVLNode* leftRightRotate(AVLNode* z);
    AVLNode* rightLeftRotate(AVLNode* z);
    AVLNode* insertHelper(AVLNode* node, Task task);
    AVLNode* deleteHelper(AVLNode* node, int taskID);
    AVLNode* findMin(AVLNode* node);
    AVLNode* searchHelper(AVLNode* node, int taskID);
    
public:
    AVLTree();
    ~AVLTree();
    Task* search(int taskID);
    void insert(Task task);
    bool deleteTask(int taskID);
    void inorderTraversal();
    void prettyPrint();
    void setLogging(bool enable);
};

#endif