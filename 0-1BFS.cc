#include<bits/stdc++.h>
using namespace std;
/*
    use BFS to solve the SSSP problem in O(E) if the weight of each edge is either 0 or 1.
*/
const int mx = 1e5 + 5;
int dist[mx];
bool vis[mx];
vector<pair<int, int>>adj[mx];
void bfs(int src) {
    memset(dist, 0x3f3f3f3f, sizeof dist);
    dist[src] = 0;
    deque<int> q;
    q.push_front(src);
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        if (vis[u])continue;
        vis[u] = 1;
        for (auto edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 1)
                    q.push_back(v);
                else
                    q.push_front(v);
            }
        }
    }
}
int main() {

}
