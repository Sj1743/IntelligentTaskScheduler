#include "RedBlackTree.h"

RedBlackTree::RedBlackTree() : enableLogging(true) {
    NIL = new RBNode(Task());
    NIL->color = BLACK;
    root = NIL;
}

RedBlackTree::~RedBlackTree() {
    destroyTree(root);
    delete NIL;
}

void RedBlackTree::destroyTree(RBNode* node) {
    if (node != NIL) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

void RedBlackTree::leftRotate(RBNode* x) {
    if (enableLogging) {
        std::cout << "RBT FIXUP: RotateLeft(" << x->task.taskID << ")" << std::endl;
    }
    RBNode* y = x->right;
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr) root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else x->parent->right = y;
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(RBNode* x) {
    if (enableLogging) {
        std::cout << "RBT FIXUP: RotateRight (" << x->task.taskID << ")" << std::endl;
    }
    RBNode* y = x->left;
    x->left = y->right;
    if (y->right != NIL) y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr) root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else x->parent->left = y;
    y->right = x;
    x->parent = y;
}

void RedBlackTree::insertFixup(RBNode* z) {
    while (z->parent != nullptr && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode* y = z->parent->parent->right;
            if (y->color == RED) {
                if (enableLogging) {
                    std::cout << "RBT FIXUP: Recolor at node " << z->parent->parent->task.taskID << std::endl;
                }
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            RBNode* y = z->parent->parent->left;
            if (y->color == RED) {
                if (enableLogging) {
                    std::cout << "RBT FIXUP: Recolor at node " << z->parent->parent->task.taskID << std::endl;
                }
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void RedBlackTree::insert(const Task& task) {
    RBNode* z = new RBNode(task);
    z->left = NIL;
    z->right = NIL;
    
    RBNode* y = nullptr;
    RBNode* x = root;
    
    while (x != NIL) {
        y = x;
        if (z->task.taskID < x->task.taskID) x = x->left;
        else if (z->task.taskID > x->task.taskID) x = x->right;
        else {
            x->task = task;
            delete z;
            return;
        }
    }
    
    z->parent = y;
    if (y == nullptr) root = z;
    else if (z->task.taskID < y->task.taskID) y->left = z;
    else y->right = z;
    
    insertFixup(z);
}

Task* RedBlackTree::search(int taskID) {
    RBNode* curr = root;
    while (curr != NIL && taskID != curr->task.taskID) {
        if (taskID < curr->task.taskID) curr = curr->left;
        else curr = curr->right;
    }
    return (curr != NIL) ? &(curr->task) : nullptr;
}

void RedBlackTree::inorderHelper(RBNode* node) {
    if (node != NIL) {
        inorderHelper(node->left);
        std::string c = (node->color == RED) ? "R" : "B";
        std::cout << "TaskID: " << node->task.taskID << " (" << c << ")" << std::endl;
        inorderHelper(node->right);
    }
}

void RedBlackTree::inorderTraversal() {
    std::cout << "\n=== Red-Black Tree Inorder Traversal ===" << std::endl;
    inorderHelper(root);
}

void RedBlackTree::prettyPrintHelper(RBNode* node, int indent) {
    if (node != NIL) {
        prettyPrintHelper(node->right, indent + 4);
        std::string c = (node->color == RED) ? "R" : "B";
        for (int i = 0; i < indent; i++) std::cout << " ";
        std::cout << node->task.taskID << " (" << c << ")" << std::endl;
        prettyPrintHelper(node->left, indent + 4);
    }
}

void RedBlackTree::prettyPrint() {
    std::cout << "\n=== Red-Black Tree Structure ===" << std::endl;
    prettyPrintHelper(root, 0);
}

void RedBlackTree::setLogging(bool enable) { enableLogging = enable; }