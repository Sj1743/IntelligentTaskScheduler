#include "TwoThreeTree.h"

TwoThreeTree::TwoThreeTree() {
    root = NULL;
    enableLogging = true;
}

TwoThreeTree::~TwoThreeTree() {
    destroyTree(root);
}

void TwoThreeTree::destroyTree(Node23* node) {
    if (node != NULL) {
        destroyTree(node->children[0]);
        destroyTree(node->children[1]);
        destroyTree(node->children[2]);
        delete node;
    }
}

void TwoThreeTree::sortKeys(Task keys[], int count) {
    if (count == 2 && keys[0].taskID > keys[1].taskID) {
        Task temp = keys[0]; keys[0] = keys[1]; keys[1] = temp;
    } else if (count == 3) {
        if (keys[0].taskID > keys[1].taskID) { Task temp = keys[0]; keys[0] = keys[1]; keys[1] = temp; }
        if (keys[1].taskID > keys[2].taskID) { Task temp = keys[1]; keys[1] = keys[2]; keys[2] = temp; }
        if (keys[0].taskID > keys[1].taskID) { Task temp = keys[0]; keys[0] = keys[1]; keys[1] = temp; }
    }
}

TwoThreeTree::SplitResult TwoThreeTree::insertHelper(Node23* node, Task task) {
    SplitResult res;
    if (node->isLeaf()) {
        if (node->keyCount < 2) {
            node->keys[node->keyCount] = task;
            node->keyCount++;
            sortKeys(node->keys, node->keyCount);
        } else {
            Task smallest, middle, largest;
            if (task.taskID < node->keys[0].taskID) {
                smallest = task;
                middle = node->keys[0];
                largest = node->keys[1];
            } else if (task.taskID < node->keys[1].taskID) {
                smallest = node->keys[0];
                middle = task;
                largest = node->keys[1];
            } else {
                smallest = node->keys[0];
                middle = node->keys[1];
                largest = task;
            }
            
            if (enableLogging) {
                int a = (node->keys[0].taskID < node->keys[1].taskID) ? node->keys[0].taskID : node->keys[1].taskID;
                int b = (node->keys[0].taskID > node->keys[1].taskID) ? node->keys[0].taskID : node->keys[1].taskID;
                cout << "23T SPLIT: Split node containing keys [" << a << "," << b << "]\n";
                cout << "23T SPLIT: Promote key " << middle.taskID << "\n";
            }
            
            node->keys[0] = smallest;
            node->keyCount = 1;
            
            Node23* sibling = new Node23();
            sibling->keys[0] = largest;
            sibling->keyCount = 1;
            
            res.isSplit = true;
            res.promotedKey = middle;
            res.rightNode = sibling;
        }
        return res;
    }
    
    int childIdx = 0;
    if (task.taskID < node->keys[0].taskID) childIdx = 0;
    else if (node->keyCount == 1 || task.taskID < node->keys[1].taskID) childIdx = 1;
    else childIdx = 2;
    
    SplitResult childRes = insertHelper(node->children[childIdx], task);
    
    if (childRes.isSplit) {
        if (node->keyCount < 2) {
            node->keys[1] = childRes.promotedKey;
            node->keyCount = 2;
            sortKeys(node->keys, 2);
            
            if (node->keys[0].taskID == childRes.promotedKey.taskID) {
                node->children[2] = node->children[1];
                node->children[1] = childRes.rightNode;
            } else {
                node->children[2] = childRes.rightNode;
            }
            res.isSplit = false;
        } else {
            Task smallest, middle, largest;
            if (childRes.promotedKey.taskID < node->keys[0].taskID) {
                smallest = childRes.promotedKey;
                middle = node->keys[0];
                largest = node->keys[1];
            } else if (childRes.promotedKey.taskID < node->keys[1].taskID) {
                smallest = node->keys[0];
                middle = childRes.promotedKey;
                largest = node->keys[1];
            } else {
                smallest = node->keys[0];
                middle = node->keys[1];
                largest = childRes.promotedKey;
            }
            
            Node23* tempChildren[4];
            tempChildren[0] = node->children[0];
            tempChildren[1] = node->children[1];
            tempChildren[2] = node->children[2];
            tempChildren[3] = NULL;
            
            int insertPos = 0;
            if (childRes.promotedKey.taskID > node->keys[0].taskID) insertPos = 1;
            if (childRes.promotedKey.taskID > node->keys[1].taskID) insertPos = 2;
            
            for (int i = 3; i > insertPos + 1; i--) tempChildren[i] = tempChildren[i-1];
            tempChildren[insertPos + 1] = childRes.rightNode;
            
            if (enableLogging) {
                int a = (node->keys[0].taskID < node->keys[1].taskID) ? node->keys[0].taskID : node->keys[1].taskID;
                int b = (node->keys[0].taskID > node->keys[1].taskID) ? node->keys[0].taskID : node->keys[1].taskID;
                cout << "23T SPLIT: Split node containing keys [" << a << "," << b << "]\n";
                cout << "23T SPLIT: Promote key " << middle.taskID << "\n";
            }
            
            node->keys[0] = smallest;
            node->keyCount = 1;
            node->children[0] = tempChildren[0];
            node->children[1] = tempChildren[1];
            node->children[2] = NULL;
            
            Node23* sibling = new Node23();
            sibling->keys[0] = largest;
            sibling->keyCount = 1;
            sibling->children[0] = tempChildren[2];
            sibling->children[1] = tempChildren[3];
            
            res.isSplit = true;
            res.promotedKey = middle;
            res.rightNode = sibling;
        }
    }
    return res;
}

