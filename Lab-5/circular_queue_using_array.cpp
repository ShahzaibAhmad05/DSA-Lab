#include <iostream>
using namespace std;

class CircularQueue {
private:
    int* arr;       // Pointer to array
    int front;      // Index of front element
    int back;       // Index of last element
    int size;       // Storing maximum capacity of queue

public:
    CircularQueue(int capacity) {
        size = capacity;
        arr = new int[size];
        front = -1;
        back = -1;
    }

    // Release allocated memory at destructor
    ~CircularQueue() {
        delete[] arr;
    }

    void enqueue(int value) {   // Add to front
        // Check if queue is full
        if ((front == 0 && back == size - 1) || (back + 1 == front)) {
            cout << "Queue is full\n";
            return;
        }

        // For first time insertion
        if (front == -1) {
            front = 0;
            back = 0;
        }
        else {
            back = (back + 1) % size;   // Take % for circular nature
        }

        arr[back] = value;
        cout << "Enqueued: " << value << endl;
    }

    void dequeue() {        // Remove from front
        // Check for empty condition
        if (front == -1) {
            cout << "Queue is empty\n";
            return;
        }

        cout << "Dequeued: " << arr[front] << endl;

        // If only one element was present
        if (front == back) {
            front = back = -1;
        } 
        else {
            front = (front + 1) % size;     // Take % for circular nature
        }
    }

    void display() const {
        if (front == -1) {      // Empty queue handling
            cout << "Queue is empty\n";
            return;
        }
        cout << "Queue elements:\n";

        int i = front;
        while (true) {
            cout << arr[i] << " -> ";
            if (i == back)
                break;
            i = (i + 1) % size;
        }
        cout << "END\n";
    }
};

// Test driver
int main() {
    CircularQueue q(5);

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);
    q.enqueue(50);

    cout << "\nDisplaying queue:\n";
    q.display();

    cout << "\nPerforming two dequeues:\n";
    q.dequeue();
    q.dequeue();

    cout << "\nDisplaying after dequeues:\n";
    q.display();

    cout << "\nAdding new elements (wrap around):\n";
    q.enqueue(60);
    q.enqueue(70);
    q.display();

    cout << "\nTrying to enqueue into a full queue:\n";
    q.enqueue(80);

    cout << "\nPerforming all dequeues:\n";
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();

    cout << "\nChecking for error handling for the empty case:\n";
    q.dequeue();
    return 0;
}
