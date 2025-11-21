#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

// ================== QUICK SORT (BAD PIVOT = FIRST) ==================
// Worst case when array is descending.

int partitionFirst(int arr[], int low, int high) {
    int pivot = arr[low];   // BAD pivot choice → worst case on descending
    int i = low + 1;
    int j = high;

    while (true) {
        while (i <= high && arr[i] <= pivot) i++;
        while (j >= low && arr[j] > pivot) j--;

        if (i >= j) break;

        swap(arr[i], arr[j]);
    }

    swap(arr[low], arr[j]);
    return j;
}

void quickSortWorstRec(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionFirst(arr, low, high);
        quickSortWorstRec(arr, low, pi - 1);
        quickSortWorstRec(arr, pi + 1, high);
    }
}

void quickSortWorst(int arr[], int n) {
    quickSortWorstRec(arr, 0, n - 1);
}

// ================== QUICK SORT (GOOD PIVOT = MIDDLE) ==================
// Best case when array is already sorted ascending.

int partitionMiddle(int arr[], int low, int high) {
    int mid = (low + high) / 2;
    int pivot = arr[mid];

    int i = low;
    int j = high;

    while (i <= j) {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;

        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    return i;
}

void quickSortBestRec(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionMiddle(arr, low, high);
        quickSortBestRec(arr, low, pi - 1);
        quickSortBestRec(arr, pi, high);
    }
}

void quickSortBest(int arr[], int n) {
    quickSortBestRec(arr, 0, n - 1);
}

// ================== HELPER FUNCTIONS ==================

void fillAscending(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = i + 1;
}

void fillDescending(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] = n - i;
}

void copyArray(int from[], int to[], int n) {
    for (int i = 0; i < n; i++) to[i] = from[i];
}

long long measureTime(void (*func)(int[], int), int arr[], int n) {
    auto start = chrono::high_resolution_clock::now();
    func(arr, n);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    return duration.count();
}

int main() {
    int sizes[] = {100, 1000, 10000};
    int sizeCount = 3;

    cout << "-- Quick Sort Best & Worst Case Analysis --\n";

    for (int s = 0; s < sizeCount; s++) {
        int n = sizes[s];
        int* asc = new int[n];
        int* desc = new int[n];
        int* temp = new int[n];

        fillAscending(asc, n);
        fillDescending(desc, n);

        cout << "\nArray size: " << n << "\n";

        // Best Case (ascending + good pivot)
        copyArray(asc, temp, n);
        long long tBest = measureTime(quickSortBest, temp, n);
        cout << "Best case (ascending, middle pivot): " << tBest << " ms\n";

        // Worst Case (descending + first pivot)
        copyArray(desc, temp, n);
        long long tWorst = measureTime(quickSortWorst, temp, n);
        cout << "Worst case (descending, first pivot): " << tWorst << " ms\n";

        delete[] asc;
        delete[] desc;
        delete[] temp;
    }

    cout << "\nprogram finished.\n";
    return 0;
}
