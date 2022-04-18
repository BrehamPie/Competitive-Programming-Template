#include<bits/stdc++.h>
using namespace std;
// Finds Maximum matching in General Graph 
// Complexity O(NM)
// source: https://codeforces.com/blog/entry/92339?#comment-810242
using pii = pair<int, int>;
int Blossom(vector<vector<int>>& graph) {
    //mate contains matched edge.
    int n = graph.size(), timer = -1;
    vector<int> mate(n, -1), label(n), parent(n),
        orig(n), aux(n, -1), q;
    auto lca = [&](int x, int y) {
        for (timer++; ; swap(x, y)) {
            if (x == -1) continue;
            if (aux[x] == timer) return x;
            aux[x] = timer;
            x = (mate[x] == -1 ? -1 : orig[parent[mate[x]]]);
        }
    };
    auto blossom = [&](int v, int w, int a) {
        while (orig[v] != a) {
            parent[v] = w; w = mate[v];
            if (label[w] == 1) label[w] = 0, q.push_back(w);
            orig[v] = orig[w] = a; v = parent[w];
        }
    };
    auto augment = [&](int v) {
        while (v != -1) {
            int pv = parent[v], nv = mate[pv];
            mate[v] = pv; mate[pv] = v; v = nv;
        }
    };
    auto bfs = [&](int root) {
        fill(label.begin(), label.end(), -1);
        iota(orig.begin(), orig.end(), 0);
        q.clear();
        label[root] = 0; q.push_back(root);
        for (int i = 0; i < (int)q.size(); ++i) {
            int v = q[i];
            for (auto x : graph[v]) {
                if (label[x] == -1) {
                    label[x] = 1; parent[x] = v;
                    if (mate[x] == -1)
                        return augment(x), 1;
                    label[mate[x]] = 0; q.push_back(mate[x]);
                }
                else if (label[x] == 0 && orig[v] != orig[x]) {
                    int a = lca(orig[v], orig[x]);
                    blossom(x, v, a); blossom(v, x, a);
                }
            }
        }
        return 0;
    };
    // Time halves if you start with (any) maximal matching.
    for (int i = 0; i < n; i++)
        if (mate[i] == -1)
            bfs(i);
    int match = 0;
    for (int i = 0;i < n;i++) {
        if (mate[i] + 1)match++;
    }
    return match / 2;
}

int main() {
    int t;
    scanf("%d", &t);
    for (int ks = 1;ks <= t;ks++) {
        int n;
        scanf("%d", &n);
        vector<int>a[1 << n];
        int total = (1 << n);
        vector<vector<pii>>adj(total);
        for (int i = 0;i < total - 1;i++) {
            for (int j = i + 1;j < total;j++) {
                int x;
                scanf("%d", &x);
                adj[i].push_back({ j,x });
                adj[j].push_back({ i,x });
            }
        }
        int hi = 1000000000;
        int lo = 0;
        int ans = 0;
        while (lo <= hi) {
            int mid = (hi + lo) / 2;
            vector<vector<int>>g(total);
            for (int i = 0;i < total;i++) {
                for (auto x : adj[i]) {
                    if (x.second >= mid) {
                        g[i].push_back(x.first);
                    }
                }
            }
            int match = Blossom(g);
            if (match == (total) / 2) {
                ans = mid;
                lo = mid + 1;
            }
            else hi = mid - 1;
        }
        printf("Case %d: %d\n", ks, ans);
    }
}