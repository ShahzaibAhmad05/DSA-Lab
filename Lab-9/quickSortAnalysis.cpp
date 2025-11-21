#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

// partition function for quick sort
int partitionArr(int arr[], int low, int high) {
    int pivot = arr[high];   // last element as pivot
    int i = low - 1;         // index of smaller element

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // place pivot in correct position
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// recursive quick sort
void quickSortRec(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionArr(arr, low, high);

        quickSortRec(arr, low, pi - 1);   // left part
        quickSortRec(arr, pi + 1, high);  // right part
    }
}

// wrapper to match signature
void quickSort(int arr[], int n) {
    quickSortRec(arr, 0, n - 1);
}

// fill array with random integers from 1 to 100
void fillRandom(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100 + 1;   // 1 to 100
    }
}

// copy one array into another
void copyArray(int from[], int to[], int n) {
    for (int i = 0; i < n; i++) {
        to[i] = from[i];
    }
}

// function pointer type for sorting functions
typedef void (*SortFunc)(int[], int);

// measure sorting time in milliseconds
long long measureTime(SortFunc func, int arr[], int n) {
    auto start = chrono::high_resolution_clock::now();
    func(arr, n);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}

int main() {
    srand(time(0));   // seed random

    cout << "-- average case timing for Quick Sort on random arrays (values 1-100)\n";

    int sizes[] = {100, 1000, 10000};
    int sizeCount = 3;

    for (int s = 0; s < sizeCount; s++) {
        int n = sizes[s];
        int* baseArr = new int[n];
        int* temp = new int[n];

        // generate base random array
        fillRandom(baseArr, n);
        copyArray(baseArr, temp, n);

        cout << "\narray size: " << n << "\n";

        long long tQuick = measureTime(quickSort, temp, n);
        cout << "quick sort time: " << tQuick << " ms\n";

        delete[] baseArr;
        delete[] temp;
    }

    cout << "\nprogram finished.\n";
    return 0;
}
