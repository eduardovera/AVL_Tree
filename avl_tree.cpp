#include "avl_tree.h"
#include <iostream>

using namespace std;

namespace Tree {

    /**
     * Inserts a value into a tree. This method is called recursively.
     * On first call, receives a tree root node. In each call, recomputes
     * nodes height and balance and make rotations if necessary.
     * @param node
     * @param info
     * @return
     */
    Node* insert(Node *node, const int &info) {

        if (node == NULL) {
            node = (Node*)malloc(sizeof(Node));
            node->left = NULL;
            node->right = NULL;
            node->info = info;
            node->balance = 0;
            node->height = 0;
            return node;
        } else {
            if (info < node->info) {
                node->left = insert(node->left, info);
            } else if (info > node->info) {
                node->right = insert(node->right, info);
            } else {
                cout << "Couldn't add node " << info << ": node is already on tree." << endl;
            }
        }
        resetHeightAndBalance(node);
        node = fix(node);
        return node;
    }

    /**
     * Removes a value from a tree. This method is called recursively.
     * On first call, receives a tree root node. In each call, recomputes
     * nodes height and balance and make rotations if necessary.
     * @see removeNodeReference(Node *)
     * @param node
     * @param info
     * @return
     */
    Node *remove(Node *node, const int &info) {
        Node *ptr = node;
        Node *ptrParent = node;
        int direction = 0;

        do {
            if (ptr->info == info) {
                Node *newReference = removeNodeReference(ptr);
                resetHeightAndBalance(newReference);
                newReference = fix(newReference);
                if (direction == +1) {
                    ptrParent->right = newReference;
                } else if (direction == -1) {
                    ptrParent->left = newReference;
                } else {
                    return newReference;
                }
                resetHeightAndBalance(node);
                node = fix(node);
                return node;
            } else {
                ptrParent = ptr;
                if (info < ptr->info) {
                    direction = -1;
                    ptr = ptr->left;
                } else if (info > ptr->info) {
                    direction = +1;
                    ptr = ptr->right;
                }
            }
        } while (ptr != NULL);
        cout << "Couldn't remove node " << info << ": node not found." << endl;
        return node;
    }

    /**
     * Removes a reference to a node.
     * - If node is a leaf, the method just removes it.
     * - If one of the children is null, removes parent and
     * returns the not null child.
     * - Otherwise, replaces node content with the rightmost child
     * and removes that node.
     * @param node
     * @return
     */
    Node *removeNodeReference(Node *node) {
        Node *ptr;
        if (node->left == NULL && node->right == NULL) {
            free(node);
            return NULL;
        } else if (node->left == NULL && node->right != NULL) {
            ptr = node->right;
            free(node);
            return ptr;
        } else if (node->left != NULL && node->right == NULL) {
            ptr = node->left;
            free(node);
            return ptr;
        } else {
            if  (node->left->right == NULL) {
                ptr = node->left;
                node->left->right = node->right;
                free(node);
                return ptr;
            } else {
                Node *ptrParent;
                ptr = node->left;
                while (ptr->right != NULL) {
                    ptrParent = ptr;
                    ptr = ptr->right;
                }
                if (ptr->left != NULL) {
                    ptrParent->right = ptr->left;
                } else {
                    ptrParent->right = NULL;
                }
                ptr->right = node->right;
                ptr->left = node->left;
                free(node);
                return ptr;
            }
        }
        return NULL;
    }

    Node *search(Node *node, const int &info) {
        if (node == NULL) {
            cout << "Couldn't find node " << info << ": node is not on tree. Returning NULL..." << endl;
            return NULL;
        } else {
            if (info < node->info)  {
                node = search(node->left, info);
            } else if (info > node->info) {
                node = search(node->right, info);
            }
        }
        return node;
    }

    /**
     * Fixes a tree configuration by rotations.
     * - If a node has a inverse balance in relation to
     * his parent after the insertion, a double rotation
     * on parent must be done. The direction depends only
     * of the balance.
     * - If both has the same balance signal, a single rotation
     * on unbalanced node must be done.
     * @param node
     * @return
     */
    Node *fix(Node* node) {
        if (node != NULL) {
            if (node->balance >= 2) {
                if (node->left && node->left->balance > 0) {
                    cout << "Rotacao simples a direita no node " << node->info << endl;
                    node = singleRotationRight(node);
                } else {
                    cout << "Rotacao dupla a direita no node " << node->info << endl;
                    node = doubleRotationRight(node);
                }
            } else if (node->balance <= -2) {
                if (node->right && node->right->balance < 0) {
                    cout << "Rotacao simples a esquerda no node " << node->info << endl;
                    node = singleRotationLeft(node);
                } else {
                    cout << "Rotacao dupla a esquerda no node " << node->info << endl;
                    node = doubleRotationLeft(node);
                }
            }
            resetHeightAndBalance(node);
            node->left = fix(node->left);
            node->right = fix(node->right);
        }
        return node;
    }
    /**
     * Prints all nodes of a tree or subtree according
     * to the following order:
     * 1º - Parent node;
     * 2º - Left child;
     * 3º - Right child;
     * @param node
     */
    void printPreOrder(Node *node) {
        if (node != NULL) {
            cout << node->info  << "\t" << node->height << "\t" << node->balance << endl;
            printPreOrder(node->left);
            printPreOrder(node->right);
        }
    }

