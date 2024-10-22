#include<iostream>
using namespace std;
int arraysize = 0;
template<class T>

class Queue {
private:
	int front, rear;
	T* Array;
	int count;
public:
	Queue() {
		 rear = 0;
		 front = 0;
		 count = 0;
		Array = new T[arraysize];
	};
	~Queue() {};
	bool isEmpty() {
		return count==0;
	}
	bool isFull() {
		return count == arraysize;
	}
	void Push(T value) {
		if(isFull()==false)
		{
			if (rear == arraysize-1)
			{
				Array[rear] = value;
				rear = (rear + 1) % arraysize;
				count++;
			}
			else {
				
				Array[rear] = value;
				rear++;
				count++;
			}
			/cout<<"Pushed: "+ value<<endl;/
		}
		else
			cout << "Queue OverFlow" << endl;
	}
	T Pop() {
		if (!isEmpty()) {
			if (front == arraysize - 1)
			{
				T temp = Array[front];
				front = (front + 1) % arraysize;

				count--;
				return temp;
			}
			else {
				T temp = Array[front];
				front++;
				count--;
				return temp;
			}
		}
		else
			cout << "Queue UnderFlow" << endl;
		
	}
};

int main() {
	arraysize = 5;
	Queue<int> q;
	string choice;
	while (true) {
		cout << "Welcome to Queue Implementation." << endl
			<< "1. Push a value." << endl
			<< "2. Pop a value" << endl
			<< "3. Exit" << endl
			<< "Enter your choice: ";
		cin >> choice;
		if (choice[0] == '1') {
			bool pushflag = true;
			while (pushflag) {
				
				int temp;
				string choice;
				cout << "Enter a value: ";
				cin >> temp;
				q.Push(temp);
				bool flag = true;
				while (flag)
				{
					cout << "Do you want to enter another value (y/n)? ";
					cin >> choice;
					if (choice[0] == 'Y' || choice[0] == 'y')
					{
						flag = false;
						pushflag = true;
					}
					else if (choice[0] == 'N' || choice[0] == 'n') {
						flag = false;
						pushflag = false;
					}
					else
					{
						cout << "Enter correct Value." << endl;
						continue;
					}
				}
			}
		}
		else if (choice[0] == '2') {
			bool popflag = true;
			while (popflag) {
				cout << "Pop Value is: " << q.Pop()<<endl;
				bool flag = true;
				while (flag)
				{
					cout << "Do you want to Pop another value (y/n)? ";
					cin >> choice;
					if (choice[0] == 'Y' || choice[0] == 'y')
					{
						flag = false;
						popflag = true;
					}
					else if (choice[0] == 'N' || choice[0] == 'n') {
						flag = false;
						popflag = false;
					}
					else
					{
						cout << "Enter correct Value." << endl;
						continue;
					}
				}
			}
		}
		else if (choice[0] == '3') {
			break;
		}
		else
			cout << "\nEnter a correct value.\n" << endl;
	}
}