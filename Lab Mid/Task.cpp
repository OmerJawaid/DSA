#include<iostream>
using namespace std;

struct Node {
	int runs;
	Node* next;
	Node* previous;
};

template<class t>
class List {
private:
	Node* head= nullptr;
	Node* tail = nullptr;

public:
	void addrunsatstart(t value) {
		Node* newnode = new Node();
		newnode->runs = value;
		if (!head) {
			head = tail = newnode;
		}
		else {
			head->previous = newnode;
			newnode->next = head;
			head = newnode;
			
		}
	}
	void addrunsatend(t value) {
		Node* newnode = new Node();
		newnode->runs = value;
		if (!tail) {
			head = tail = newnode;
		}
		else {
			tail->next = newnode;
			newnode->previous = tail;
			tail = newnode;
		}

	}
	void deletealloccurencesofscore(t score) {
		int count = 0;
		Node* temp = head;
		while (temp!=nullptr) {
			
			if (temp->runs == score) {
				Node* tobedeleted = temp;
				if (temp == head) {
					head = temp->next;
					if (head != nullptr) {
						head->previous = nullptr;
					}
				}
				else {
					temp->previous->next = temp->next;
					if (temp->next != nullptr) {
						temp->next->previous = temp->previous;
					}
				}

				temp = temp->next;
				delete tobedeleted;
				count++;
			}
			else
				temp = temp->next;
		}
		if (count == 0) {
			cout << "Score not found in any match" << endl;
		}
	}
	void displayscoreinsequence() {
		int count=0;
		Node* temp = head;
		if (head->runs != NULL) {
			cout << "Runs:\t";
			if (head->next == nullptr) {
				cout << head->runs <<" -> " << endl;
			}
			while (temp!= nullptr ) {

				cout << temp->runs << " -> ";
				temp = temp->next;
					count++;
			}
			cout << "NULL" << endl;
		}
		else {
			cout << "List is empty" << endl;
		}
	}
	void displayscoreinreversesequence() {
		int count = 0;
		Node* temp = tail;
		if (tail->runs != NULL) {
			cout << "Runs: \t";
			if (tail->previous == nullptr) {
				cout << tail->runs << endl;
			}
			while (temp != nullptr) {
				cout << temp->runs << " -> ";
				temp = temp->previous;
			}
			cout << "NULL" << endl;
		}
		else {
			cout << "List is empty" << endl;
		}
	}
	void highestandlowest() {
		int max = INT_MIN, min = INT_MAX;
		
		Node* itr = head;
		if (head->runs != NULL) {
			while (itr != nullptr) {
				if (itr->runs > max) {
					max = itr->runs;
				}
				if (itr->runs < min) {
					min = itr->runs;
				}
				itr = itr->next;
			}
				cout << "Highest: " << max<<endl;
				cout << "Lowest: " << min<<endl;
		}
		else {
			cout << "List is empty" << endl;
		}
	}
};

int main() {
	string choice;
	List<int> l1;
	
	while (true) {
		cout << "***********************************************************************" << endl
			<< "	Welcome to Cricket Teams's Performance System				" << endl
			<< "***********************************************************************" << endl;
		cout << "1) Add Runs at Start of list." << endl
			<< "2) Add Runs at End of the list." << endl
			<< "3) Delete Specific runs from the list" << endl
			<< "4) Display Score" << endl
			<< "5) Display Score in reverse order." << endl
			<< "6) Find the Highest and the Lowest runs value." << endl
			<< "7) Exit" << endl
			<< "\nEnter you Choice: ";
		cin >> choice;
		if (choice=="1") {
			while (true) {
				int runs;
				cout << "Enter the value of runs: ";
				if (!(cin >> runs)) {
					cout << "\nInvalid Input!!!!!!!" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(),'\n');
					continue;
				}
				l1.addrunsatstart(runs);
				cout << "Sucessfully Added." << endl << endl;
				system("pause");
				system("CLS");
				
				break;
			}
		}
		else if (choice == "2") {
			while (true) {
				int runs;
				cout << "Enter the value of runs: ";
			
				cin >> runs;
				if (!cin>>runs) {
					cout << "\nInvalid Input!!!!!!!" << endl;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					continue;
				}
				l1.addrunsatend(runs);
				cout << "Sucessfully Added." << endl << endl;
				system("pause");
				system("CLS");

				break;
			}
		}
		else if (choice == "3") {
			int runs;
			while (true) {
				cout << "Enter the runs you want to delete: ";
				cin >> runs;
				if (isdigit(runs)) {
					cout << "Invalid Input!!!!!!!!" << endl;
					continue;
				}
				l1.deletealloccurencesofscore(runs);
				cout << "Sucessfully Deleted the occurences." << endl;
				system("pause");
				system("CLS");
				break;
			}
		}
		else if (choice == "4") {
			l1.displayscoreinsequence();
			system("pause");
			system("CLS");
		}
		else if (choice == "5") {
			l1.displayscoreinreversesequence();
			system("pause");
			system("CLS");
		}
		else if (choice == "6") {
			l1.highestandlowest();
			system("pause");
			system("CLS");
		}
		else if (choice == "7") {
			exit(0);
		}
		else
		{
			cout << "Invaild Input Try Again!!!!" << endl;
			system("pause");
			system("CLS");

		}
	}
}