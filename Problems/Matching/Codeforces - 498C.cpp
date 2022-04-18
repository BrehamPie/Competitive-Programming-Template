#include<bits/stdc++.h>
using namespace std;
// Problem Link: https://codeforces.com/contest/499/problem/E
//idea: https://codeforces.com/blog/entry/15353
struct HK {
    static const int inf = 1e9;
    int n;
    vector<int>matchL, matchR, dist;
    //matchL contains value of matched node for L part.
    vector<vector<int>>adj;
    HK(int n) :n(n), matchL(n + 1), matchR(n + 1), dist(n + 1), adj(n + 1) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    bool bfs() {
        queue<int>q;
        for (int u = 1;u <= n;u++) {
            if (!matchL[u]) {
                dist[u] = 0;
                q.push(u);
            }
            else dist[u] = inf;
        }
        dist[0] = inf;///unmatched node matches with 0.
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto v : adj[u]) {
                if (dist[matchR[v]] == inf) {
                    dist[matchR[v]] = dist[u] + 1;
                    q.push(matchR[v]);
                }
            }
        }
        return dist[0] != inf;
    }

    bool dfs(int u) {
        if (!u) return true;
        for (auto v : adj[u]) {
            if (dist[matchR[v]] == dist[u] + 1 && dfs(matchR[v])) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        dist[u] = inf;
        return false;
    }

    int max_match() {
        int matching = 0;
        while (bfs()) {
            for (int u = 1;u <= n;u++) {
                if (!matchL[u])
                    if (dfs(u))
                        matching++;
            }
        }
        return matching;
    }
};

bool vis[100005];

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int>a(n);
    for (int i = 0;i < n;i++) {
        scanf("%d", &a[i]);
    }
    vector<int>primes = { 2 };
    for (int i = 3;i * i <= 100000;i += 2) {
        if (vis[i])continue;
        for (int j = i * i;j <= 100000;j += 2 * i) {
            vis[j] = 1;
        }
    }
    for (int i = 3;i <= 100000;i += 2)if (!vis[i])primes.push_back(i);
    struct node {
        int id, val, who;
    };
    vector<node>facts;
    vector<int>ID[n];
    int cur = 0;
    for (int i = 0;i < n;i++) {
        int x = a[i];
        for (auto y : primes) {
            while (x % y == 0) {
                x /= y;
                facts.push_back({ cur,y,i });
                ID[i].push_back(cur);
                cur++;
            }
        }
        if (x > 1) {
            facts.push_back({ cur,x,i });
            ID[i].push_back(cur);
            cur++;
        }
    }
    HK hk(cur + 1);
    while (m--) {
        int i, j;
        scanf("%d%d", &i, &j);
        i--, j--;
        if (i % 2)swap(i, j);
        for (auto x : ID[i]) {
            for (auto y : ID[j]) {
                if (facts[x].val == facts[y].val) {
                    hk.addEdge(x + 1, y + 1);
                }
            }
        }
    }
    printf("%d", hk.max_match());

}