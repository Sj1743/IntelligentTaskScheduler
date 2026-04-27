#include "TwoThreeTree.h"

TwoThreeTree::TwoThreeTree() : root(nullptr), enableLogging(true) {}

TwoThreeTree::~TwoThreeTree() { destroyTree(root); }

void TwoThreeTree::destroyTree(Node23* node) {
    if (node) {
        destroyTree(node->children[0]);
        destroyTree(node->children[1]);
        destroyTree(node->children[2]);
        delete node;
    }
}

void TwoThreeTree::sortKeys(Task keys[], int count) {
    if (count == 2 && keys[0].taskID > keys[1].taskID) {
        std::swap(keys[0], keys[1]);
    } else if (count == 3) {
        if (keys[0].taskID > keys[1].taskID) std::swap(keys[0], keys[1]);
        if (keys[1].taskID > keys[2].taskID) std::swap(keys[1], keys[2]);
        if (keys[0].taskID > keys[1].taskID) std::swap(keys[0], keys[1]);
    }
}

TwoThreeTree::SplitResult TwoThreeTree::insertHelper(Node23* node, const Task& task) {
    SplitResult res;
    if (node->isLeaf()) {
        if (node->keyCount < 2) {
            node->keys[node->keyCount++] = task;
            sortKeys(node->keys, node->keyCount);
        } else {
            Task tempKeys[3] = {node->keys[0], node->keys[1], task};
            sortKeys(tempKeys, 3);
            
            if (enableLogging) {
                int a = std::min(node->keys[0].taskID, node->keys[1].taskID);
                int b = std::max(node->keys[0].taskID, node->keys[1].taskID);
                std::cout << "23T SPLIT: Split node containing keys [" << a << "," << b << "]" << std::endl;
                std::cout << "23T SPLIT: Promote key " << tempKeys[1].taskID << std::endl;
            }
            
            node->keys[0] = tempKeys[0];
            node->keyCount = 1;
            
            Node23* sibling = new Node23();
            sibling->keys[0] = tempKeys[2];
            sibling->keyCount = 1;
            
            res.isSplit = true;
            res.promotedKey = tempKeys[1];
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
            Task tempKeys[3] = {node->keys[0], node->keys[1], childRes.promotedKey};
            Node23* tempChildren[4] = {node->children[0], node->children[1], node->children[2], nullptr};
            
            int insertPos = (childRes.promotedKey.taskID < node->keys[0].taskID) ? 0 :
                            (childRes.promotedKey.taskID < node->keys[1].taskID) ? 1 : 2;
            
            for (int i = 3; i > insertPos + 1; --i) tempChildren[i] = tempChildren[i-1];
            tempChildren[insertPos + 1] = childRes.rightNode;
            sortKeys(tempKeys, 3);
            
            if (enableLogging) {
                int a = std::min(node->keys[0].taskID, node->keys[1].taskID);
                int b = std::max(node->keys[0].taskID, node->keys[1].taskID);
                std::cout << "23T SPLIT: Split node containing keys [" << a << "," << b << "]" << std::endl;
                std::cout << "23T SPLIT: Promote key " << tempKeys[1].taskID << std::endl;
            }
            
            node->keys[0] = tempKeys[0];
            node->keyCount = 1;
            node->children[0] = tempChildren[0];
            node->children[1] = tempChildren[1];
            node->children[2] = nullptr;
            
            Node23* sibling = new Node23();
            sibling->keys[0] = tempKeys[2];
            sibling->keyCount = 1;
            sibling->children[0] = tempChildren[2];
            sibling->children[1] = tempChildren[3];
            
            res.isSplit = true;
            res.promotedKey = tempKeys[1];
            res.rightNode = sibling;
        }
    }
    return res;
}

void TwoThreeTree::insert(const Task& task) {
    if (!root) {
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
    if (!node) return nullptr;
    for (int i = 0; i < node->keyCount; ++i) {
        if (taskID == node->keys[i].taskID) return &(node->keys[i]);
    }
    if (node->isLeaf()) return nullptr;
    if (taskID < node->keys[0].taskID) return searchHelper(node->children[0], taskID);
    if (node->keyCount == 1 || taskID < node->keys[1].taskID) return searchHelper(node->children[1], taskID);
    return searchHelper(node->children[2], taskID);
}

Task* TwoThreeTree::search(int taskID) { return searchHelper(root, taskID); }

void TwoThreeTree::inorderHelper(Node23* node) {
    if (!node) return;
    inorderHelper(node->children[0]);
    std::cout << "TaskID: " << node->keys[0].taskID << std::endl;
    inorderHelper(node->children[1]);
    if (node->keyCount == 2) {
        std::cout << "TaskID: " << node->keys[1].taskID << std::endl;
        inorderHelper(node->children[2]);
    }
}

void TwoThreeTree::inorderTraversal() {
    std::cout << "\n=== 2-3 Tree Inorder Traversal ===" << std::endl;
    inorderHelper(root);
}

void TwoThreeTree::prettyPrintHelper(Node23* node, int indent) {
    if (!node) return;
    std::string spaces(indent, ' ');
    std::cout << spaces << "[";
    for(int i=0; i<node->keyCount; ++i) {
        std::cout << node->keys[i].taskID << (i == 0 && node->keyCount > 1 ? ", " : "");
    }
    std::cout << "]" << std::endl;
    if (!node->isLeaf()) {
        for(int i=0; i<=node->keyCount; ++i) {
            prettyPrintHelper(node->children[i], indent + 4);
        }
    }
}

void TwoThreeTree::prettyPrint() {
    std::cout << "\n=== 2-3 Tree Structure ===" << std::endl;
    prettyPrintHelper(root, 0);
}

void TwoThreeTree::setLogging(bool enable) { enableLogging = enable; }