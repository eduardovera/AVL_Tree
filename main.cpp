#include <QCoreApplication>
#include <utils.cpp>
#include <avl_tree.cpp>
#include <iostream>

using namespace std;
using namespace Tree;

/**
 * Read a Random Tree File and make node insertions and
 * node removals according to file. Returns a pointer to
 * resulting tree root node.
 * @param node
 * @param file
 * @return
 */
Node* readFile(Node *node, string file) {
    ifstream infile(file);
    string line;
    vector<string> tokens;
    getline(infile, line);
    split(tokens, line, " ");
    int sizeToAdd = stoi(tokens[1]);
    for (int i = 0; i < sizeToAdd; i++) {
        getline(infile, line);
        node = insert(node, stoi(line));
    }
    tokens.clear();
    getline(infile, line);
    split(tokens, line, " ");
    int sizeToRemove = stoi(tokens[1]);
    for (int i = 0; i < sizeToRemove - 1; i++) {
        getline(infile, line);
        node = remove(node, stoi(line));
    }
    resetHeightAndBalance(node);
    node = fix(node);
    return node;
}


int main(int argc, char *argv[]) {
    if (argc != 3 && argc != 5) {
        cout << "usage: "<< endl;
        cout << "AVL_Tree.exe -g nodesToAdd nodesToRemove file_name_to_be_generated" << endl;
        cout << "AVL_Tree.exe -r file_name_to_be_read" << endl;
        return 1;
    }

    if (strcmp(argv[1], "-g") == 0) {
        generateRandomData(atoi(argv[2]), atoi(argv[3]), argv[4]);
    } else if (strcmp(argv[1], "-r") == 0) {
        Node *tree = readFile(NULL, argv[2]);
        getchar();
        int option = 0;
        while (option > 0 || option < 7) {
            system("cls");
            cout << "-------------------- AVL TREE -----------------" << endl << endl;
            cout << "1..................Insert" << endl;
            cout << "2..................Remove" << endl;
            cout << "3..................Search" << endl;
            cout << "4..................Display tree" << endl;
            cout << "5..................Print pre-order" << endl;
            cout << "6..................Exit" << endl;
            cin >> option;

            switch (option) {
            int info;
            case 1: {
                system("cls");
                cout << "[INSERT] Value: " << endl;
                cin >> info;
                tree = insert(tree, info);
                getchar();
                getchar();
                break;
            }
            case 2: {
                system("cls");
                cout << "[REMOVE] Value: " << endl;
                cin >> info;
                tree = remove(tree, info);
                getchar();
                getchar();
                break;
            }
            case 3: {
                system("cls");
                cout << "[SEARCH] Value: " << endl;
                cin >> info;
                Node *n = search(tree, info);
                if (n != NULL) {
                    cout << "Found node: " << n->info << endl;
                    cout << "Height: " << n->height << endl;
                    cout << "Balance: " << n->balance << endl;
                }
                getchar();
                getchar();
                break;
            }
            case 4: {
                system("cls");
                drawTree(tree);
                break;
            }
            case 5: {
                system("cls");
                cout << "Node\tHeight\tBalance" << endl;
                cout << "------------------------" << endl;
                printPreOrder(tree);
                getchar();
                getchar();
                break;
            }
            case 6: {
                return 0;
            }
            default: {
                break;
            }
            }
        }
    }
    return 0;
}
