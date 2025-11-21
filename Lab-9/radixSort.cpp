#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

// function to fill array with random integers from 0 to 9999
void fillRandom(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000;   // 0 to 9999
    }
}

// function to print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

// get maximum element in array (for number of digits)
int getMax(int arr[], int n) {
    int mx = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > mx) {
            mx = arr[i];
        }
    }
    return mx;
}

// counting sort for a specific digit (exp = 1, 10, 100, ...)
void countingSortDigit(int arr[], int n, int exp) {
    int* output = new int[n];  // output array
    int count[10] = {0};       // count array for digits 0-9

    // count occurrences of each digit
    for (int i = 0; i < n; i++) {
        int digit = (arr[i] / exp) % 10;
        count[digit]++;
    }

    // convert count to prefix sum (positions)
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // build output array (traverse from end for stability)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // copy back to original array
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    delete[] output;
}

// LSD Radix Sort using counting sort on each digit
void radixSort(int arr[], int n) {
    int mx = getMax(arr, n);

    // do counting sort for every digit
    // exp = 1 (ones), 10 (tens), 100 (hundreds), ...
    for (int exp = 1; mx / exp > 0; exp *= 10) {
        countingSortDigit(arr, n, exp);
    }
}

int main() {
    srand(time(0));   // seed random

    int n;
    cout << "Enter array size: ";
    cin >> n;

    int* arr = new int[n];

    fillRandom(arr, n);

    cout << "\nOriginal array:\n";
    printArray(arr, n);

    radixSort(arr, n);

    cout << "\nSorted array using LSD Radix Sort:\n";
    printArray(arr, n);

    delete[] arr;

    cout << "\nprogram finished.\n";
    return 0;
}
