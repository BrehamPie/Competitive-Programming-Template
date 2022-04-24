#include<bits/stdc++.h>
using namespace std;
const int mx = 1e5 + 5;
vector<int>adj[mx], disc, low, ap;
int timer;
int dfs(int u, int p = -1) {
    low[u] = disc[u] = ++timer;
    int child = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (disc[v]) {
            low[u] = min(low[u], disc[v]);
        }
        else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            child++;
            if (disc[u] <= low[v]) ap[u] = 1;
            /* for bridge:
                disc[u]<low[v] - (u,v) is bridge.
            */
        }
    }
    return child;
}
void findcuts(int n) {
    ap = disc = low = vector<int>(n + 1, 0);
    timer = 0;
    for (int i = 1; i <= n; i++) {
        if (!disc[i]) ap[i] = dfs(i) > 1;
    }
}
/*
    Important tips:
    *  2 edge connected components: no bridge in graph
    *  if there are bridge SCC is not possible
*/
int main(){
    
}