#include<iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

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

class Sorting {
public:
	int* arr = new int[100000];

	long values;
public:
	Sorting(int propsize) {
		values = propsize;
	}
	void getnumber() {
		for (int i = 0; i < values; i++) {
			int number = rand() % 1000000;
			arr[i] = number;
		}
	}
	void selectionsort() {
		int Min = INT_MAX;
		for (int i = 0; i < values; i++) {
			for (int j = i + 1; j < values; j++) {
				if (arr[i] > arr[j]) {
					swap(arr[i], arr[j]);
				}
			}
		}
	}
	void bubblesort()
	{
		for (int i = 0; i < values - 1; i++) {
			for (int j = 0; j < values - i - 1; j++) {
				if (arr[j] > arr[j + 1]) {
					swap(arr[j], arr[j + 1]);
				}
			}
		}
	}
	int itr = 0;
	Node* maketree(int x) {
		Node* p = get_node();
		p->info = x;
		p->left = NULL;
		p->right = NULL;
		return (p);
	}
	Node* Build_Tree() {
		Node* root = nullptr;
		while (itr < values) {
			Node* newnode = maketree(arr[itr]);

			if (root == nullptr) {
				root = newnode;
			}
			else {
				Node* current = root;
				while (true) {
					if (arr[itr] < current->info) { // Insert to the left
						if (current->left == nullptr) {
							current->left = newnode;
							newnode->parent = current;
							break;
						}
						else {
							current = current->left;
						}
					}
					else { // Insert to the right
						if (current->right == nullptr) {
							current->right = newnode;
							newnode->parent = current;
							break;
						}
						else {
							current = current->right;
						}
					}
				}
			}
			itr++;
		}
		return root;
	}

	void inorder_traversal(Node* root, int* sortedArr, int& index) {
		if (root != nullptr) {
			inorder_traversal(root->left, sortedArr, index);
			sortedArr[index++] = root->info;
			inorder_traversal(root->right, sortedArr, index);
		}
	}

};

int main() {
	int sizes[] = { 10, 1000, 10000, 100000 };

	cout << "Size\tSelection Sort \t\tBubble Sort \t\tBST Sort" << endl;

	// For different sizes
	for (int size : sizes) {
		Sorting* sort = new Sorting(size);

		// Selection Sort Time Measurement
		sort->getnumber();
		auto start = high_resolution_clock::now();
		sort->selectionsort();
		auto stop = high_resolution_clock::now();
		auto selectionduration = duration_cast<milliseconds>(stop - start);
		cout << size << "\t" << selectionduration.count() << "\t\t\t";

		// Bubble Sort Time Measurement
		sort->getnumber();
		auto startbubble = high_resolution_clock::now();
		sort->bubblesort();
		auto stopbubble = high_resolution_clock::now();
		auto bubbleduration = duration_cast<milliseconds>(stopbubble - startbubble);
		cout << bubbleduration.count() << "\t\t\t";

		// BST Sort Time Measurement
		sort->getnumber();
		sort->itr = 0;
		Node* root = sort->Build_Tree();

		// Perform in-order traversal to get the sorted result
		int* bstSortedArr = new int[size];
		int index = 0;
		auto startbst = high_resolution_clock::now();
		sort->inorder_traversal(root, bstSortedArr, index);
		auto stopbst = high_resolution_clock::now();
		auto bstduration = duration_cast<milliseconds>(stopbst - startbst);
		cout << bstduration.count() << endl;

	}
}