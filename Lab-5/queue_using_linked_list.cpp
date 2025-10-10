#include <iostream>
using namespace std;

// Node for linked list
struct Node {
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class LinkedList {
protected:      // protected makes them accessible to child classes
    Node* head;
    Node* tail;

public:
    LinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    void append(int value) {
        Node* newNode = new Node(value);

        // If list is empty, new node becomes both head and tail
        if (!head) {
            head = tail = newNode;
        } 
        else {
            // Attach new node at the end
            tail->next = newNode;
            tail = newNode;     // Point the tail pointer
        }
    }

    // Remove a node from the front
    int popFront() {
        if (!head) {
            cout << "Queue is empty\n";
            return -1;
        }

        // Save value and move head forward
        int value = head->data;
        Node* temp = head;
        head = head->next;

        if (!head)      // If head is null
            tail = nullptr;     // Reset tail to null
        delete temp;
        return value;
    }

    // Check if list is empty
    bool isEmpty() const {
        return head == nullptr;
    }

    // Get the value at the front
    int frontValue() const {
        if (!head) {
            cout << "Queue is empty\n";
            return -1;
        }
        return head->data;
    }
};

// Implement queue from linked list class
class Queue : public LinkedList {
public:
    void enqueue(int value) {
        append(value);
    }

    int dequeue() {
        return popFront();
    }

    int peek() const {
        return frontValue();
    }

    // This function is not included in std::queue
    void display() const {
        if (!head) {
            cout << "Queue is empty\n";
            return;
        }

        Node* current = head;
        cout << "Queue elements: \n";
        while (current) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }
};

// Test Driver
int main() {
    Queue q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    cout << "Front element: " << q.peek() << endl;  // 10
    cout << "Removing the front element: " << q.dequeue() << endl;     // 10
    cout << "Front element: " << q.peek() << endl << endl;  // 20

    cout << "Displaying the full list:\n";
    q.display();
    cout << endl;

    q.dequeue();
    q.dequeue();
    cout << "Trying to dequeue from an empty list..." << endl;
    q.dequeue();        // Check for error handling

    return 0;
}
