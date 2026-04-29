#include "RedBlackTree.h"

RedBlackTree::RedBlackTree() {
    enableLogging = true;
    NIL = new RBNode(Task());
    NIL->color = BLACK;
    root = NIL;
}

RedBlackTree::~RedBlackTree() {
    destroyTree(root);
    delete NIL;
}

void RedBlackTree::destroyTree(RBNode* node) {
    if (node != NIL && node != NULL) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

void RedBlackTree::leftRotate(RBNode* x) {
    if (enableLogging) {
        cout << "RBT FIXUP: RotateLeft(" << x->task.taskID << ")\n";
    }
    RBNode* y = x->right;
    x->right = y->left;
    if (y->left != NIL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(RBNode* x) {
    if (enableLogging) {
        cout << "RBT FIXUP: RotateRight (" << x->task.taskID << ")\n";
    }
    RBNode* y = x->left;
    x->left = y->right;
    if (y->right != NIL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void RedBlackTree::insertFixup(RBNode* z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode* y = z->parent->parent->right;
            if (y->color == RED) {
                if (enableLogging) cout << "RBT FIXUP: Recolor at node " << z->parent->parent->task.taskID << "\n";
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
                if (enableLogging) cout << "RBT FIXUP: Recolor at node " << z->parent->parent->task.taskID << "\n";
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

void RedBlackTree::insert(Task task) {
    RBNode* z = new RBNode(task);
    z->left = NIL;
    z->right = NIL;
    RBNode* y = NULL;
    RBNode* x = root;
    
    while (x != NIL) {
        y = x;
        if (z->task.taskID < x->task.taskID) {
            x = x->left;
        } else if (z->task.taskID > x->task.taskID) {
            x = x->right;
        } else {
            x->task = task;
            delete z;
            return;
        }
    }
    
    z->parent = y;
    if (y == NULL) {
        root = z;
    } else if (z->task.taskID < y->task.taskID) {
        y->left = z;
    } else {
        y->right = z;
    }
    
    insertFixup(z);
}

RedBlackTree::RBNode* RedBlackTree::searchHelper(RBNode* node, int taskID) {
    if (node == NIL || node->task.taskID == taskID) {
        return node;
    }
    if (taskID < node->task.taskID) {
        return searchHelper(node->left, taskID);
    }
    return searchHelper(node->right, taskID);
}

Task* RedBlackTree::search(int taskID) {
    RBNode* node = searchHelper(root, taskID);
    if (node == NIL) {
        return NULL;
    }
    return &(node->task);
}

void RedBlackTree::inorderHelper(RBNode* node) {
    if (node != NIL) {
        inorderHelper(node->left);
        string c = (node->color == RED) ? "R" : "B";
        cout << "TaskID: " << node->task.taskID << " (" << c << ")\n";
        inorderHelper(node->right);
    }
}

void RedBlackTree::inorderTraversal() {
    cout << "\n=== Red-Black Tree Inorder Traversal ===\n";
    inorderHelper(root);
}

void RedBlackTree::prettyPrintHelper(RBNode* node, int indent) {
    if (node != NIL) {
        prettyPrintHelper(node->right, indent + 4);
        string c = (node->color == RED) ? "R" : "B";
        for (int i = 0; i < indent; i++) {
            cout << " ";
        }
        cout << node->task.taskID << " (" << c << ")\n";
        prettyPrintHelper(node->left, indent + 4);
    }
}

void RedBlackTree::prettyPrint() {
    cout << "\n=== Red-Black Tree Structure ===\n";
    prettyPrintHelper(root, 0);
}

void RedBlackTree::setLogging(bool enable) { enableLogging = enable; }