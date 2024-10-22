#include<iostream>
using namespace std;

template <class Type>
class Stack {
private:
	int top;
	Type* Array = new Type[100];
public:
	Stack() { top = -1; }
	~Stack() {};
	bool isEmpty() {
		if (top < 0) {
			cout << "Stack is Empty Nothing to POP" << endl;
			return true;
		}
		else return false;
	}
	bool isFull() {
		if (top >= 99) {
			cout << "Stack is FUll can't Push" << endl;
			return true;
		}
		else return false;
	}
	void Push(Type item) {
		if (isFull() == false) {
			top++;
			Array[top] = item;
		}
	}
	Type  Pop() {
		if (isEmpty() == false) {
			Type character = Array[top];
			top--;
			return character;

		}
	}

};

void main() {
	Stack <char> Palindrome;
	string word, palindromcheck;
	cout << "Enter the word: ";
	cin >> word;
	for (int i = 0; i < word.length(); i++)
		Palindrome.Push(word[i]);
	for (int i = 0; i < word.length(); i++)
	{
		palindromcheck += Palindrome.Pop();
	}
	if (palindromcheck == word) {
		cout << "It is Palindrome." << endl;
	}
	else {
		cout << "Not a Palindrome." << endl;
	}
}