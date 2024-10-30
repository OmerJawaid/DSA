#include<iostream>
#include <cmath>
using namespace std;

struct Node {
	int coefficient;
	int exponent;
	Node* next;
};

class Polynomial {
private:
	Node* head;
public:
	Polynomial() : head(nullptr) {}
	~Polynomial() {};
	void insert_term(int coefficient, int exponent) {
		if (coefficient == 0)
			return;
		Node* newnode = new Node();
		newnode->coefficient = coefficient;
		newnode->exponent = exponent;

		if (!head || head->exponent < exponent) {
			newnode->next = head;
			head = newnode;
		
			return;
		}
		
		Node* temp = head;
		Node* previous = nullptr;

		while (temp && temp->exponent > exponent) {
			previous = temp;
			temp = temp->next;
		}

		if (temp && temp->exponent == exponent) {
			temp->coefficient += coefficient;
			delete newnode;
		}
		else {
			newnode->next = temp;
			if (previous) previous->next = newnode;
			else head = newnode;
		}
		
	}

	void display(string variable) {
		Node* temp = head;
		int count = 0;
		while (temp!=nullptr) {
			if (temp->coefficient <=-1) {
				
				cout << temp->coefficient << "x^" << temp->exponent;
			}
			else {
				if (temp->exponent == 0) {
					
						cout << " + " << temp->coefficient;
				}
				else {
					if (count == 0) {
						cout << variable << ":  " << temp->coefficient << "x^" << temp->exponent;
					}
					else{ cout << " + " << temp->coefficient << "x^" << temp->exponent; }
				}
			}
			temp = temp->next;
			count++;
		}
	}
	Polynomial operator + (Polynomial& second) {
		Polynomial result;
		Node* temp1 = head;
		Node* temp2 = second.head;
		while (temp1 || temp2) {
			if (temp1 && (!temp2 || temp1->exponent > temp2->exponent)) {
				result.insert_term(temp1->coefficient, temp1->exponent);
				temp1 = temp1->next;
			}
			else if (temp2 && (!temp1 || temp2->exponent > temp1->exponent)) {
				result.insert_term(temp2->coefficient, temp2->exponent);
				temp2 = temp2->next;
			}
			else {				
				result.insert_term(temp1->coefficient + temp2->coefficient, temp2->exponent);
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
		}
		return result;
	}
	
	Polynomial operator - (Polynomial& second) {
		Polynomial result;
		Node* temp1 = head;
		Node* temp2 = second.head;
		while (temp1 || temp2) {
			if (temp1 && (!temp2 || temp1->exponent > temp2->exponent)) {
				result.insert_term(temp1->coefficient, temp1->exponent);
				temp1 = temp1->next;
			}
			else if (temp2 && (!temp1 || temp2->exponent > temp1->exponent)) {
				result.insert_term(temp2->coefficient, temp2->exponent);
				temp2 = temp2->next;
			}
			else {
				result.insert_term(temp1->coefficient - temp2->coefficient, temp2->exponent);
				temp1 = temp1->next;
				temp2 = temp2->next;
			}
		}
		return result;
	}

	Polynomial operator *(Polynomial& second) {
		Polynomial result,result2;
		
		for (Node* temp1 = head; temp1 != nullptr; temp1 = temp1->next)
		{
			for (Node* temp2 = second.head; temp2 != nullptr; temp2 = temp2->next) {
				int New_Coffecient = temp1->coefficient * temp2->coefficient;
				int New_Exponent = temp1->exponent + temp2->exponent;
				result.insert_term(New_Coffecient, New_Exponent);
			}
			
		}
		
		Node* current = result.head;

		while (current != nullptr) {
			int coefficient_sum = current->coefficient;
			int exponent = current->exponent;

			Node* temp = current->next;
			while (temp != nullptr && temp->exponent == exponent) {
				coefficient_sum += temp->coefficient;
				temp = temp->next;
			}

			result2.insert_term(coefficient_sum, exponent);
			current = temp;
		}


		return result2;
		
	}

	int evaluate(int x) const {
		int result = 0;
		Node* temp = head;
		while (temp) {
			result += temp->coefficient * pow(x, temp->exponent);
			temp = temp->next;
		}
		return result;
	}
		
};

int main() {
	Polynomial p1, p2;

	int choice,coeffient, exponent;
	do {
		cout << "\nPolynomial Operations Menu:\n";
		cout << "1. Insert term into Polynomial 1\n";
		cout << "2. Insert term into Polynomial 2\n";
		cout << "3. Display Polynomial 1\n";
		cout << "4. Display Polynomial 2\n";
		cout << "5. Add Polynomials\n";
		cout << "6. Subtract Polynomials\n";
		cout << "7. Multiply Polynomials\n";
		cout << "8. Evaluate Polynomial 1\n";
		cout << "9. Evaluate Polynomial 2\n";
		cout << "0. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Enter coefficient and exponent for Polynomial 1: ";
			cin >> coeffient >> exponent;
			p1.insert_term(coeffient, exponent);
			break;
		case 2:
			cout << "Enter coeffient and exponent for Polynomial 2: ";
			cin >> coeffient >> exponent;
			p2.insert_term(coeffient, exponent);
			break;
		case 3:
			cout << "Polynomial 1: ";
			p1.display("p1");
			break;
		case 4:
			cout << "Polynomial 2: ";
			p2.display("p2");
			break;
		case 5: {
			Polynomial sum = p1 + p2;
			cout << "Sum: ";
			sum.display("p3");
			break;
		}
		case 6: {
			Polynomial diff = p1 - p2;
			cout << "Difference: ";
			diff.display("p3");
			break;
		}
		case 7: {
			Polynomial product = p1 * p2;
			cout << "Product: ";
			product.display("p3");
			break;
		}
		case 8: {
			int x;
			cout << "Enter value of x to evaluate Polynomial 1: ";
			cin >> x;
			cout << "Result: " << p1.evaluate(x) << endl;
			break;
		}
		case 9: {
			int x;
			cout << "Enter value of x to evaluate Polynomial 2: ";
			cin >> x;
			cout << "Result: " << p2.evaluate(x) << endl;
			break;
		}
		case 0:
			cout << "Exiting program." << endl;
			break;
		default:
			cout << "Invalid choice, please try again." << endl;
			break;
		}
		cout << "\n";
		system("pause");
		system("CLS");
	} while (choice != 0);

	return 0;
}