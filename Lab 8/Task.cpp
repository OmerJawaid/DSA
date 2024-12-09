#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct Player {
    string name;
    int age, matchesPlayed, averageScore;
    Player* prev = nullptr;
    Player* next = nullptr;
};

class PlayerList {
private:
    Player* head;
    Player* tail;

public:
    PlayerList() {
        head = nullptr;
        tail = nullptr;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    void AddPlayerToEnd(string name, int age, int matchesPlayed, int averageScore) {
        Player* newPlayer = new Player();
        newPlayer->name = name;
        newPlayer->age = age;
        newPlayer->matchesPlayed = matchesPlayed;
        newPlayer->averageScore = averageScore;

        if (isEmpty()) {
            head = tail = newPlayer;
        }
        else {
            newPlayer->prev = tail;
            tail->next = newPlayer;
            tail = newPlayer;
        }
    }

    void RemovePlayer(string name) {
        if (isEmpty()) {
            cout << " The player list is empty. Unable to remove the player." << endl;
            return;
        }

        Player* current = head;
        while (current != nullptr && current->name != name) {
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Player not found in the list." << endl;
            return;
        }

        if (current == head && current == tail) {
            head = tail = nullptr;
        }
        else if (current == head) {
            head = head->next;
            head->prev = nullptr;
        }
        else if (current == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        delete current;

        string filename = name + ".txt";
        if (remove(filename.c_str()) == 0) {
            cout << "Player file deleted: " << filename<< endl;
        }
        else {
            cout << "Error deleting player file: " << filename << endl;
        }
    }

    void ShowPlayer(string name) {
        ifstream file(name + ".txt");
        if (!file) {
            cout << "Player " << name << " not found in the records." << endl;
            return;
        }

        cout << "Displaying data for player: " << name << endl;
        string line;
        while (getline(file, line)) {
            cout << "   " << line << endl;
        }
        file.close();
    }

    void ShowAllPlayers() {
        if (isEmpty()) {
            cout << "No players to display. The list is empty." << endl;
            return;
        }

        cout << "All Players in the List: " << endl;
        Player* current = head;
        while (current != nullptr) {
            cout << "   Name: " << current->name
                << ", Age: " << current->age
                << ", Matches Played: " << current->matchesPlayed
                << ", Average Score: " << current->averageScore << endl;
            current = current->next;
        }
    }
};

int main() {
    PlayerList players;
    string choice;

    while (true) {
        cout << "===================================" << endl;
        cout << "       Player Management System   " << endl;
        cout << "===================================" << endl;
        cout << " 1) Add Player" << endl;
        cout << " 2) Remove Player" << endl;
        cout << " 3) Show Player Details" << endl;
        cout << " 4) Show All Players" << endl;
        cout << " 0) Exit" << endl;
        cout << "===================================" << endl;
        cout << " Enter your choice: ";
        getline(cin, choice);

        if (choice == "1") {
            string name;
            int age, matchesPlayed, averageScore;

            cout << "Enter Player Name: ";
            getline(cin, name);

            cout << "Enter Player Age: ";
            cin >> age;

            cout << "Enter Number of Matches Played: ";
            cin >> matchesPlayed;

            cout << "Enter Average Score: ";
            cin >> averageScore;

            players.AddPlayerToEnd(name, age, matchesPlayed, averageScore);

            ofstream newfile(name + ".txt");
            if (newfile) {
                newfile << "Name: " << name << endl;
                newfile << "Age: " << age << endl;
                newfile << "Matches Played: " << matchesPlayed << endl;
                newfile << "Average Score: " << averageScore << endl;
                newfile.close();
                cout << "Player added successfully. File created: " << name + ".txt" << endl;
            }
            else {
                cout << "Error creating file for player: " << name << endl;
            }

        }
        else if (choice == "2") {
            string name;
            cout << "Enter Player Name to Remove: ";
            getline(cin, name);
            players.RemovePlayer(name);
        }
        else if (choice == "3") {
            string name;
            cout << "Enter Player Name to Show Details: ";
            getline(cin, name);
            players.ShowPlayer(name);
        }
        else if (choice == "4") {
            players.ShowAllPlayers();
        }
        else if (choice == "0") {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
        system("pause");
        system("cls");
    }

    return 0;
}
