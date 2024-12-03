#include<iostream>
using namespace std;

struct Node {
    int info;
    Node* left;
    Node* right;
    Node* parent;
};

Node* get_node() {
    Node* newnode = new Node();
    newnode->left = nullptr;
    newnode->right = nullptr;
    newnode->parent = nullptr;
    return newnode;
}

class Binary_Tree {
private:
    int itr = -1;

public:
    Binary_Tree() { }

    Node* maketree(int x) {
        Node* p = get_node();
        p->info = x;
        p->left = NULL;
        p->right = NULL;
        return (p);
    }

    Node* Build_Tree(int arr[], int size) {
        itr++;
        if (arr[itr] == -1 || itr >= size) {
            return NULL;
        }
        Node* newnode = maketree(arr[itr]);
        newnode->left = Build_Tree(arr, size);
        /*   if (newnode->left) {
               newnode->left->parent = newnode;
           }*/
        newnode->right = Build_Tree(arr, size);
        /* if (newnode->right) {
             newnode->right->parent = newnode;
         }*/
        return newnode;
    }
    void Pre_Order_Traversal(Node* root) {
        if (root == nullptr) {
            return;
        }
        cout << root->info << endl;
        Pre_Order_Traversal(root->left);
        Pre_Order_Traversal(root->right);
    }
    void In_Order_Traversal(Node* root) {
        if (root == nullptr) {
            return;
        }
        Pre_Order_Traversal(root->left);
        cout << root->info << endl;
        
        Pre_Order_Traversal(root->right);
    }
    void Post_Order_Traversal(Node* root) {
        if (root == nullptr) {
            return;
        }
        Pre_Order_Traversal(root->left);
        Pre_Order_Traversal(root->right);
        cout << root->info << endl;
    }

};
int main() {
    Binary_Tree tree;
    Node* root = nullptr;
    int choice;
    bool treeBuilt = false;

    while (true) {
        cout << "Menu:" << endl
            << "1. Build Tree" << endl
            << "2. Pre-Order Traversal" << endl
            << "3. In-Order Traversal" << endl
            << "4. Post-Order Traversal" << endl
            << "5. Exit" << endl
            << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int size;
            cout << "Enter the number of elements in the array e.g (17): ";
            cin >> size;

            if (size <= 0) {
                cout << "Invalid size. Please try again.\n";
            }
            else {
                int* arr = new int[size];
                cout << "Enter the elements (-1 for NULL nodes):\n";
                for (int i = 0; i < size; i++) {
                    cin >> arr[i];
                }

                root = tree.Build_Tree(arr, size);
                delete[] arr;
                treeBuilt = true;
                cout << "Tree built successfully.\n";
            }

        }
        else if (choice == 2) {
            if (treeBuilt) {
                cout << "Pre-Order Traversal: ";
                tree.Pre_Order_Traversal(root);
                cout << endl;
            }
            else {
                cout << "Tree not built yet. Please build the tree first.\n";
            }

        }
        else if (choice == 3) {
            if (treeBuilt) {
                cout << "In-Order Traversal: ";
                tree.In_Order_Traversal(root);
                cout << endl;
            }
            else {
                cout << "Tree not built yet. Please build the tree first.\n";
            }

        }
        else if (choice == 4) {
            if (treeBuilt) {
                cout << "Post-Order Traversal: ";
                tree.Post_Order_Traversal(root);
                cout << endl;
            }
            else {
                cout << "Tree not built yet. Please build the tree first.\n";
            }

        }
        else if (choice == 5) {
            cout << "Exiting program.\n";
            return 0;

        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
