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
        In_Order_Traversal(root->left);
        cout << root->info << endl;
        
        In_Order_Traversal(root->right);
    }
    void Post_Order_Traversal(Node* root) {
        if (root == nullptr) {
            return;
        }
        Post_Order_Traversal(root->left);
        Post_Order_Traversal(root->right);
        cout << root->info << endl;
    }

    Node* Left_Brother(Node* temp, int num) {
        if (temp == nullptr) { return nullptr; }
        if (temp->right && temp->right->info == num) {
            return temp->left;
        }
        Node* LeftBrother = Left_Brother(temp->left, num);
        if (LeftBrother) {
            return LeftBrother;
        }
        return Left_Brother(temp->right, num);
    }

    Node* Right_Brother(Node* root, int num) {
        if (root == nullptr) { return nullptr; }
        if (root->left && root->left->info == num) {
            return root->right;
        }
        Node* RightBrother = Right_Brother(root->right, num);
        if (RightBrother) {
            return RightBrother;
        }
        return Right_Brother(root->left, num);
    }

    Node* Parent(Node* root, int num) {
        if (root == nullptr) {
            return nullptr;
        }
        if ((root->left && root->left->info == num) || (root->right && root->right->info == num)) {
            return root;
        }
        Node* LeftParent = Parent(root->left, num);
        if (LeftParent) {
            return LeftParent;
        }
        return Parent(root->right, num);
    }

    pair<Node*, Node*> Child(Node* root, int num) {
        if (root == nullptr) {
            return { nullptr, nullptr };
        }
        if (root->info == num) {
            return { root->left, root->right };
        }
        auto LeftChildren = Child(root->left, num);
        if (LeftChildren.first || LeftChildren.second) {
            return LeftChildren;
        }
        return Child(root->right, num);
    }
};
int main() {
    Binary_Tree tree;
    Node* root = nullptr;
    int choice;
    bool treeBuilt = false;

    while (true) {
        cout << "Welcome to Binary Tree Implementation" << endl
            << "1. Build Tree" << endl
            << "2. Pre-Order Traversal" << endl
            << "3. In-Order Traversal" << endl
            << "4. Post-Order Traversal" << endl
            << "5. Check Parent of a node"<<endl
            << "6. Check Left Brother of a node"<<endl
            << "7. Check Right Brother of a node"<<endl
            << "8. Check both children of a parent"<<endl
            << "9. Exit" << endl
            << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int size;
            cout << "Enter the number of elements in the array e.g (13): ";
            cin >> size;

            if (size <= 0) {
                cout << "Invalid size. Please try again.\n";
            }
            else {
                int* arr = new int[size];
                cout << "Enter the elements (-1 for NULL nodes) e.g (1,2,4,-1,-1,5,-1,-1,3,-1,6,-1,-1):\n";
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
        else if(choice==5){
            int number;
            cout << "Enter the node value to find its parent: ";
            cin >> number;

            Node* parent = tree.Parent(root, number);
            if (parent) {
                cout << "The parent of " << number << " is: " << parent->info << endl;
            }
            else {
                cout << "No parent found." << endl;
            }
        }
        else if(choice==6){
            int number;
            cout << "Enter the node value to find its left brother: ";
            cin >> number;

            Node* leftBrother = tree.Left_Brother(root, number);
            if (leftBrother) {
                cout << "The left brother of " << number << " is: " << leftBrother->info << endl;
            }
            else {
                cout << "No left brother found." << endl;
            }
        }
        else if(choice==7){
            int number;
            cout << "Enter the node value to find its right brother: ";
            cin >> number;

            Node* rightBrother = tree.Right_Brother(root, number);
            if (rightBrother) {
                cout << "The right brother of " << number << " is: " << rightBrother->info << endl;
            }
            else {
                cout << "No right brother found." << endl;
            }
        }
        else if(choice==8){
            int parentValue;
            cout << "Enter parent value to find its children: ";
            cin >> parentValue;

            auto children = tree.Child(root, parentValue);
            if (children.first) {
                cout << "Left child of " << parentValue << ": " << children.first->info << endl;
            }
            else {
                cout << "No left child of " << parentValue << endl;
            }

            if (children.second) {
                cout << "Right child of " << parentValue << ": " << children.second->info << endl;
            }
            else {
                cout << "No right child of " << parentValue << endl;
            }
        }
        else if (choice == 9) {
            cout << "Exiting program.\n";
            return 0;

        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
        system("pause");
        system("CLS");

    }

    return 0;
}
