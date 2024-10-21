#include<iostream>
using namespace std;

template <class t>
class Queue {
private:
    int front, rear;
    t* Array;
    int arraysize;
public:
    int count;

    Queue(int size = 2) { 
        rear = 0;
        front = 0;
        count = 0;
        arraysize = size; 
        Array = new t[arraysize];
    }

    ~Queue() {
        delete[] Array;
    }

    bool isEmpty() {
        return count == 0;
    }

    bool isFull() {
        return count == arraysize;
    }

    void Push(t value) {
        if (!isFull()) {
            Array[rear] = value;
            rear = (rear + 1) % arraysize;
            count++;
        }
        else {
            cout << "Queue Overflow" << endl;
        }
    }

    t Pop() {
        if (!isEmpty()) {
            t temp = Array[front];
            front = (front + 1) % arraysize;
            count--;
            return temp;
        }
        else {
            cout << "Queue Underflow" << endl;
            return "";
        }
    }
};

int main() {
    int arraysize;
    cout << "How many persons will be there: ";
    cin >> arraysize;

    Queue<string> TeacherQueue(arraysize), StudentQueue(arraysize), AdminQueue(arraysize), MainQueue(arraysize * 3);

    string choice;

    while (true) {
        cout << "Welcome to Priority Queue implementation." << endl;
        cout << "1. Add Admin" << endl
            << "2. Add Teacher" << endl
            << "3. Add Student" << endl
            << "4. Display" << endl
            << "5. Exit" << endl
            << "Enter your choice: ";
        cin >> choice;

        if (choice[0] == '1') {
            for (int i = 0; i < arraysize; i++) {
                string Name;
                cout << "Enter Admin Name: ";
                cin >> Name;
                AdminQueue.Push(Name);
            }
        }
        else if (choice[0] == '2') {
            for (int i = 0; i < arraysize; i++) {
                string Name;
                cout << "Enter Teacher Name: ";
                cin >> Name;
                TeacherQueue.Push(Name);
            }
        }
        else if (choice[0] == '3') {
            for (int i = 0; i < arraysize; i++) {
                string Name;
                cout << "Enter Student Name: ";
                cin >> Name;
                StudentQueue.Push(Name);
            }
        }
        else if (choice[0] == '4') {
            int teachercount = TeacherQueue.count;
            int studentcount = StudentQueue.count;
            int admincount = AdminQueue.count;

            for (int i = 0; i < admincount; i++) {
                MainQueue.Push(AdminQueue.Pop());
            }
            for (int i = 0; i < teachercount; i++) {
                MainQueue.Push(TeacherQueue.Pop());
            }
            for (int i = 0; i < studentcount; i++) {
                MainQueue.Push(StudentQueue.Pop());
            }

            int maincount = MainQueue.count;
            cout << "Displaying Priority wise data: " << endl;
            for (int i = 0; i < maincount; i++) {
                cout << (i + 1) << ". " << MainQueue.Pop() << endl;
            }
        }
        else if (choice[0] == '5') {
            cout << "Exiting Priority Queue Program." << endl;
            break;
        }
        else {
            cout << "Invalid input, please try again." << endl;
        }
    }

    return 0;
}
