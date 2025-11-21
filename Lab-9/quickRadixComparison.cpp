#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

// ================== QUICK SORT ==================

int partitionArr(int arr[], int low, int high) {
    int pivot = arr[high];   // last element as pivot
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

void quickSortRec(int arr[], int low, int high) {
    if (low < high) {
        int pi = partitionArr(arr, low, high);

        quickSortRec(arr, low, pi - 1);
        quickSortRec(arr, pi + 1, high);
    }
}

void quickSort(int arr[], int n) {
    quickSortRec(arr, 0, n - 1);
}

// ================== RADIX SORT (LSD, base 10) ==================

int getMax(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > mx) {
            mx = arr[i];
        }
    }
    return mx;
}

// counting sort by a single digit (exp = 1, 10, 100, ...)
void countingSortDigit(int arr[], int n, int exp) {
    int* output = new int[n];
    int count[10] = {0};

    // count digit occurrences
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // prefix sums
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // build output (stable, traverse from end)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // copy back
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    delete[] output;
}

void radixSort(int arr[], int n) {
    int mx = getMax(arr, n);

    // sort by each digit
    for (int exp = 1; mx / exp > 0; exp *= 10) {
        countingSortDigit(arr, n, exp);
    }
}

// ================== HELPER FUNCTIONS ==================

void fillRandom(int arr[], int n) {
    // values 1–100 (same as Quick Sort experiment)
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100 + 1;
    }
}

void copyArray(int from[], int to[], int n) {
    for (int i = 0; i < n; i++) {
        to[i] = from[i];
    }
}

typedef void (*SortFunc)(int[], int);

// measure time in milliseconds
long long measureTime(SortFunc func, int arr[], int n) {
    auto start = chrono::high_resolution_clock::now();
    func(arr, n);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    return duration.count();
}

int main() {
    srand(time(0));

    cout << "-- average case timing on random arrays (values 1-100)\n";
    cout << "-- Quick Sort vs Radix Sort (LSD)\n";

    int sizes[] = {100, 1000, 10000};
    int sizeCount = 3;

    for (int s = 0; s < sizeCount; s++) {
        int n = sizes[s];
        int* baseArr = new int[n];
        int* temp = new int[n];

        fillRandom(baseArr, n);

        cout << "\narray size: " << n << "\n";

        // Quick Sort timing
        copyArray(baseArr, temp, n);
        long long tQuick = measureTime(quickSort, temp, n);
        cout << "quick sort time:  " << tQuick << " microsec\n";

        // Radix Sort timing
        copyArray(baseArr, temp, n);
        long long tRadix = measureTime(radixSort, temp, n);
        cout << "radix sort time:  " << tRadix << " microsec\n";

        delete[] baseArr;
        delete[] temp;
    }

    cout << "\nprogram finished.\n";
    return 0;
}
