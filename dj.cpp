#include <bits/stdc++.h>
using namespace std;

vector<int> dijkstra(int V, vector<vector<int>> adj[], int S) {
    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;

    vector<int> dist(V, 1e9);
    dist[S] = 0;

    pq.push({0, S});

    while (!pq.empty()) {
        int dis = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        for (auto it : adj[node]) {
            int nxt = it[0];
            int w = it[1];

            if (dis + w < dist[nxt]) {
                dist[nxt] = dis + w;
                pq.push({dist[nxt], nxt});
            }
        }
    }
    return dist;
}

int main() {
    int V, E;
    cin >> V >> E;

    vector<vector<int>> adj[V];

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int S;
    cin >> S;

    vector<int> out = dijkstra(V, adj, S);

    for (int x : out) {
        if (x == 1e9) cout << "INF ";
        else cout << x << " ";
    }
}
