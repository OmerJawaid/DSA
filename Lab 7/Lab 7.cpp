#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<cstdio>
using namespace std;

struct Node {
    string name;
    int age, matchesPlayed, averageScore;
    Node* prev = NULL;
    Node* next = NULL;
};

class DLL
{
private:
    Node* head;
    Node* tail;
    int count;
public:
    DLL()
    {
        head = NULL;
        tail = NULL;
        count = 0;
    }

    bool isEmpty()
    {
        return head == NULL && tail == NULL;
    }

    void insert_at_head(string n, int a, int mP, int aS)
    {
        Node* temp = new Node();
        temp->name = n;
        temp->age = a;
        temp->matchesPlayed = mP;
        temp->averageScore = aS;

        if (head == NULL && tail == NULL)
        {
            head = tail = temp;
        }
        else
        {
            temp->next = head;
            head->prev = temp;
            head = temp;
        }
    }

    void insert_at_tail(string n, int a, int mP, int aS)
    {
        Node* temp = new Node();
        temp->name = n;
        temp->age = a;
        temp->matchesPlayed = mP;
        temp->averageScore = aS;

        if (head == NULL && tail == NULL)
        {
            head = tail = temp;
        }
        else
        {
            temp->prev = tail;
            tail->next = temp;
            tail = temp;
        }
    }

    void deletePlayer(string name)
    {
        if (isEmpty()) {
            cout << "List is empty. Cannot delete player." << endl;
            return;
        }

        Node* current = head;
        while (current && current->name != name) {
            current = current->next;
        }

        if (!current) {
            cout << "Player not found." << endl;
            return;
        }

        // If there's only one node in the list.
        if (current == head && current == tail) {
            head = tail = NULL;
        }
        else if (current == head) {
            head = head->next;
            head->prev = NULL;
        }
        else if (current == tail) {
            tail = tail->prev;
            tail->next = NULL;
        }
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        delete current;

        string file = name + ".txt";
        if (remove(file.c_str()) == 0) {
            cout << "Player file deleted successfully: " << file << endl;
        }
        else {
            perror("Error deleting file");
        }
    }

    void displayPlayer(string name)
    {
        ifstream fin(name + ".txt");
        if (!fin) {
            cerr << "Error: File for player '" << name << "' not found!" << endl;
            return;
        }

        cout << "Displaying data for player: " << name << endl;
        string line;
        while (getline(fin, line)) {
            cout << line << endl;
        }
        fin.close();
    }

    void displayAll()
    {
        if (isEmpty()) {
            cout << "List is empty." << endl;
            return;
        }

        Node* current = head;
        while (current) {
            cout << "Name: " << current->name
                << ", Age: " << current->age
                << ", Matches Played: " << current->matchesPlayed
                << ", Average Score: " << current->averageScore << endl;
            current = current->next;
        }
    }
};

int main()
{
    DLL l;
    string choice;

    do {
        cout << "\n1) Insert Player \n2) Remove Player \n3) Display Player \n4) Display All Players. \n0) Exit. \nEnter choice = ";
        cin >> choice;
        cout << endl;

        if (choice == "1")
        {
            string name;
            int age, matchesPlayed, averageScore;

            cout << "Enter Player Name = ";
            cin.ignore();
            getline(cin, name);
            if (name.empty())
            {
                cerr << "Error: Name cannot be empty.\n";
                continue;
            }

            cout << "Enter Player Age = ";
            cin >> age;
            if (cin.fail() || age <= 0)
            {
                cerr << "Error: Invalid age. Please enter a positive integer.\n";
                cin.clear();
                cin.ignore();
                continue;
            }

            cout << "Enter No. of Matches Played by Player = ";
            cin >> matchesPlayed;
            if (cin.fail() || matchesPlayed < 0)
            {
                cerr << "Error: Invalid matches played. Please enter a non-negative integer.\n";
                cin.clear();
                cin.ignore();
                continue;
            }

            cout << "Enter Average score of player = ";
            cin >> averageScore;
            if (cin.fail() || averageScore < 0)
            {
                cerr << "Error: Invalid average score. Please enter a non-negative integer.\n";
                cin.clear();
                cin.ignore();
                continue;
            }

            l.insert_at_tail(name, age, matchesPlayed, averageScore);

            ofstream fout(name + ".txt");
            if (!fout) {
                cerr << "Error creating file for " << name << endl;
                continue;
            }

            fout << "Name: " << name << endl;
            fout << "Age: " << age << endl;
            fout << "Matches Played: " << matchesPlayed << endl;
            fout << "Average Score: " << averageScore << endl;
            fout.close();
            cout << "Player file created successfully: " << name + ".txt" << endl;
        }
        else if (choice == "2")
        {
            string playerName;
            cout << "Enter Name of player you want to delete = ";
            cin.ignore();
            getline(cin, playerName);
            if (playerName.empty())
            {
                cerr << "Error: Name cannot be empty.\n";
                continue;
            }
            l.deletePlayer(playerName);
        }
        else if (choice == "3")
        {
            string name;
            cout << "Enter Name of Player = ";
            cin.ignore();
            getline(cin, name);
            if (name.empty())
            {
                cerr << "Error: Name cannot be empty.\n";
                continue;
            }
            l.displayPlayer(name);
        }
        else if (choice == "4")
        {
            l.displayAll();
        }
        else if (choice == "0")
        {
            cout << "Exiting" << endl;
        }
        else
        {
            cout << "Invalid input. Please enter a number between 0 and 4.\n";
        }
    } while (choice != "0");

    return 0;
}
