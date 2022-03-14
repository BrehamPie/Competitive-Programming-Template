#include <bits/stdc++.h>
using namespace std;
const int mx = 1e5 + 5;
const int block_size = 440;
const int lg = 23;
using ll = long long;
vector<int> adj[mx];
int dp[lg + 1][mx]; /* Keeps track of 2^ith parent */
int level[mx], st[mx], en[mx], ID[mx * 2], vis[mx];
int Time;
/* calculate start time,end time and euler tour */
void dfs(int u) {
    st[u] = ++Time;
    ID[Time] = u;
    for (int i = 1; i <= 22; i++) dp[i][u] = dp[i - 1][dp[i - 1][u]];
    for (int v : adj[u]) {
        if (dp[0][u] == v) continue;
        level[v] = level[u] + 1;
        dp[0][v] = u;
        dfs(v);
    }
    en[u] = ++Time;
    ID[Time] = u;
}
/* return lca of u,v */
int lca(int u, int v) {
    if (level[v] < level[u]) swap(u, v);
    int dif = level[v] - level[u];
    for (int i = 0; i <= lg; i++)
        if ((dif >> i) & 1) v = dp[i][v];
    for (int i = lg; i >= 0; i--)
        if (dp[i][u] != dp[i][v]) u = dp[i][u], v = dp[i][v];
    return u == v ? u : dp[0][u];
}
/* Query Structure */
struct Query {
    int L, R, id, LCA, block_id;
    Query() {}
    Query(int _L, int _R, int _LCA, int _id) : L(_L), R(_R), LCA(_LCA), id(_id) {
        block_id = L / block_size;
    }
    bool operator<(const Query& p) const {
        return block_id == p.block_id ? R < p.R : block_id < p.block_id;
    }
};
Query Q[mx];
ll ans[mx];
/* Define other problem specific data */
inline void add(int id) {
    // Problem Specific operations
}
inline void remove(int id) {
    // Problem Specific operations
}
inline void change(int id) {
    if (vis[id])
        remove(id);
    else
        add(id);
    vis[id] ^= 1;
}
inline int get() {
    // Problem Specific Operations
}
void MO(int n) {
    sort(Q + 1, Q + n + 1);
    int L = 1, R = 0;
    for (int i = 1; i <= n; i++) {
        Query q = Q[i];
        while (L > q.L) change(ID[--L]);
        while (R < q.R) change(ID[++R]);
        while (L < q.L) change(ID[L++]);
        while (R > q.R) change(ID[R--]);
        if (q.LCA != ID[L] && q.LCA != ID[R]) change(q.LCA);
        ans[q.id] = get();
        if (q.LCA != ID[L] && q.LCA != ID[R]) change(q.LCA);
    }
}
/*
    -> In path query LCA needs to be ignored.
    -> Node starts with 1.
    -> Query Starts with 1.
    -> call dfs(1).
    -> Adding Query:
        int p = lca(u, v);
        if (st[u] > st[v]) swap(u, v);
        if (p == u || p == v) Q[i] = Query(st[u], st[v], p, i);
        else  Q[i] = Query(en[u], st[v], p, i);
*/
int main() {

}