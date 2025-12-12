#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    const int V = 8;

    // adjacency list
    vector<vector<int>> adj(V + 1);

    // undirected edges from the given graph
    auto addEdge = [&](int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    addEdge(1, 2);
    addEdge(1, 5);
    addEdge(2, 6);
    addEdge(6, 7);
    addEdge(6, 3);
    addEdge(3, 7);
    addEdge(3, 4);
    addEdge(7, 4);
    addEdge(7, 8);
    addEdge(4, 8);

    int start = 2;
    vector<bool> visited(V + 1, false); 
    queue<int> q;       // Queue for traversal

    // start bfs from vertex 2
    visited[start] = true;
    q.push(start);

    cout << "bfs traversal order: ";

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        cout << u << " ";

        // visit all adjacent unvisited vertices
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    cout << "\n";
    return 0;
}
