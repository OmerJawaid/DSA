#include <iostream>
#include <string>
using namespace std;


class Player {
public:
    string playerName;
    int gamesPlayed;
    int totalPoints;

    Player(string name, int games, int points)
        : playerName(name), gamesPlayed(games), totalPoints(points) {}
};

class Node {
public:
    Player player;
    Node* next;

    Node(Player p) : player(p), next(nullptr) {}
};

class PlayerQueue {
private:
    Node* front;
    Node* rear;
    int size;
    const int MaxPlayers = 30;

public:
    PlayerQueue() : front(nullptr), rear(nullptr), size(0) {}

    ~PlayerQueue() {
        while (front != nullptr) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }

    bool isFull() const {
        return size >= MaxPlayers;
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    void addPlayer(const Player& player) {
        if (isFull()) {
            cout << "Team is full. Cannot add more players.\n";
            return;
        }

        Node* newNode = new Node(player);
        if (rear == nullptr) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
        cout << "Player added: " << player.playerName << endl;
    }

    void removePlayer() {
        if (isEmpty()) {
            cout << "No players to remove.\n";
            return;
        }

        Node* temp = front;
        front = front->next;
        cout << "Player removed: " << temp->player.playerName << endl;
        delete temp;
        size--;
    }

    void displayPlayers() const {
        if (isEmpty()) {
            cout << "No players in the team.\n";
            return;
        }

        Node* current = front;
        cout << "Players in the team:\n";
        while (current != nullptr) {
            cout << "Name: " << current->player.playerName
                << ", Matches Played: " << current->player.gamesPlayed
                << ", Total Score: " << current->player.totalPoints << endl;
            current = current->next;
        }
    }

    void updatePlayerStats(const string& name, int games, int points) {
        Node* current = front;
        while (current != nullptr) {
            if (current->player.playerName == name) {
                current->player.gamesPlayed = games;
                current->player.totalPoints = points;
                cout << "Updated stats for " << name << endl;
                return;
            }
            current = current->next;
        }
        cout << "Player not found.\n";
    }

    void searchPlayer(const string& name) const {
        Node* current = front;
        while (current != nullptr) {
            if (current->player.playerName == name) {
                cout << "Player found:\n";
                cout << "Name: " << current->player.playerName
                    << ", Matches Played: " << current->player.gamesPlayed
                    << ", Total Score: " << current->player.totalPoints << endl;
                return;
            }
            current = current->next;
        }
        cout << "Player not found.\n";
    }
};

int getValidatedInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if ( value >= 0) {
            cin.ignore(1000, '\n');
            return value;
        }
        cout << "Invalid input! Please enter a positive number.\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

int main() {
    PlayerQueue cricketTeam;
    int choice;

    while (true) {
      
        cout << "CRICKET TEAM MANAGEMENT SYSTEM"<<endl
        << "1. Add Player"<<endl
         << "2. Remove Player"<<endl
         << "3. View All Players"<<endl
         << "4. Update Player Stats"<<endl
         << "5. Search Player"<<endl
         << "6. Exit"<<endl
        << "Enter your choice: ";
        cin >> choice;

        if (choice < 1 || choice > 6) {
            cout << "Invalid choice! Please select a valid option from the menu.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        string name;
        int games, points;

        if (choice == 1) {
            cout << "Enter player name: ";
            cin.ignore();
            getline(cin, name);
            games = getValidatedInput("Enter matches played: ");
            points = getValidatedInput("Enter total score: ");
            cricketTeam.addPlayer(Player(name, games, points));
        }
        else if (choice == 2) {
            cricketTeam.removePlayer();
        }
        else if (choice == 3) {
            cricketTeam.displayPlayers();
        }
        else if (choice == 4) {
            cout << "Enter player name to update: ";
            cin.ignore();
            getline(cin, name);
            games = getValidatedInput("Enter new matches played: ");
            points = getValidatedInput("Enter new total score: ");
            cricketTeam.updatePlayerStats(name, games, points);
        }
        else if (choice == 5) {
            cout << "Enter player name to search: ";
            cin.ignore();
            getline(cin, name);
            cricketTeam.searchPlayer(name);
        }
        else if (choice == 6) {
            cout << "Exiting program. Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice. Please select a valid option.\n";
        }
    }

    return 0;
}
