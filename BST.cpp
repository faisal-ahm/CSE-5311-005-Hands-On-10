#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node *left, *right;

    Node(int value) {
        data = value;
        left = right = nullptr;
    }
};

class BST {
public:
    Node* root;

    BST() : root(nullptr) {}

    Node* insert(Node* node, int value) {
        if (!node) return new Node(value);
        if (value < node->data) 
            node->left = insert(node->left, value);
        else 
            node->right = insert(node->right, value);
        return node;
    }

    bool search(Node* node, int value) {
        if (!node) return false;
        if (node->data == value) return true;
        if (value < node->data) 
            return search(node->left, value);
        else 
            return search(node->right, value);
    }

    Node* findMin(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    Node* remove(Node* node, int value) {
        if (!node) return nullptr;
        if (value < node->data)
            node->left = remove(node->left, value);
        else if (value > node->data)
            node->right = remove(node->right, value);
        else {
            if (!node->left) return node->right;
            if (!node->right) return node->left;
            Node* minRight = findMin(node->right);
            node->data = minRight->data;
            node->right = remove(node->right, minRight->data);
        }
        return node;
    }

    void inOrder(Node* node) {
        if (!node) return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }
};

int main() {
    BST tree;
    tree.root = tree.insert(tree.root, 5);
    tree.insert(tree.root, 3);
    tree.insert(tree.root, 8);
    tree.insert(tree.root, 2);
    tree.insert(tree.root, 4);

    cout << "In-order Traversal: ";
    tree.inOrder(tree.root);
    cout << endl;

    cout << "Search 3: " << (tree.search(tree.root, 3) ? "Found" : "Not Found") << endl;
    tree.root = tree.remove(tree.root, 3);
    cout << "In-order after deleting 3: ";
    tree.inOrder(tree.root);
    cout << endl;

    return 0;
}


/*
OUTPUT: 
In-order Traversal: 2 3 4 5 8 
Search 3: Found
In-order after deleting 3: 2 4 5 8
*/