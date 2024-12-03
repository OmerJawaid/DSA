#include<iostream>
#include<string>
#include<vector>
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
    Node* root = nullptr;
    Binary_Tree bin1;

    while (true) {
        int* arr = nullptr;
        int size = 0;
        string choice;

        cout << "Welcome to Binary Tree implementation" << endl;
        cout << "1) Create Tree" << endl
            << "2) Check Parent of a node" << endl
            << "3) Check Left Brother of a node" << endl
            << "4) Check Right Brother of a node" << endl
            << "5) Check both children of a parent" << endl
            << "Enter your choice: ";
        getline(cin, choice);

        if (choice == "1") {
            cout << "Enter number of elements: ";
            cin >> size;

            arr = new int[size];
            cout << "Enter tree values in level order (use -1 for null nodes) e.g (1,2,4,-1,-1,5,-1,-1,3,-1,6,-1,-1): " << endl;

            for (int i = 0; i < size; ++i) {
                cin >> arr[i];
            }

            cin.ignore(); 
            root = bin1.Build_Tree(arr, size);
            cout << "Tree created successfully." << endl;

            delete[] arr; 
        }
        else if (choice == "2") {
            int number;
            cout << "Enter the node value to find its parent: ";
            cin >> number;

            Node* parent = bin1.Parent(root, number);
            if (parent) {
                cout << "The parent of " << number << " is: " << parent->info << endl;
            }
            else {
                cout << "No parent found." << endl;
            }
        }
        else if (choice == "3") {
            int number;
            cout << "Enter the node value to find its left brother: ";
            cin >> number;

            Node* leftBrother = bin1.Left_Brother(root, number);
            if (leftBrother) {
                cout << "The left brother of " << number << " is: " << leftBrother->info << endl;
            }
            else {
                cout << "No left brother found." << endl;
            }
        }
        else if (choice == "4") {
            int number;
            cout << "Enter the node value to find its right brother: ";
            cin >> number;

            Node* rightBrother = bin1.Right_Brother(root, number);
            if (rightBrother) {
                cout << "The right brother of " << number << " is: " << rightBrother->info << endl;
            }
            else {
                cout << "No right brother found." << endl;
            }
        }
        else if (choice == "5") {
            int parentValue;
            cout << "Enter parent value to find its children: ";
            cin >> parentValue;

            auto children = bin1.Child(root, parentValue);
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
        else {
            cout << "Incorrect Choice. Try again." << endl;
        }

        cin.ignore();
        cout << endl;
        system("pause");
        system("cls");
    }

    return 0;
}
