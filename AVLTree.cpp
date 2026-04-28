#include "AVLTree.h"
#include <iomanip>

AVLTree::AVLTree() {
    root = NULL;
    enableLogging = true;
}

AVLTree::~AVLTree() {
    destroyTree(root);
}

void AVLTree::destroyTree(AVLNode* node) {
    if (node != NULL) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

int AVLTree::maxVal(int a, int b) {
    return (a > b) ? a : b;
}

int AVLTree::getHeight(AVLNode* node) {
    if (node == NULL) return 0;
    return node->height;
}

int AVLTree::getBalance(AVLNode* node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void AVLTree::updateHeight(AVLNode* node) {
    if (node != NULL) {
        node->height = 1 + maxVal(getHeight(node->left), getHeight(node->right));
    }
}

AVLTree::AVLNode* AVLTree::leftRotate(AVLNode* z) {
    if (enableLogging) {
        cout << "AVL ROTATE: LeftRotate (" << z->task.taskID << ")\n";
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
        cout << "AVL ROTATE: RightRotate (" << z->task.taskID << ")\n";
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
        cout << "AVL ROTATE: LeftRightRotate(" << z->task.taskID << ")\n";
    }
    z->left = leftRotate(z->left);
    return rightRotate(z);
}

AVLTree::AVLNode* AVLTree::rightLeftRotate(AVLNode* z) {
    if (enableLogging) {
        cout << "AVL ROTATE: RightLeftRotate(" << z->task.taskID << ")\n";
    }
    z->right = rightRotate(z->right);
    return leftRotate(z);
}

AVLTree::AVLNode* AVLTree::insertHelper(AVLNode* node, Task task) {
    if (node == NULL) {
        return new AVLNode(task);
    }
    
    if (task.taskID < node->task.taskID) {
        node->left = insertHelper(node->left, task);
    } else if (task.taskID > node->task.taskID) {
        node->right = insertHelper(node->right, task);
    } else {
        node->task = task;
        return node;
    }
    
    updateHeight(node);
    int balance = getBalance(node);
    
    if (balance > 1 && task.taskID < node->left->task.taskID) return rightRotate(node);
    if (balance < -1 && task.taskID > node->right->task.taskID) return leftRotate(node);
    if (balance > 1 && task.taskID > node->left->task.taskID) return leftRightRotate(node);
    if (balance < -1 && task.taskID < node->right->task.taskID) return rightLeftRotate(node);
    
    return node;
}

AVLTree::AVLNode* AVLTree::findMin(AVLNode* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

AVLTree::AVLNode* AVLTree::deleteHelper(AVLNode* node, int taskID) {
    if (node == NULL) return NULL;
    
    if (taskID < node->task.taskID) {
        node->left = deleteHelper(node->left, taskID);
    } else if (taskID > node->task.taskID) {
        node->right = deleteHelper(node->right, taskID);
    } else {
        if (node->left == NULL || node->right == NULL) {
            AVLNode* temp = node->left ? node->left : node->right;
            if (temp == NULL) {
                temp = node;
                node = NULL;
            } else {
                *node = *temp;
            }
            delete temp;
        } else {
            AVLNode* temp = findMin(node->right);
            node->task = temp->task;
            node->right = deleteHelper(node->right, temp->task.taskID);
        }
    }
    
    if (node == NULL) return node;
    
    updateHeight(node);
    int balance = getBalance(node);
    
    if (balance > 1 && getBalance(node->left) >= 0) return rightRotate(node);
    if (balance > 1 && getBalance(node->left) < 0) return leftRightRotate(node);
    if (balance < -1 && getBalance(node->right) <= 0) return leftRotate(node);
    if (balance < -1 && getBalance(node->right) > 0) return rightLeftRotate(node);
    
    return node;
}

AVLTree::AVLNode* AVLTree::searchHelper(AVLNode* node, int taskID) {
    if (node == NULL || node->task.taskID == taskID) return node;
    if (taskID < node->task.taskID) return searchHelper(node->left, taskID);
    return searchHelper(node->right, taskID);
}

void AVLTree::insert(Task task) { root = insertHelper(root, task); }
bool AVLTree::deleteTask(int taskID) {
    if (searchHelper(root, taskID) == NULL) return false;
    root = deleteHelper(root, taskID);
    return true;
}
Task* AVLTree::search(int taskID) {
    AVLNode* node = searchHelper(root, taskID);
    if (node == NULL) return NULL;
    return &(node->task);
}

void AVLTree::inorderHelper(AVLNode* node) {
    if (node != NULL) {
        inorderHelper(node->left);
        cout << "TaskID: " << node->task.taskID << " (BF: " << getBalance(node) << ")\n";
        inorderHelper(node->right);
    }
}
void AVLTree::inorderTraversal() {
    cout << "\n=== AVL Tree Inorder Traversal ===\n";
    inorderHelper(root);
}
void AVLTree::prettyPrintHelper(AVLNode* node, int indent) {
    if (node != NULL) {
        prettyPrintHelper(node->right, indent + 4);
        for(int i=0; i<indent; i++) cout << " ";
        cout << node->task.taskID << " (BF:" << getBalance(node) << ")\n";
        prettyPrintHelper(node->left, indent + 4);
    }
}
void AVLTree::prettyPrint() {
    cout << "\n=== AVL Tree Structure ===\n";
    prettyPrintHelper(root, 0);
}
void AVLTree::setLogging(bool enable) { enableLogging = enable; }