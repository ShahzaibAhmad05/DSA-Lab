#include <iostream>
#include <list>
#include <iomanip>
using namespace std;

#define TABLE_SIZE 7  // initial table size

class HashTable {
private:
    list<int> *table;
    int size;
    int count;

    int hashFunction(int key) {
        return key % size;
    }

public:
    HashTable(int s = TABLE_SIZE) {
        size = s;
        table = new list<int>[size];
        count = 0;
    }

    void insert(int key) {
        int index = hashFunction(key);
        table[index].push_back(key);
        count++;
    }

    bool search(int key) {
        int index = hashFunction(key);
        for (int val : table[index])
            if (val == key)
                return true;
        return false;
    }

    double loadFactor() {
        return (double)count / size;
    }

    void rehash() {
        int oldSize = size;
        size *= 2;
        list<int>* newTable = new list<int>[size];

        for (int i = 0; i < oldSize; i++) {
            for (int key : table[i]) {
                int newIndex = key % size;
                newTable[newIndex].push_back(key);
            }
        }

        delete[] table;
        table = newTable;
    }

    void display() {
        for (int i = 0; i < size; i++) {
            cout << "[" << i << "] -> ";
            for (int val : table[i]) cout << val << " -> ";
            cout << "NULL\n";
        }
    }

    int getSize() { return size; }
    int getCount() { return count; }
};

int main() {
    HashTable ht;
    int keys[] = {15, 11, 27, 8, 12, 14, 33, 19};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int key : keys) ht.insert(key);

    cout << "Before Resizing (m=" << ht.getSize() << ", n=" << ht.getCount() << ")\n";
    cout << "Load Factor (λ) = " << fixed << setprecision(3) << ht.loadFactor() << "\n";
    ht.display();

    ht.rehash();

    cout << "\nAfter Resizing (m=" << ht.getSize() << ", n=" << ht.getCount() << ")\n";
    cout << "Load Factor (λ) = " << fixed << setprecision(3) << ht.loadFactor() << "\n";
    ht.display();

    return 0;
}
