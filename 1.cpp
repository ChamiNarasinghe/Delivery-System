#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

const double INVALID_DISTANCE = -1.0;

class Parcel {
public:
    int parcelNumber;
    string sender;
    string receiver;
    double weight;
    int priority;
    string destination;
};

class ParcelQueue {
private:
    queue<Parcel> parcelQueue;
    int parcelCounter;

public:
    ParcelQueue() : parcelCounter(0) {}

    void addParcel(const vector<string>& cities);
    void deleteParcel();
    void viewParcel() const;
    void viewSortedParcels() const;
    void sortParcels();
    void deliverParcel();
    void shortestPath(const vector<string>& cities, const vector<vector<double>>& distances);
};

void ParcelQueue::addParcel(const vector<string>& cities) {
    Parcel newParcel;

    cout << "Enter sender: ";
    cin >> newParcel.sender;

    cout << "Enter receiver: ";
    cin >> newParcel.receiver;


    cout << "Enter weight (in grams): ";
    while (!(cin >> newParcel.weight) || newParcel.weight < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid non-negative weight: ";
    }


    cout << "Enter priority (1 for speed post, 2 for normal post): ";
    while (!(cin >> newParcel.priority) || (newParcel.priority != 1 && newParcel.priority != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter 1 for speed post or 2 for normal post: ";
    }


    cout << "Enter destination city (";
    for (size_t i = 0; i < cities.size(); ++i) {
        cout << cities[i];
        if (i < cities.size() - 1) {
            cout << ", ";
        }
    }
    cout << "): ";

    while (true) {
        cin >> newParcel.destination;
        if (find(cities.begin(), cities.end(), newParcel.destination) != cities.end()) {
            break;
        } else {
            cout << "Invalid city. Please enter a valid destination city: ";
        }
    }

    newParcel.parcelNumber = ++parcelCounter;

    parcelQueue.push(newParcel);

    cout << "Parcel added successfully. Parcel number: " << newParcel.parcelNumber << endl;
}

void ParcelQueue::deleteParcel() {
    if (parcelQueue.empty()) {
        cout << "Queue is empty. No parcels to delete." << endl;
        return;
    }

    int parcelNumber;
    cout << "Enter parcel number to delete: ";
    while (!(cin >> parcelNumber)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid parcel number: ";
    }

    queue<Parcel> tempQueue;

    while (!parcelQueue.empty()) {
        if (parcelQueue.front().parcelNumber != parcelNumber) {
            tempQueue.push(parcelQueue.front());
        } else {
            cout << "Parcel deleted successfully. Parcel number: " << parcelNumber << endl;
        }
        parcelQueue.pop();
    }

    parcelQueue = tempQueue;
}

void ParcelQueue::viewParcel() const {
    if (parcelQueue.empty()) {
        cout << "Queue is empty. No parcels to view." << endl;
        return;
    }

    const Parcel& firstParcel = parcelQueue.front();

    cout << "First Parcel in the Original Queue:" << endl;
    cout << "Parcel Number: " << firstParcel.parcelNumber << endl;
    cout << "Sender: " << firstParcel.sender << endl;
    cout << "Receiver: " << firstParcel.receiver << endl;
    cout << "Weight: " << firstParcel.weight << " grams" << endl;
    cout << "Priority: " << (firstParcel.priority == 1 ? "Speed Post" : "Normal Post") << endl;
    cout << "Destination City: " << firstParcel.destination << endl;
}

void ParcelQueue::viewSortedParcels() const {
    if (parcelQueue.empty()) {
        cout << "Queue is empty. No parcels to view." << endl;
        return;
    }

    queue<Parcel> tempQueue = parcelQueue;

    cout << "Sorted Parcels:" << endl;

    while (!tempQueue.empty()) {
        const Parcel& currentParcel = tempQueue.front();

        cout << "Parcel Number: " << currentParcel.parcelNumber << endl;
        cout << "Sender: " << currentParcel.sender << endl;
        cout << "Receiver: " << currentParcel.receiver << endl;
        cout << "Weight: " << currentParcel.weight << " grams" << endl;
        cout << "Priority: " << (currentParcel.priority == 1 ? "Speed Post" : "Normal Post") << endl;
        cout << "Destination City: " << currentParcel.destination << endl;

        tempQueue.pop();
    }
}

void ParcelQueue::sortParcels() {
    if (parcelQueue.empty()) {
        cout << "Queue is empty. No parcels to sort." << endl;
        return;
    }

    vector<Parcel> parcels;
    while (!parcelQueue.empty()) {
        parcels.push_back(parcelQueue.front());
        parcelQueue.pop();
    }

    int n = parcels.size();

    for (int i = 1; i < n; ++i) {
        Parcel key = parcels[i];
        int j = i - 1;

        while (j >= 0 && (key.priority < parcels[j].priority || (key.priority == parcels[j].priority && key.parcelNumber < parcels[j].parcelNumber))) {
            parcels[j + 1] = parcels[j];
            --j;
        }

        parcels[j + 1] = key;
    }

    for (const auto& parcel : parcels) {
        parcelQueue.push(parcel);
    }

    cout << "Parcels sorted successfully using Insertion Sort." << endl;
}



void ParcelQueue::deliverParcel() {
    if (parcelQueue.empty()) {
        cout << "Queue is empty. No parcels to deliver." << endl;
        return;
    }

    const Parcel deliveredParcel = parcelQueue.front();
    cout << "Delivering Parcel Number " << deliveredParcel.parcelNumber << " to " << deliveredParcel.destination << endl;

    parcelQueue.pop();
}

void ParcelQueue::shortestPath(const vector<string>& cities, const vector<vector<double>>& distances) {
    if (parcelQueue.empty()) {
        cout << "Queue is empty. No parcels to determine the shortest path." << endl;
        return;
    }

    string sourceCity;
    int sourceIndex;


    cout << "Enter source city (";
    for (size_t i = 0; i < cities.size(); ++i) {
        cout << cities[i];
        if (i < cities.size() - 1) {
            cout << ", ";
        }
    }
    cout << "): ";

    while (true) {
        cin >> sourceCity;

        auto it = find(cities.begin(), cities.end(), sourceCity);
        if (it != cities.end()) {
            sourceIndex = it - cities.begin();
            break;
        } else {
            cout << "Invalid city. Please enter a valid source city: ";
        }
    }

    int n = cities.size();

    vector<double> dist(n, INT_MAX);
    vector<bool> visited(n, false);

    dist[sourceIndex] = 0;

    for (int count = 0; count < n - 1; ++count) {
        int u = -1;
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u]))
                u = i;
        }

        visited[u] = true;

        for (int v = 0; v < n; ++v) {
            if (!visited[v] && distances[u][v] != INVALID_DISTANCE && dist[u] != INT_MAX &&
                dist[u] + distances[u][v] < dist[v]) {
                dist[v] = dist[u] + distances[u][v];
            }
        }
    }


    cout << "Shortest paths from " << sourceCity << " to other cities:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << cities[i] << ": " << dist[i] << " KM" << endl;
    }
}

