#include<bits/stdc++.h>
using namespace std;
const int mx = 2e5 + 5;
const int Lg = 22;
vector<int>adj[mx];
int level[mx];
int dp[Lg][mx];
void dfs(int u) {
    for (int i = 1;i < Lg;i++)
        dp[i][u] = dp[i - 1][dp[i - 1][u]];
    for (int v : adj[u]) {
        if (dp[0][u] == v)continue;
        level[v] = level[u] + 1;
        dp[0][v] = u;
        dfs(v);
    }
}
int lca(int u, int v) {
    if (level[v] < level[u])swap(u, v);
    int diff = level[v] - level[u];
    for (int i = 0;i < Lg;i++)
        if (diff & (1 << i))
            v = dp[i][v];
    for (int i = Lg - 1;i >= 0;i--)
        if (dp[i][u] != dp[i][v])
            u = dp[i][u], v = dp[i][v];
    return u == v ? u : dp[0][u];
}
/*
    LCA(u,v) with root r:
        lca(u,v)^lca(u,r)^lca(v,r)
*/
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1;i < n;i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1);
    int q;
    scanf("%d", &q);
    while (q--) {
        int u, v, r;
        scanf("%d%d%d", &u, &v, &r);
        int ans = lca(u, v) ^ lca(u, r) ^ lca(v, r);
        printf("%d\n", ans);
    }
}
