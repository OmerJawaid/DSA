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
	int getrear() {
		return rear;
	}
	int getfront() {
		return front;
	}
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
			/*cout<<"Pushed: "+ value<<endl;*/
		}
		else
			cout << "Queue OverFlow" << endl;
	}
	void  Pop(T &item) {
		if (!isEmpty()) {
			if (front == arraysize - 1)
			{
				T temp = Array[front];
				front = (front + 1) % arraysize;

				count--;
				item= temp;
			}
			else {
				T temp = Array[front];
				front++;
				count--;
				item= temp;
			}
		}
		else
		{
			cout << "Queue UnderFlow" << endl;
			//return 0;
			exit(1);
		}
		
	}
};

int main() {
	arraysize = 5;
	Queue<int> q;
	string choice;
	cout << "What will be the size of queue : ";
	cin >> arraysize;
	while (true) {
		cout << "Welcome to Queue Implementation." << endl;
		cout << "Queue size is: " << arraysize << endl<<endl;
		cout << "1. Push a value." << endl
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
			int a;
			while (popflag) {
				q.Pop(a);
				cout << "Pop Value is: " << a<<endl;
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
				cout << "Rear: " << q.getrear() << endl;
				cout << "Front: " << q.getfront() << endl;

			}
		}
		else if (choice[0] == '3') {
			break;
		}
		else
			cout << "\nEnter a correct value.\n" << endl;
	}
}