    /**
     * Recalculates a node height and balance and set it into the node.
     * Height is given by: 1 + max(left_subtree, right_subtree);
     * Balance is given by: height(left_child) - height(right_child);
     * @brief resetHeightAndBalance
     * @param node
     */
    void resetHeightAndBalance(Node *node) {
        int h_left = 0;
        int h_right = 0;
        if (node != NULL) {
            if (node->left == NULL && node->right == NULL) {
                node->height = 0;
                node->balance = 0;
            } else {
                if (node->left != NULL) {
                    resetHeightAndBalance(node->left);
                    h_left = node->left->height + 1;
                }
                if (node->right != NULL) {
                    resetHeightAndBalance(node->right);
                    h_right = node->right->height + 1;
                }
                node->height = h_left > h_right ? h_left : h_right;
                node->balance = h_left - h_right;
            }
        }
    }
    /**
     * @brief singleRotationLeft
     * @param oldRoot
     * @return
     */
    Node* singleRotationLeft(Node *oldRoot) {
        Node *newRoot = oldRoot->right;
        if (newRoot->left != NULL) {
            oldRoot->right = newRoot->left;
        } else {
            oldRoot->right = NULL;
        }
        newRoot->left = oldRoot;
        return newRoot;
    }
    /**
     * @brief singleRotationRight
     * @param oldRoot
     * @return
     */
    Node* singleRotationRight(Node *oldRoot) {
        Node *newRoot = oldRoot->left;
        if (newRoot->right != NULL) {
            oldRoot->left = newRoot->right;
        } else {
            oldRoot->left = NULL;
        }
        newRoot->right = oldRoot;
        return newRoot;
    }
    /**
     * @brief doubleRotationRight
     * @param oldRoot
     * @return
     */
    Node* doubleRotationRight(Node *oldRoot) {
        Node *aux = oldRoot->left;
        Node *newRoot = aux->right;
        if (newRoot->left != NULL) {
            aux->right = newRoot->left;
        } else {
            aux->right = NULL;
        }
        if (newRoot->right != NULL) {
            oldRoot->left = newRoot->right;
        } else {
            oldRoot->left = NULL;
        }

        newRoot->left = aux;
        newRoot->right = oldRoot;
        return newRoot;
    }
    /**
     * @brief doubleRotationLeft
     * @param oldRoot
     * @return
     */
    Node* doubleRotationLeft(Node *oldRoot) {
        Node *aux = oldRoot->right;
        Node *newRoot = aux->left;

        if (newRoot->left != NULL) {
            oldRoot->right = newRoot->left;
        } else {
            oldRoot->right = NULL;
        }
        if (newRoot->right != NULL) {
            aux->left = newRoot->right;
        } else {
            aux->left = NULL;
        }
        newRoot->left = oldRoot;
        newRoot->right = aux;
        return newRoot;
    }
    /**
     * For each node, generates a string on .dot format
     * for graph drawing and inserts it into 'nodes' and
     * 'relationships'.
     * @see drawTreeR(Node *, string &, string &)
     * @param node
     * @param nodes
     * @param relationships
     */
    void drawTreeR(Node *node, string &nodes, string &relationships) {
        if (node != NULL) {
            nodes.append(putNodeOnDotFormat(node->info));
            nodes.append("\n");
            if (node->left != NULL) {
                relationships.append(putRelationshipOnDotFormat(node->info, node->left->info, -1));
                relationships.append("\n");
                drawTreeR(node->left, nodes, relationships);
            }
            if (node->right != NULL) {
                relationships.append(putRelationshipOnDotFormat(node->info, node->right->info, +1));
                relationships.append("\n");
                drawTreeR(node->right, nodes, relationships);
            }
        }
    }

    /**
     * Generate, compile and display a .dot file based on
     * tree nodes. Writes it on a .png file.
     * @param node
     */
    void drawTree(Node *node) {
        string header = "digraph g {\n";
        header.append("node [shape = record,height=.1];\n");
        string nodes;
        string relationships;
        drawTreeR(node, nodes, relationships);
        header.append(nodes);
        header.append(relationships);
        header.append("}");
        stringToFile(header, "temp.dot");
        system("dot -Tpng temp.dot -o output.png");
//        system("rm temp.dot");
        system("echo OFF");
        system("taskkill >nul 2>&1 /FI \"WINDOWTITLE eq output - Visualizador de Fotos do Windows");
        system("output.png");

    }
}
