#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    int N, E;
    cout << "enter number of nodes (n): ";
    cin >> N;

    cout << "enter number of edges (e): ";
    cin >> E;

    // adjacency list (1 to N) depending on user input
    vector<vector<int>> adj(N + 1);

    cout << "enter " << E << " edges (u v) for an undirected graph:\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;

        // store both directions (since it is undirected)
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int start;
    cout << "enter starting node for bfs: ";
    cin >> start;

    vector<bool> visited(N + 1, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "bfs traversal order: ";

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        cout << u << " ";

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
