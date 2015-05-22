#ifndef AVL_TREE_H
#define AVL_TREE_H


class AVL_Tree {
    struct Node {
        int info;
        Node *left;
        Node *right;
    };

public:
    AVL_Tree();
    void insert(int);
    void remove(int);
    Node* search(int);
};

#endif // AVL_TREE_H
