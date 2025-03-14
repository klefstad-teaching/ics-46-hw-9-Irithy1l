#include "dijkstras.h"
#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distance(n, INF);
    previous.assign(n, -1);
    
    using Node = pair<int, int>; // (distance, vertex)
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    
    distance[source] = 0;
    pq.push({0, source});
    
    while (!pq.empty()) {
        int dist, u;
        tie(dist, u) = pq.top();
        pq.pop();
        
        if (dist > distance[u]) continue;
        
        for (const Edge& neighbor : G[u]) {
            int v = neighbor.dst, weight = neighbor.weight;
            
            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination){
    vector<int> path;
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total){
    if (v.empty()) {
        cout << "No path found" << endl;
        return;
    }
    cout << "Shortest path (cost " << total << "): ";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i];
        if (i < v.size() - 1) cout << " -> ";
    }
    cout << endl;
}
