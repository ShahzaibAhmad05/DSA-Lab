#include <iostream>
#include <algorithm>
#include <chrono>
using namespace std;

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

// counting sort by digit (exp = 1, 10, 100, ...)
void countingSortDigit(int arr[], int n, int exp) {
    int* output = new int[n];
    int count[10] = {0};

    // count occurrences of each digit
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // prefix sums
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // build output (stable)
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

void fillAscending(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;   // 1, 2, 3, ...
    }
}

void fillDescending(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;   // n, n-1, ..., 1
    }
}

void copyArray(int from[], int to[], int n) {
    for (int i = 0; i < n; i++) {
        to[i] = from[i];
    }
}

long long measureTime(void (*func)(int[], int), int arr[], int n) {
    auto start = chrono::high_resolution_clock::now();
    func(arr, n);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}

// ================== MAIN: BEST & WORST CASE FOR RADIX SORT ==================

int main() {
    int sizes[] = {100, 1000, 10000};
    int sizeCount = 3;

    cout << "-- Radix Sort Best & Worst Case Analysis --\n";

    for (int s = 0; s < sizeCount; s++) {
        int n = sizes[s];

        int* asc = new int[n];
        int* desc = new int[n];
        int* temp = new int[n];

        fillAscending(asc, n);
        fillDescending(desc, n);

        cout << "\nArray size: " << n << "\n";

        // "Best case" (ascending)
        copyArray(asc, temp, n);
        long long tBest = measureTime(radixSort, temp, n);
        cout << "Best case (ascending):   " << tBest << " ms\n";

        // "Worst case" (descending)
        copyArray(desc, temp, n);
        long long tWorst = measureTime(radixSort, temp, n);
        cout << "Worst case (descending): " << tWorst << " ms\n";

        delete[] asc;
        delete[] desc;
        delete[] temp;
    }

    cout << "\nprogram finished.\n";
    return 0;
}
