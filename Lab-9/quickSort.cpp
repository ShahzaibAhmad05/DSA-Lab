#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

// partition function for quicksort
int partitionArr(int arr[], int low, int high) {
    int pivot = arr[high];      // choose last element as pivot
    int i = low - 1;            // pointer for smaller elements

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // place pivot in its correct position
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// recursive quicksort
void quickSortRec(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionArr(arr, low, high);

        quickSortRec(arr, low, pi - 1);  // left side
        quickSortRec(arr, pi + 1, high); // right side
    }
}

// matching signature for sort functions
void quickSort(int arr[], int n) {
    quickSortRec(arr, 0, n - 1);
}

// fill array with random values 1–100
void fillRandom(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100 + 1;
    }
}

// print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

// time measurement function
long long measureTime(void (*func)(int[], int), int arr[], int n) {
    auto start = chrono::high_resolution_clock::now();
    func(arr, n);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    return duration.count();
}

int main() {
    srand(time(0));

    int n;
    cout << "Enter array size: ";
    cin >> n;

    int* arr = new int[n];
    fillRandom(arr, n);

    cout << "\nOriginal Array:\n";
    printArray(arr, n);

    long long tQuick = measureTime(quickSort, arr, n);

    cout << "\nSorted Array (Quick Sort):\n";
    printArray(arr, n);

    cout << "\nQuick Sort time: " << tQuick << " microseconds\n";

    delete[] arr;

    cout << "\nprogram finished.\n";
    return 0;
}
