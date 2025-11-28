#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class BinaryHeap {
private:
    vector<int> heap;   // underlying array storing heap elements

    // maintain heap property upwards after insertion
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;

            if (heap[index] < heap[parent]) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    // maintain heap property downwards after removal
    void heapifyDown(int index) {
        int n = heap.size();

        while (true) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int smallest = index;

            if (left < n && heap[left] < heap[smallest])
                smallest = left;

            if (right < n && heap[right] < heap[smallest])
                smallest = right;

            if (smallest != index) {
                swap(heap[index], heap[smallest]);
                index = smallest;
            } else {
                break;
            }
        }
    }

public:

    // returns the minimum value without removing it
    int top() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        return heap[0];
    }

    // removes the minimum value and maintains heap property
    void pop() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    // inserts a new value x into the heap
    void push(int x) {
        heap.push_back(x);
        heapifyUp(heap.size() - 1);
    }

    // returns true if heap is empty
    bool isEmpty() {
        return heap.empty();
    }

    // returns number of elements
    int size() {
        return heap.size();
    }

    // returns height of heap: floor(log2(n))
    int height() {
        if (heap.empty()) return -1;
        return floor(log2(heap.size()));
    }

    // builds a heap from an unsorted array using heapifyDown
    void buildHeap(const vector<int>& arr) {
        heap = arr;

        // heapify from last non-leaf node down to root
        for (int i = heap.size() / 2 - 1; i >= 0; i--) {
            heapifyDown(i);
        }
    }

    // prints the heap in array form
    void print() {
        for (int x : heap)
            cout << x << " ";
        cout << endl;
    }
};

// Example usage
int main() {
    BinaryHeap bh;

    bh.push(10);
    bh.push(4);
    bh.push(15);
    bh.push(20);
    bh.push(0);

    cout << "Heap elements: ";
    bh.print();

    cout << "Min element: " << bh.top() << endl;

    bh.pop();
    cout << "After removing min: ";
    bh.print();

    vector<int> arr = {5, 2, 8, 3, 1};
    bh.buildHeap(arr);

    cout << "Built heap: ";
    bh.print();

    cout << "Height: " << bh.height() << endl;

    return 0;
}
