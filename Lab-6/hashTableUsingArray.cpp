#include <iostream>
using namespace std;

#define TABLE_SIZE 10

class HashTable {
private:
    int table[TABLE_SIZE];

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++)
            table[i] = -1;  // -1 denotes empty slot
    }

    int hashFunction(int key) {
        return key % TABLE_SIZE;
    }

    void insert(int key) {
        int index = hashFunction(key);
        int startIndex = index;

        // Linear probing
        while (table[index] != -1) {
            index = (index + 1) % TABLE_SIZE;
            if (index == startIndex) {
                cout << "Hash table is full. Cannot insert " << key << endl;
                return;
            }
        }
        table[index] = key;
    }

    int search(int key) {   // Returns index if found, else -1
        int index = hashFunction(key);
        int startIndex = index;

        while (table[index] != -1) {
            if (table[index] == key)
                return index;
            index = (index + 1) % TABLE_SIZE;
            if (index == startIndex)
                break;
        }
        return -1;
    }

    void display() {
        cout << "\nHash Table:\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "[" << i << "] -> ";
            if (table[i] != -1)
                cout << table[i];
            else
                cout << "NULL";
            cout << endl;
        }
    }
};

int main() {
    HashTable ht;

    int keys[] = {23, 43, 13, 27, 33, 37};
    int n = sizeof(keys) / sizeof(keys[0]);

    // Insert keys
    for (int i = 0; i < n; i++)
        ht.insert(keys[i]);

    // Display hash table
    ht.display();

    // Search for keys
    int searchKeys[] = {27, 99};
    for (int i = 0; i < 2; i++) {
        int result = ht.search(searchKeys[i]);
        if (result != -1)
            cout << "\nKey " << searchKeys[i] << " found at index " << result << endl;
        else
            cout << "\nKey " << searchKeys[i] << " not found!" << endl;
    }

    cout << endl;
    return 0;
}
