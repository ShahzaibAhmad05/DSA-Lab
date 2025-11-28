#include <bits/stdc++.h>
using namespace std;

// struct to store value and its position in the matrix
struct Item {
    int value;
    int row;
    int col;
};

// comparator to make a min-heap based on value
struct Compare {
    bool operator()(const Item& a, const Item& b) const {
        return a.value > b.value; // min-heap
    }
};

// function to find the kth smallest element in a sorted matrix
int kthSmallest(vector<vector<int>>& matrix, int k) {
    int n = matrix.size();
    if (n == 0) return -1;

    // min-heap of Items
    priority_queue<Item, vector<Item>, Compare> pq;

    // push the first element of each row into the heap
    for (int r = 0; r < n; ++r) {
        pq.push({matrix[r][0], r, 0});
    }

    // pop k-1 times to reach the kth smallest
    while (k > 1 && !pq.empty()) {
        Item cur = pq.top();
        pq.pop();

        // push the next element in the same row, if it exists
        if (cur.col + 1 < n) {
            pq.push({matrix[cur.row][cur.col + 1], cur.row, cur.col + 1});
        }

        --k;
    }

    // top of the heap is now the kth smallest element
    return pq.top().value;
}

int main() {
    // example usage
    vector<vector<int>> matrix = {
        {1,  5,  9},
        {10, 11, 13},
        {12, 13, 15}
    };
    int k = 8;

    cout << "kth smallest element is: " << kthSmallest(matrix, k) << endl;
    return 0;
}
