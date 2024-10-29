#include<iostream>
using namespace std;
template<class t>
struct Node {
	t item;
	Node* next;
};
template<class t>
class Linkedlist {
private:
	Node<t>* head=NULL;
public:
	Linkedlist() {};
	void insertatbegining(t value) {
		Node<t> * newnode = new Node<t>();
		newnode->item = value;
		newnode->next = head;
		head = newnode;
	}
	void insertatend(t value) {
	
		Node<t> * newnode =new Node<t>();
		newnode -> item = value;
		newnode->next = NULL;
		if (!head) {
			head = newnode;
			return;
		}
		Node<t>* temp =head;
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = newnode;
	}
	void insertatmiddle(t value, int position) {
		Node <t> * newnode = new Node<t>();
		newnode->item = value;
		Node <t> * temp = head;
		for (int i = 1; i < position; i++) {
			temp = temp->next;
		}
		if (!temp) {
			cout << "position out of range"<<endl;
			delete newnode;
			/*return;*/
		}
		newnode->next = temp->next;
		temp->next = newnode;
	}
	t deleteFromBegining() {
		if (!head) {
			cout << "List is already empty." << endl;
			/*return;*/
		}
		
		t value;
		Node<t> * temp = head;
		value = head->item;
		head = head->next;
		delete temp;
		return value;
	}
	void deleteFromEnd(t & value) {
		if (!head) {
			cout << "List is Empty" << endl;
			return;
		}
		if (!head->next) {
			delete head;
			head = NULL;
			return;
		}
		Node<t>* temp = head;
		while (temp->next) {
			temp = temp->next;
		}
		value = temp->item;
		delete temp->next;
		temp->next = NULL;
		return;
	}
	void deleteFromMiddle(int position, t& value) {
		if (position < 1) {
			cout << "Position should be greater than 1" << endl;
		
		}
		if (position == 1) {
			deleteFromBegining();
		}
		
		Node<t>* temp = head;
		for (int i = 1; i < position; i++) {
			if (!temp) {
				cout << "Out of range." << endl;
				return;
			}
			temp = temp->next;
		}
		
		
		Node<t>* deletenode = temp->next;
		temp->next = temp->next->next;
		value = temp->item;
		delete temp->next;
		
	}
	void display() {
		Node<t>* temp = head;
		if (!head) {
			cout << "No item in List" << endl;
			return;
		}
		while (temp) {
			cout << temp->item;
			if (temp->next) {
				cout << " -> ";
			}
			temp = temp->next;
		}
		cout << " -> NULL" << endl;
	}

};

int main()
{
	Linkedlist<int> List;
	string choice;
	while (choice != "7") {
		cout << "Welcome to Linked List Implementation" << endl
			<< "1) Insert at Beginning" << endl
			<< "2) Insert at End" << endl
			<< "3) Insert at Middle" << endl
			<< "4) Delete from Begining" << endl
			<< "5) Delete from End" << endl
			<< "6) Delete from Middle" << endl
			<< "7) Display"<<endl
			<< "8) Exit" << endl << "\nEnter your Choice: ";
		cin >> choice;
		if (choice == "1") {
			int value;
			cout << "Enter the value: ";
			cin >> value;
			List.insertatbegining(value);
		}
		else if (choice == "2") {
			int value;
			cout << "Enter the value: ";
			cin >> value;
			List.insertatend(value);
		}
		else if (choice == "3") {
			int value,position;
			cout << "Enter the value: ";
			cin >> value;
			cout << "Enter the position: ";
			cin >> position;
			List.insertatmiddle(value, position);
		}
		else if (choice == "4") {
			cout<<"Value:" << List.deleteFromBegining()<<endl;
		}
		else if (choice == "5") {
			int value = NULL;
			List.deleteFromEnd(value);
			if (value) {
				cout << "Value: " << value<<endl;
			}
			
		}
		else if (choice == "6") {
			int position, value=NULL;
			cout << "Enter the position from where you want to delete: ";
			cin >> position;
			List.deleteFromMiddle(position, value);
			if (value) {
				cout << " Value: " << value;
			}
			}
		else if (choice == "7") {
			List.display();
		}
		else if (choice == "8") {
			cout << "Exiting" << endl;
			exit;
		}
	}

}