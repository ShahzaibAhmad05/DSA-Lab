#include <iostream>
#include <vector>
using namespace std;

class PatientQueue {
private:
    int* arr;        // Array to store patient IDs
    int capacity;    // Maximum number of patients in the waiting room
    int frontIdx;    // Index of current front
    int backIdx;     // Index of next insertion
    int size;       // Current number of patients
    int nextId;      // Next auto-generated ID

public:
    // Explicit forces calling contructor intentionally
    explicit PatientQueue(int cap)
        : capacity(cap), frontIdx(0), backIdx(0), size(0), nextId(1) {
        arr = new int[capacity];
    }

    // Free up allocated memory
    ~PatientQueue() {
        delete[] arr;
        arr = nullptr;
    }

    bool isEmpty() const { return size == 0; }
    bool isFull() const { return size == capacity; }

    void RegisterPatient() {
        if (isFull()) {
            cout << "Waiting room is full\n";
            return;
        }
        int id = nextId++;
        arr[backIdx] = id;
        backIdx = (backIdx + 1) % capacity;     // For array based circular queue
        size++;
        cout << "Registered patient with ID: " << id << '\n';
    }

    void ServePatient() {
        if (isEmpty()) {
            cout << "No patient to serve\n";
            return;
        }
        // Serve on the basis of First Come, First Served
        int id = arr[frontIdx];
        frontIdx = (frontIdx + 1) % capacity;
        size--;
        cout << "Serving patient with ID: " << id << '\n';
    }

    void CancelAll() {
        // Reset indices and size; IDs already assigned are ignored
        frontIdx = 0;
        backIdx = 0;
        size = 0;
        cout << "All appointments cancelled\n";
    }

    bool CanDoctorGoHome() const {
        return isEmpty();   // Return true if no patient is waiting
    }

    void ShowAllPatient() const {
        if (isEmpty()) {
            cout << "No patient is waiting\n";
            return;
        }

        // Collect current queue elements in arrival order
        vector<int> temp;
        temp.reserve(size);
        for (int i = 0; i < size; ++i) {
            int idx = (frontIdx + i) % capacity;
            temp.push_back(arr[idx]);
        }

        // Selection sort
        for (int i = 0; i < (int)temp.size() - 1; ++i) {
            int minPos = i;
            for (int j = i + 1; j < (int)temp.size(); ++j) {
                if (temp[j] < temp[minPos]) minPos = j;
            }
            if (minPos != i) {
                int t = temp[i];
                temp[i] = temp[minPos];
                temp[minPos] = t;
            }
        }

        // Print sorted IDs
        cout << "Patient IDs (sorted): ";
        for (int id : temp) cout << id << ' ';
        cout << '\n';
    }
};

int main() {
    // Choose capacity for waiting room
    int cap;
    cout << "Enter waiting room capacity: ";
    if (!(cin >> cap) || cap <= 0) {
        cout << "Invalid capacity\n";
        return 0;
    }

    PatientQueue pq(cap);

    while (true) {
        cout << "\n1) RegisterPatient  2) ServePatient  3) CancelAll\n";
        cout << "4) CanDoctorGoHome  5) ShowAllPatient  6) Exit\n";
        cout << "Choose: ";
        int choice;
        if (!(cin >> choice)) break;

        if (choice == 1) {
            pq.RegisterPatient();
        } else if (choice == 2) {
            pq.ServePatient();
        } else if (choice == 3) {
            pq.CancelAll();
        } else if (choice == 4) {
            cout << (pq.CanDoctorGoHome() ? "Yes\n" : "No\n");
        } else if (choice == 5) {
            pq.ShowAllPatient();
        } else if (choice == 6) {
            cout << "Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice\n";
        }
    }

    return 0;
}
