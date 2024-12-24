#include <iostream>
#include <queue>

class Node
{
public:
    int data;
    Node* left;
    Node* right;

    Node(int key)
    {
        data = key;
        left = right = nullptr;
    }
};

// Breadth-First Search
void BFS(Node* root)
{
    if (root == nullptr)
    {
        return;
    }
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty())
    {
        Node* node = q.front();
        q.pop();
        std::cout << node->data << " ";
        if (node->left != nullptr)
        {
            q.push(node->left);
        }
        if (node->right != nullptr)
        {
            q.push(node->right);
        }
    }
}

// Function to build the tree with user input
Node* buildTree()
{
    int data;
    std::cout << "Enter node data (enter -1 to indicate no node): ";
    std::cin >> data;

    // If the user enters -1, it means there is no node to add at this position
    if (data == -1)
    {
        return nullptr;
    }

    Node* node = new Node(data);

    // Recursively build the left and right subtrees
    std::cout << "Enter left child of " << data << ":\n";
    node->left = buildTree();
    std::cout << "Enter right child of " << data << ":\n";
    node->right = buildTree();

    return node;
}

int main()
{
    // Build the tree from user input
    std::cout << "Build the tree:\n";
    Node* root = buildTree();

    std::cout << "Breadth-First Search (BFS) of the tree:\n";
    BFS(root);

    return 0;
}