int main() {
    ParcelQueue parcelQueue;

    vector<string> cities = {"Matara", "Mirissa", "Galle", "Hikkaduwa", "Bentota", "Colombo"};
    vector<vector<double>> distances = {
        {0, 11, INVALID_DISTANCE, INVALID_DISTANCE, INVALID_DISTANCE, 158},
        {11, 0, 33, INVALID_DISTANCE, INVALID_DISTANCE, 153},
        {INVALID_DISTANCE, 33, 0, 18.9, INVALID_DISTANCE, 129},
        {INVALID_DISTANCE, INVALID_DISTANCE, 18.9, 0, 36.9, 120},
        {INVALID_DISTANCE, INVALID_DISTANCE, INVALID_DISTANCE, 36.9, 0, 84},
        {158, 153, 129, 120, 84, 0}
    };

    enum MenuChoice { ADD_PARCEL = 1, DELETE_PARCEL, VIEW_PARCEL, SORT_PARCELS, VIEW_SORTED_PARCELS, DELIVER_PARCEL, SHORTEST_PATH, EXIT };

    int choice;
    bool exitProgram = false;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Parcel\n";
        cout << "2. Delete Parcel\n";
        cout << "3. View Parcel\n";
        cout << "4. Sort Parcels\n";
        cout << "5. View Sorted Parcels\n";
        cout << "6. Deliver Parcel\n";
        cout << "7. Shortest Path\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice) || (choice < 0 || choice > 7)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid choice: ";
        }

        switch (choice) {
            case ADD_PARCEL:
                parcelQueue.addParcel(cities);
                break;
            case DELETE_PARCEL:
                parcelQueue.deleteParcel();
                break;
            case VIEW_PARCEL:
                parcelQueue.viewParcel();
                break;
            case SORT_PARCELS:
                parcelQueue.sortParcels();
                break;
            case VIEW_SORTED_PARCELS:
                parcelQueue.viewSortedParcels();
                break;
            case DELIVER_PARCEL:
                parcelQueue.deliverParcel();
                break;
            case SHORTEST_PATH:
                parcelQueue.shortestPath(cities, distances);
                break;
            case EXIT:
                cout << "Exiting program. Goodbye!" << endl;
                exitProgram = true;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (!exitProgram);

    return 0;
}