void TwoThreeTree::insert(Task task) {
    if (root == NULL) {
        root = new Node23();
        root->keys[0] = task;
        root->keyCount = 1;
        return;
    }
    
    SplitResult res = insertHelper(root, task);
    if (res.isSplit) {
        Node23* newRoot = new Node23();
        newRoot->keys[0] = res.promotedKey;
        newRoot->keyCount = 1;
        newRoot->children[0] = root;
        newRoot->children[1] = res.rightNode;
        root = newRoot;
    }
}

Task* TwoThreeTree::searchHelper(Node23* node, int taskID) {
    if (node == NULL) return NULL;
    for (int i = 0; i < node->keyCount; i++) {
        if (taskID == node->keys[i].taskID) return &(node->keys[i]);
    }
    if (node->isLeaf()) return NULL;
    if (taskID < node->keys[0].taskID) return searchHelper(node->children[0], taskID);
    if (node->keyCount == 1 || taskID < node->keys[1].taskID) return searchHelper(node->children[1], taskID);
    return searchHelper(node->children[2], taskID);
}

Task* TwoThreeTree::search(int taskID) { return searchHelper(root, taskID); }

void TwoThreeTree::inorderHelper(Node23* node) {
    if (node == NULL) return;
    inorderHelper(node->children[0]);
    cout << "TaskID: " << node->keys[0].taskID << "\n";
    inorderHelper(node->children[1]);
    if (node->keyCount == 2) {
        cout << "TaskID: " << node->keys[1].taskID << "\n";
        inorderHelper(node->children[2]);
    }
}

void TwoThreeTree::inorderTraversal() {
    cout << "\n=== 2-3 Tree Inorder Traversal ===\n";
    inorderHelper(root);
}

void TwoThreeTree::prettyPrintHelper(Node23* node, int indent) {
    if (node == NULL) return;
    for(int i=0; i<indent; i++) cout << " ";
    cout << "[";
    for(int i=0; i<node->keyCount; i++) {
        cout << node->keys[i].taskID;
        if(i == 0 && node->keyCount > 1) cout << ", ";
    }
    cout << "]\n";
    if (!node->isLeaf()) {
        for(int i=0; i<=node->keyCount; i++) {
            prettyPrintHelper(node->children[i], indent + 4);
        }
    }
}

void TwoThreeTree::prettyPrint() {
    cout << "\n=== 2-3 Tree Structure ===\n";
    prettyPrintHelper(root, 0);
}

void TwoThreeTree::setLogging(bool enable) { enableLogging = enable; }