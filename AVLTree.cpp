#include "AVLTree.h"
#include <iomanip>

AVLTree::AVLTree() : root(nullptr), enableLogging(true) {}

AVLTree::~AVLTree() {
    destroyTree(root);
}

void AVLTree::destroyTree(AVLNode* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

int AVLTree::getHeight(AVLNode* node) {
    return node ? node->height : 0;
}

int AVLTree::getBalance(AVLNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

void AVLTree::updateHeight(AVLNode* node) {
    if (node) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
}

AVLTree::AVLNode* AVLTree::leftRotate(AVLNode* z) {
    if (enableLogging) {
        // Space added before ( to match exactly: "AVL ROTATE: LeftRotate (<taskID>)"
        std::cout << "AVL ROTATE: LeftRotate (" << z->task.taskID << ")" << std::endl;
    }
    
    AVLNode* y = z->right;
    AVLNode* T2 = y->left;
    
    y->left = z;
    z->right = T2;
    
    updateHeight(z);
    updateHeight(y);
    
    return y;
}

AVLTree::AVLNode* AVLTree::rightRotate(AVLNode* z) {
    if (enableLogging) {
        // Space added before ( to match exactly: "AVL ROTATE: RightRotate (<taskID>)"
        std::cout << "AVL ROTATE: RightRotate (" << z->task.taskID << ")" << std::endl;
    }
    
    AVLNode* y = z->left;
    AVLNode* T3 = y->right;
    
    y->right = z;
    z->left = T3;
    
    updateHeight(z);
    updateHeight(y);
    
    return y;
}

AVLTree::AVLNode* AVLTree::leftRightRotate(AVLNode* z) {
    if (enableLogging) {
        // No space here as per PDF: "AVL ROTATE: LeftRightRotate(<taskID>)"
        std::cout << "AVL ROTATE: LeftRightRotate(" << z->task.taskID << ")" << std::endl;
    }
    
    z->left = leftRotate(z->left);
    return rightRotate(z);
}

AVLTree::AVLNode* AVLTree::rightLeftRotate(AVLNode* z) {
    if (enableLogging) {
        // No space here as per PDF: "AVL ROTATE: RightLeftRotate(<taskID>)"
        std::cout << "AVL ROTATE: RightLeftRotate(" << z->task.taskID << ")" << std::endl;
    }
    
    z->right = rightRotate(z->right);
    return leftRotate(z);
}

AVLTree::AVLNode* AVLTree::insertHelper(AVLNode* node, const Task& task) {
    // Standard BST insertion
    if (!node) {
        return new AVLNode(task);
    }
    
    if (task.taskID < node->task.taskID) {
        node->left = insertHelper(node->left, task);
    } else if (task.taskID > node->task.taskID) {
        node->right = insertHelper(node->right, task);
    } else {
        // Duplicate taskID - update existing task
        node->task = task;
        return node;
    }
    
    // Update height
    updateHeight(node);
    
    // Get balance factor
    int balance = getBalance(node);
    
    // Left-Left Case
    if (balance > 1 && task.taskID < node->left->task.taskID) {
        return rightRotate(node);
    }
    
    // Right-Right Case
    if (balance < -1 && task.taskID > node->right->task.taskID) {
        return leftRotate(node);
    }
    
    // Left-Right Case
    if (balance > 1 && task.taskID > node->left->task.taskID) {
        return leftRightRotate(node);
    }
    
    // Right-Left Case
    if (balance < -1 && task.taskID < node->right->task.taskID) {
        return rightLeftRotate(node);
    }
    
    return node;
}

AVLTree::AVLNode* AVLTree::findMin(AVLNode* node) {
    while (node->left) {
        node = node->left;
    }
    return node;
}

AVLTree::AVLNode* AVLTree::deleteHelper(AVLNode* node, int taskID) {
    if (!node) {
        return nullptr;
    }
    
    // Standard BST deletion
    if (taskID < node->task.taskID) {
        node->left = deleteHelper(node->left, taskID);
    } else if (taskID > node->task.taskID) {
        node->right = deleteHelper(node->right, taskID);
    } else {
        // Node to be deleted found
        if (!node->left || !node->right) {
            AVLNode* temp = node->left ? node->left : node->right;
            
            if (!temp) {
                // No child case
                temp = node;
                node = nullptr;
            } else {
                // One child case
                *node = *temp;
            }
            delete temp;
        } else {
            // Two children case
            AVLNode* temp = findMin(node->right);
            node->task = temp->task;
            node->right = deleteHelper(node->right, temp->task.taskID);
        }
    }
    
    if (!node) {
        return node;
    }
    
    // Update height
    updateHeight(node);
    
    // Get balance factor
    int balance = getBalance(node);
    
    // Left-Left Case
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rightRotate(node);
    }
    
    // Left-Right Case
    if (balance > 1 && getBalance(node->left) < 0) {
        return leftRightRotate(node);
    }
    
    // Right-Right Case
    if (balance < -1 && getBalance(node->right) <= 0) {
        return leftRotate(node);
    }
    
    // Right-Left Case
    if (balance < -1 && getBalance(node->right) > 0) {
        return rightLeftRotate(node);
    }
    
    return node;
}

AVLTree::AVLNode* AVLTree::searchHelper(AVLNode* node, int taskID) {
    if (!node || node->task.taskID == taskID) {
        return node;
    }
    
    if (taskID < node->task.taskID) {
        return searchHelper(node->left, taskID);
    }
    return searchHelper(node->right, taskID);
}

void AVLTree::insert(const Task& task) {
    root = insertHelper(root, task);
}

bool AVLTree::deleteTask(int taskID) {
    AVLNode* found = searchHelper(root, taskID);
    if (!found) {
        return false;
    }
    root = deleteHelper(root, taskID);
    return true;
}

Task* AVLTree::search(int taskID) {
    AVLNode* node = searchHelper(root, taskID);
    return node ? &(node->task) : nullptr;
}

void AVLTree::inorderHelper(AVLNode* node) {
    if (node) {
        inorderHelper(node->left);
        std::cout << "TaskID: " << node->task.taskID << " (BF: " << getBalance(node) << ")" << std::endl;
        inorderHelper(node->right);
    }
}

void AVLTree::inorderTraversal() {
    if (!root) {
        std::cout << "AVL Tree is empty." << std::endl;
        return;
    }
    std::cout << "\n=== AVL Tree Inorder Traversal ===" << std::endl;
    inorderHelper(root);
    std::cout << std::endl;
}

void AVLTree::prettyPrintHelper(AVLNode* node, int indent) {
    if (node) {
        prettyPrintHelper(node->right, indent + 4);
        std::cout << std::setw(indent) << "" << node->task.taskID 
                  << " (BF:" << getBalance(node) << ")" << std::endl;
        prettyPrintHelper(node->left, indent + 4);
    }
}

void AVLTree::prettyPrint() {
    if (!root) {
        std::cout << "AVL Tree is empty." << std::endl;
        return;
    }
    std::cout << "\n=== AVL Tree Structure ===" << std::endl;
    prettyPrintHelper(root, 0);
    std::cout << std::endl;
}

void AVLTree::setLogging(bool enable) {
    enableLogging = enable;
}