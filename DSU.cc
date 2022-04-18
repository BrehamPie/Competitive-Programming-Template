#include<bits/stdc++.h>
using namespace std;
// Complexity: O(n)
struct DSU {
    vector<int>par, rnk, sz;///par-parent ,rnk - upper bound of tree depth,sz-size of component
    int c;///Total components.
    DSU(int n) : par(n + 1), rnk(n + 1, 0), sz(n + 1, 0), c(n) {
        for (int i = 1;i <= n;i++) par[i] = i, sz[i] = 1;
    }
    int root(int i) { return par[i] == i ? i : (par[i] = root(par[i])); }
    bool same(int a, int b) { return root(a) == root(b); }
    int get_size(int a) { return sz[root(a)]; }
    int components() { return c; }
    int marge(int a, int b) {
        a = root(a), b = root(b);
        if (a == b) return -1;
        c--;
        if (rnk[a] > rnk[b]) swap(a, b);
        par[a] = b;
        sz[b] += sz[a];
        if (rnk[a] == rnk[b]) rnk[b]++;
        return b;
    }
};
/*
    Take instance with node size.
    Index starts from 1.
    Path Compression Used.
    Problem: https://cses.fi/problemset/task/1676
*/
int main() {


}