#include <iostream>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

// bubble sort
void bubbleSort(int arr[], int n) {
    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// selection sort
void selectionSort(int arr[], int n) {
    for (int i = n - 1; i >= 0; i--) {
        int maxIndex = i;
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[maxIndex]) {
                maxIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[maxIndex];
        arr[maxIndex] = temp;
    }
}

// insertion sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// helper functions for merge sort on subarray [first, last]
void mergeSortRec(int arr[], int first, int last);
// to merge two sorted halves
void mergeArrays(int arr[], int first, int mid, int last);
// match other function signatures
void mergeSort(int arr[], int n) {
    mergeSortRec(arr, 0, n - 1);
}

// recursive merge sort implementation
void mergeSortRec(int arr[], int first, int last) {
    if (first < last) {
        int mid = (first + last) / 2;
        mergeSortRec(arr, first, mid);
        mergeSortRec(arr, mid + 1, last);
        mergeArrays(arr, first, mid, last);
    }
}

// merge two sorted parts arr[first..mid] and arr[mid+1..last]
void mergeArrays(int arr[], int first, int mid, int last) {
    int n1 = mid - first + 1;
    int n2 = last - mid;

    // create temporary arrays
    int* left = new int[n1];
    int* right = new int[n2];

    // copy data to temporary arrays
    for (int i = 0; i < n1; i++) {
        left[i] = arr[first + i];
    }
    for (int j = 0; j < n2; j++) {
        right[j] = arr[mid + 1 + j];
    }

    // merge the temporary arrays back into arr[first..last]
    int i = 0;
    int j = 0;
    int k = first;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // copy remaining elements of left[], if any
    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    // copy remaining elements of right[], if any
    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }

    // free temporary memory
    delete[] left;
    delete[] right;
}

// function to fill array with random numbers from 1 to 100
void fillRandom(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100 + 1;
    }
}

// function to copy one array into another
void copyArray(int from[], int to[], int n) {
    for (int i = 0; i < n; i++) {
        to[i] = from[i];
    }
}

// function pointer type for sorting functions
typedef void (*SortFunc)(int[], int);

// to measure time of a sorting function in milliseconds
long long measureTime(SortFunc func, int arr[], int n) {
    auto start = chrono::high_resolution_clock::now();
    func(arr, n);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    return duration.count();
}

int main() {
    srand(time(0));   // seed random numbers

    cout << "-- average case timing on random arrays\n";

    int sizes[] = {100, 1000, 10000, 100000, 1000000};
    int sizeCount = 5;

    for (int s = 0; s < sizeCount; s++) {
        int n = sizes[s];
        int* baseArr = new int[n];
        int* temp = new int[n];

        fillRandom(baseArr, n);
        cout << "\narray size: " << n << "\n";

        copyArray(baseArr, temp, n);
        long long tBubble = measureTime(bubbleSort, temp, n);
        cout << "bubble sort time: " << tBubble << " ms\n";

        copyArray(baseArr, temp, n);
        long long tSelection = measureTime(selectionSort, temp, n);
        cout << "selection sort time: " << tSelection << " ms\n";

        copyArray(baseArr, temp, n);
        long long tInsertion = measureTime(insertionSort, temp, n);
        cout << "insertion sort time: " << tInsertion << " ms\n";

        copyArray(baseArr, temp, n);
        long long tMerge = measureTime(mergeSort, temp, n);
        cout << "merge sort time: " << tMerge << " ms\n";

        delete[] baseArr;
        delete[] temp;
    }

    cout << "\n\n-- best and worst case timing\n";

    int nCase = 10000;   // you can change this value if you want
    int* baseCase = new int[nCase];
    int* sortedArr = new int[nCase];
    int* reverseArr = new int[nCase];
    int* tempArr = new int[nCase];

    fillRandom(baseCase, nCase);

    // create best case (ascending) using stl sort
    copyArray(baseCase, sortedArr, nCase);
    sort(sortedArr, sortedArr + nCase);

    // create worst case (descending) using stl sort
    copyArray(baseCase, reverseArr, nCase);
    sort(reverseArr, reverseArr + nCase, greater<int>());

    cout << "\narray size used for best/worst case: " << nCase << "\n";

    // best case timings
    cout << "\n*** best case (sorted ascending) ***\n";

    copyArray(sortedArr, tempArr, nCase);
    long long bBest = measureTime(bubbleSort, tempArr, nCase);
    cout << "bubble sort time: " << bBest << " ms\n";

    copyArray(sortedArr, tempArr, nCase);
    long long sBest = measureTime(selectionSort, tempArr, nCase);
    cout << "selection sort time: " << sBest << " ms\n";

    copyArray(sortedArr, tempArr, nCase);
    long long iBest = measureTime(insertionSort, tempArr, nCase);
    cout << "insertion sort time: " << iBest << " ms\n";

    copyArray(sortedArr, tempArr, nCase);
    long long mBest = measureTime(mergeSort, tempArr, nCase);
    cout << "merge sort time: " << mBest << " ms\n";

    // worst case timings
    cout << "\n*** worst case (sorted descending) ***\n";

    copyArray(reverseArr, tempArr, nCase);
    long long bWorst = measureTime(bubbleSort, tempArr, nCase);
    cout << "bubble sort time: " << bWorst << " ms\n";

    copyArray(reverseArr, tempArr, nCase);
    long long sWorst = measureTime(selectionSort, tempArr, nCase);
    cout << "selection sort time: " << sWorst << " ms\n";

    copyArray(reverseArr, tempArr, nCase);
    long long iWorst = measureTime(insertionSort, tempArr, nCase);
    cout << "insertion sort time: " << iWorst << " ms\n";

    copyArray(reverseArr, tempArr, nCase);
    long long mWorst = measureTime(mergeSort, tempArr, nCase);
    cout << "merge sort time: " << mWorst << " ms\n";

    delete[] baseCase;
    delete[] sortedArr;
    delete[] reverseArr;
    delete[] tempArr;

    cout << "\nprogram finished.\n";
    return 0;
}
