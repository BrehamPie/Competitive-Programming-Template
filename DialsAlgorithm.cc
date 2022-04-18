#include<bits/stdc++.h>
using namespace std;
const int mx = 1e5 + 5;
vector<pair<int, int>>adj[mx];
const int K = 51;//max distance = K-1
int dist[mx];
bool vis[mx];
// Optimized Dijkstra. Complexity: O(V*K + E)
// Source: https://codeforces.com/blog/entry/88408
void Dials(int src) {
    queue<int>q[K];
    q[0].push(src);
    dist[src] = 0;
    int pos = 0, num = 1;
    while (num > 0) {
        while (q[pos % K].empty()) pos++;
        int u = q[pos % K].front();
        q[pos % K].pop();
        num--;
        if (vis[u])continue;
        vis[u] = 1;
        for (auto e : adj[u]) {
            int v = e.first, w = e.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                q[dist[v] % K].push(v);
                num++;
            }
        }
    }

}
int main() {

}