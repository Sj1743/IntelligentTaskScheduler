#ifndef TWOTHREETREE_H
#define TWOTHREETREE_H
#include "Task.h"
using namespace std;

class TwoThreeTree {
private:
    struct Node23 {
        Task keys[2];
        Node23* children[3];
        int keyCount;
        Node23() {
            keyCount = 0;
            children[0] = NULL;
            children[1] = NULL;
            children[2] = NULL;
        }
        bool isLeaf() const { 
            return children[0] == NULL; 
        }
    };
    
    Node23* root;
    bool enableLogging;
    
    struct SplitResult {
        Task promotedKey;
        Node23* rightNode;
        bool isSplit;
        SplitResult() { 
            rightNode = NULL; 
            isSplit = false; 
        }
    };

    SplitResult insertHelper(Node23* node, Task task);
    Task* searchHelper(Node23* node, int taskID);
    void sortKeys(Task keys[], int count);
    void inorderHelper(Node23* node);
    void prettyPrintHelper(Node23* node, int indent);
    void destroyTree(Node23* node);

public:
    TwoThreeTree();
    ~TwoThreeTree();
    Task* search(int taskID);
    void insert(Task task);
    void inorderTraversal();
    void prettyPrint();
    void setLogging(bool enable);
};

#endif