#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    int height;

    Node(int value) {
        data = value;
        left = right = nullptr;
        height = 1;
    }
};

class AVL {
public:
    Node* root;

    AVL() : root(nullptr) {}

    int height(Node* node) {
        return node ? node->height : 0;
    }

    int getBalance(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node* insert(Node* node, int value) {
        if (!node) return new Node(value);

        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        // Left Left Case
        if (balance > 1 && value < node->left->data)
            return rotateRight(node);

        // Right Right Case
        if (balance < -1 && value > node->right->data)
            return rotateLeft(node);

        // Left Right Case
        if (balance > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // Right Left Case
        if (balance < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left) current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, int value) {
        if (!root) return root;

        if (value < root->data)
            root->left = deleteNode(root->left, value);
        else if (value > root->data)
            root->right = deleteNode(root->right, value);
        else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }

        if (!root) return root;

        root->height = 1 + max(height(root->left), height(root->right));
        int balance = getBalance(root);

        // Left Left Case
        if (balance > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);

        // Left Right Case
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // Right Right Case
        if (balance < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);

        // Right Left Case
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    bool search(Node* node, int value) {
        if (!node) return false;
        if (node->data == value) return true;
        if (value < node->data)
            return search(node->left, value);
        else
            return search(node->right, value);
    }

    void inOrder(Node* node) {
        if (!node) return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }
};

int main() {
    AVL tree;

    tree.root = tree.insert(tree.root, 10);
    tree.root = tree.insert(tree.root, 20);
    tree.root = tree.insert(tree.root, 30);
    tree.root = tree.insert(tree.root, 40);
    tree.root = tree.insert(tree.root, 50);
    tree.root = tree.insert(tree.root, 25);

    cout << "In-order traversal: ";
    tree.inOrder(tree.root);
    cout << endl;

    tree.root = tree.deleteNode(tree.root, 50);
    cout << "In-order after deleting 50: ";
    tree.inOrder(tree.root);
    cout << endl;

    cout << "Search 25: " << (tree.search(tree.root, 25) ? "Found" : "Not Found") << endl;
    cout << "Search 100: " << (tree.search(tree.root, 100) ? "Found" : "Not Found") << endl;

    return 0;
}

/*
OUTPUT:
In-order traversal: 10 20 25 30 40 50 
In-order after deleting 50: 10 20 25 30 40 
Search 25: Found
Search 100: Not Found
*/