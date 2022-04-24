#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int mx = 2e5 + 5;
const int Lg = 22;
int arr[mx];
vector<pair<int, int>>adj[mx];
int val[mx];
/*
    1-indexed.
    head[i] is the head of the i-th chain.
    pos[i] is the position of the i-th node in the chain.
*/
struct  HeavyLightDecomposition {
#define lc (C << 1)
#define rc (C << 1 | 1)
#define M  ((L + R) >> 1)
    inline static int N;
    vector<int>parent, head, depth, pos, heavy, dp[Lg], lazy, isLazy;
    struct node {
        ll sum;
        node() : sum(0) {}
    };

    vector<node>st;
    int cur;
    HeavyLightDecomposition(int _N) :st(4 * _N), isLazy(4 * _N), lazy(4 * _N), cur(0) {
        N = _N;
        parent = head = depth = pos = heavy = vector<int>(_N + 1, 0);
        for (int i = 0;i < Lg;i++) dp[i] = vector<int>(_N + 1, 0);
    }
    void combine(node& cur, node& l, node& r) {
        cur.sum = l.sum + r.sum;
    }
    void push(int C, int L, int R) {
        if (!isLazy[C]) return;
        if (L != R) {
            isLazy[lc] = 1;
            isLazy[rc] = 1;
            lazy[lc] += lazy[C];
            lazy[rc] += lazy[C];
        }
        st[C].sum = (R - L + 1) * lazy[C];
        lazy[C] = 0;
        isLazy[C] = false;
    }
    void build(int C = 1, int L = 1, int R = N) {
        if (L == R) {
            st[C].sum = arr[L];
            return;
        }
        build(lc, L, M);
        build(rc, M + 1, R);
        combine(st[C], st[lc], st[rc]);
    }
    node Query(int i, int j, int C = 1, int L = 1, int R = N) {
        push(C, L, R);
        if (j < L || i > R) return node();  // default val 0/INF
        if (i <= L && R <= j) return st[C];
        node ret;
        node d1 = Query(i, j, lc, L, M);
        node d2 = Query(i, j, rc, M + 1, R);
        combine(ret, d1, d2);
        return ret;
    }
    void Update(int i, int j, int val, int C = 1, int L = 1, int R = N) {
        push(C, L, R);
        if (j < L || i > R) return;
        if (i <= L && R <= j) {
            isLazy[C] = 1;
            lazy[C] = val;
            push(C, L, R);
            return;
        }
        Update(i, j, val, lc, L, M);
        Update(i, j, val, rc, M + 1, R);
        combine(st[C], st[lc], st[rc]);
    }
    int dfs(int u) {
        int sub = 1, big = 0;
        for (int i = 1;i < Lg;i++)
            dp[i][u] = dp[i - 1][dp[i - 1][u]];
        for (auto x : adj[u]) {
            int v = x.first;
            int w = x.second;
            if (v == parent[u]) continue;
            parent[v] = u;
            dp[0][v] = u;
            depth[v] = depth[u] + 1;
            val[v] = w;
            int subsize = dfs(v);
            if (subsize > big) big = subsize, heavy[u] = v;
            sub += subsize;
        }
        return sub;
    }
    int lca(int u, int v) {
        if (depth[v] < depth[u])swap(u, v);
        int diff = depth[v] - depth[u];
        for (int i = 0;i < Lg;i++)
            if (diff & (1 << i)) v = dp[i][v];
        for (int i = Lg - 1;i >= 0;i--)
            if (dp[i][u] != dp[i][v]) u = dp[i][u], v = dp[i][v];
        return u == v ? u : dp[0][u];
    }
    void decompose(int u, int par) {
        head[u] = par;
        pos[u] = ++cur;
        arr[cur] = val[u];
        if (heavy[u]) decompose(heavy[u], par);
        for (auto v : adj[u]) {
            if (v.first == parent[u] || v.first == heavy[u]) continue;
            decompose(v.first, v.first);
        }
    }
    void makeHLD(int root = 1) {
        dfs(root);
        decompose(root, root);
        build();
    }
    node pathQuery(int u, int v) {
        node ret;
        for (; head[u] != head[v]; v = parent[head[v]]) {
            if (depth[head[u]] > depth[head[v]]) swap(u, v);
            node tmp = Query(pos[head[v]], pos[v]);
            combine(ret, ret, tmp);
        }
        if (depth[u] > depth[v]) swap(u, v);
        node tmp = Query(pos[u], pos[v]);
        combine(ret, ret, tmp);
        // return whats needed, not node.
        return ret;
    }
    void pathUpdate(int u, int v, int val) {
        for (; head[u] != head[v]; v = parent[head[v]]) {
            if (depth[head[u]] > depth[head[v]]) swap(u, v);
            Update(pos[head[v]], pos[v], val);
        }
        if (depth[u] > depth[v]) swap(u, v);
        Update(pos[u], pos[v], val);
    }
};
/*
    Usage:
    HeavyLightDecomposition HLD(N);
    HLD.makeHLD();
    HLD.pathQuery(u, v);
    HLD.pathUpdate(u, v, val);
    ** In case of edge query, subtract value of lca(u, v).
    Note: inline static only supports C++17.
*/

int main() {
   
}