#include <bits/stdc++.h>
using namespace std;

enum Color { RED, BLACK };

struct Node {
    int data;
    Color color;
    Node *left, *right, *parent;

    Node(int value) : data(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
public:
    Node* root;

    RedBlackTree() : root(nullptr) {}

    void rotateLeft(Node*& root, Node*& pt) {
        Node* pt_right = pt->right;
        pt->right = pt_right->left;

        if (pt->right) pt->right->parent = pt;
        pt_right->parent = pt->parent;

        if (!pt->parent) 
            root = pt_right;
        else if (pt == pt->parent->left) 
            pt->parent->left = pt_right;
        else 
            pt->parent->right = pt_right;

        pt_right->left = pt;
        pt->parent = pt_right;
    }

    void rotateRight(Node*& root, Node*& pt) {
        Node* pt_left = pt->left;
        pt->left = pt_left->right;

        if (pt->left) pt->left->parent = pt;
        pt_left->parent = pt->parent;

        if (!pt->parent) 
            root = pt_left;
        else if (pt == pt->parent->left) 
            pt->parent->left = pt_left;
        else 
            pt->parent->right = pt_left;

        pt_left->right = pt;
        pt->parent = pt_left;
    }

    void fixViolation(Node*& root, Node*& pt) {
        Node* parent_pt = nullptr;
        Node* grand_parent_pt = nullptr;

        while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;

            if (parent_pt == grand_parent_pt->left) {
                Node* uncle_pt = grand_parent_pt->right;

                if (uncle_pt && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    if (pt == parent_pt->right) {
                        rotateLeft(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }
                    rotateRight(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            } else {
                Node* uncle_pt = grand_parent_pt->left;

                if (uncle_pt && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    if (pt == parent_pt->left) {
                        rotateRight(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }
                    rotateLeft(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }
        root->color = BLACK;
    }

    void insert(const int& value) {
        Node* pt = new Node(value);
        root = BSTInsert(root, pt);
        fixViolation(root, pt);
    }

    Node* BSTInsert(Node* root, Node* pt) {
        if (!root) return pt;

        if (pt->data < root->data) {
            root->left = BSTInsert(root->left, pt);
            root->left->parent = root;
        } else if (pt->data > root->data) {
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }
        return root;
    }

    void inOrder(Node* node) {
        if (!node) return;
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }
};

int main() {
    RedBlackTree tree;
    tree.insert(7);
    tree.insert(3);
    tree.insert(18);
    tree.insert(10);
    tree.insert(22);

    cout << "In-order Traversal: ";
    tree.inOrder(tree.root);
    cout << endl;

    return 0;
}


/*
OUTPUT:
In-order Traversal: 3 7 10 18 22 
*/