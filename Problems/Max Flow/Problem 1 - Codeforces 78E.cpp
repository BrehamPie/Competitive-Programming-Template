/**
 * Problem Link: https://codeforces.com/contest/78/problem/E
 * Editorial : https://codeforces.com/blog/entry/1812
 **/
#include<bits/stdc++.h>
using namespace std;
int n, m;
char user[12][12];
char saver[12][12];
int timeToReach[11][11][11][11];
int timeToContaminate[11][11];
bool visitedByReactor[11][11];
const int fx[] = { +0,-0,+1,-1 };
const int fy[] = { +1,-1,+0,-0 };
using ll = long long;
#define eb emplace_back
struct Dinic {
    struct Edge {
        int u, v;
        ll cap, flow = 0;
        Edge() {}
        Edge(int u, int v, ll cap) :u(u), v(v), cap(cap) {}
    };
    int N;
    vector<Edge>edge;
    vector<vector<int>>adj;
    vector<int>d, pt;//pt[i] decreases overall complexity by removing unusable edges.
    Dinic(int N) :N(N), edge(0), adj(N), d(N), pt(N) {}
    void addEdge(int u, int v, ll cap) {
        if (u == v) return;
        edge.eb(u, v, cap);
        adj[u].eb(edge.size() - 1);
        edge.eb(v, u, 0);
        adj[v].eb(edge.size() - 1);
    }
    //Creating Layered Network
    bool bfs(int s, int t) {
        queue<int>q({ s });
        fill(d.begin(), d.end(), N + 1);
        d[s] = 0;
        while (!q.empty()) {
            int u = q.front();q.pop();
            if (u == t) break;
            for (int k : adj[u]) {
                Edge& e = edge[k];
                if (e.flow<e.cap && d[e.v]>d[e.u] + 1) {
                    d[e.v] = d[e.u] + 1;
                    q.emplace(e.v);
                }
            }
        }
        return d[t] != N + 1;
    }
    ll dfs(int u, int T, ll flow = -1) {
        if (u == T || flow == 0) return flow;
        for (int& i = pt[u];i < adj[u].size();i++) {
            Edge& e = edge[adj[u][i]];
            Edge& oe = edge[adj[u][i] ^ 1];
            if (d[e.v] == d[e.u] + 1) {
                ll amt = e.cap - e.flow;
                if (flow != -1 && amt > flow) amt = flow;
                if (ll pushed = dfs(e.v, T, amt)) {
                    e.flow += pushed;
                    oe.flow -= pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }
    ll maxFlow(int s, int t) {
        ll total = 0;
        while (bfs(s, t)) {
            fill(pt.begin(), pt.end(), 0);
            while (ll flow = dfs(s, t)) {
                total += flow;
            }
        }
        return total;
    }

};
int main() {
    cin >> n >> m;
    for (int i = 0;i < n;i++)
        for (int j = 0;j < n;j++)
            cin >> user[i][j];
    for (int i = 0;i < n;i++)
        for (int j = 0;j < n;j++)
            cin >> saver[i][j];
    //calculate time to contaminate using BFS
    memset(timeToContaminate, 0x3f3f3f3f, sizeof timeToContaminate);
    queue<pair<int, int>>q;
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++) {
            if (user[i][j] == 'Z') {
                q.push({ i,j });
                visitedByReactor[i][j] = 1;
                timeToContaminate[i][j] = 0;
            }
        }
    }
    while (q.size()) {
        auto u = q.front();
        q.pop();
        for (int i = 0;i < 4;i++) {
            int x = u.first + fx[i];
            int y = u.second + fy[i];
            if (x < n && y < n && x >= 0 && y >= 0 && !visitedByReactor[x][y] && user[x][y] != 'Y') {
                visitedByReactor[x][y] = 1;
                timeToContaminate[x][y] = timeToContaminate[u.first][u.second] + 1;
                q.push({ x,y });
            }
        }
    }
    // calculate minimum Time to Reach from x1,y1 to x2,y2
    memset(timeToReach, 0x3f3f3f3f, sizeof timeToReach);
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++) {
            if (user[i][j] >= '0' && user[i][j] <= '9') {
                int visitedByUser[n][n];
                memset(visitedByUser, 0, sizeof visitedByUser);
                queue<pair<int, int>>q;
                q.push({ i,j });
                timeToReach[i][j][i][j] = 0;
                visitedByUser[i][j] = 1;
                while (q.size()) {
                    auto u = q.front();
                    int sx = u.first;
                    int sy = u.second;
                    q.pop();
                    for (int k = 0;k < 4;k++) {
                        int x = u.first + fx[k];
                        int y = u.second + fy[k];
                        int lage = timeToReach[i][j][sx][sy] + 1;
                        if (x < n && y < n && x >= 0 && y >= 0 &&
                            !visitedByUser[x][y] && user[x][y] != 'Y'
                            && timeToContaminate[x][y] >= lage) {
                            visitedByUser[x][y] = 1;
                            timeToReach[i][j][x][y] = lage;
                            if (timeToContaminate[x][y] > lage)q.push({ x,y });
                        }
                    }
                }
            }
        }
    }

    // getting max-flow
    Dinic dic(2 + 2 * n * n);
    int src = 0;
    int des = 2 * n * n + 1;

    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++) {
            if (user[i][j] >= '0' && user[i][j] <= '9') {
                int ase = user[i][j] - '0';
                dic.addEdge(src, (i * n) + (j + 1), ase);
            }
        }
    }
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < n;j++) {
            if (saver[i][j] >= '0' && saver[i][j] <= '9') {
                int ase = saver[i][j] - '0';
                dic.addEdge((n * n) + (i * n) + (j + 1), des, ase);
            }
        }
    }

    for (int x1 = 0;x1 < n;x1++) {
        for (int y1 = 0;y1 < n;y1++) {
            for (int x2 = 0;x2 < n;x2++) {
                for (int y2 = 0;y2 < n;y2++) {
                    if (timeToReach[x1][y1][x2][y2] <= m) {
                        int X = (x1 * n) + (y1 + 1);
                        int Y = (n * n) + (x2 * n) + (y2 + 1);
                        dic.addEdge(X, Y, 100);
                    }
                }
            }
        }
    }
    cout << dic.maxFlow(src, des) << endl;



}