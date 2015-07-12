#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <iostream>

using namespace std;

namespace Tree {

    struct Node {
        int info;
        int balance;
        int height;
        Node *left;
        Node *right;
    };

    Node* insert(Node *, const int &);
    Node* remove(Node *, const int &);
    Node* removeNodeReference(Node *);
    Node* search(Node *, const int &);
    Node* fix(Node*);
    void printPreOrder();
    Node* singleRotationRight(Node *);
    Node* singleRotationLeft(Node *);
    Node* doubleRotationRight(Node *);
    Node* doubleRotationLeft(Node *);

    void resetHeightAndBalance(Node *);
    void drawTree();
    void drawTreeR(Node *, string &, string &);

}
#endif // AVL_TREE_H
