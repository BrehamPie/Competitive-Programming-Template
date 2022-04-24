#include<bits/stdc++.h>
using namespace std;
const int mx = 1e5 + 5;
/*
    components: number of SCC.
    sz: size of each SCC.
    comp: component number of each node.

*/
vector<int>adj[mx], radj[mx];

int comp[mx], vis[mx], sz[mx], components;
vector<int>topo;
void dfs(int u) {
    vis[u] = 1;
    for (int v : adj[u])
        if (!vis[v]) dfs(v);
    topo.push_back(u);
}
void dfs2(int u, int val) {
    comp[u] = val;
    sz[val]++;
    for (int v : radj[u])
        if (comp[v] == -1)
            dfs2(v, val);
}
void find_scc(int n) {
    memset(vis, 0, sizeof vis);
    memset(comp, -1, sizeof comp);
    for (int i = 1;i <= n;i++)
        if (!vis[i])
            dfs(i);
    reverse(topo.begin(), topo.end());
    for (int u : topo)
        if (comp[u] == -1)
            dfs2(u, ++components);
}
vector<int>condensed[mx];
void create_condensed(int n) {
    for (int i = 1;i <= n;i++)
        for (int v : adj[i])
            if (comp[i] != comp[v])
                condensed[comp[i]].push_back(comp[v]);
}
/*
    1. Create reverse graph.
    2. Run find_scc() to find SCC.
    -> Might need to create condensation graph by create_condensed().
    -> Think about indeg/outdeg
    for multiple test cases-
        clear adj/radj/comp/vis/sz/topo/condensed.

*/
using ll = long long;
int main() {
    int n;
    scanf("%d", &n);
    vector<int>cost(n + 1);
    for (int i = 1;i <= n;i++)
        scanf("%d", &cost[i]);
    int m;
    scanf("%d", &m);
    for (int i = 0;i < m;i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].push_back(v);
        radj[v].push_back(u);
    }
    find_scc(n);
    vector<long long>ans(components+1,INT_MAX), ans2(components+1,0);
    for (int i = 1;i <= n;i++) {
       ans[comp[i]] = min(ans[comp[i]],(ll)cost[i]);
    }
    for (int i = 1;i <= n;i++) {
        if(cost[i]==ans[comp[i]])
            ans2[comp[i]]++;
    }
    ll totalCost = accumulate(ans.begin()+1,ans.end(),0ll);
    ll totalWay = 1;
    for (int i = 1;i <= components;i++) {
        totalWay *= ans2[i];
        totalWay %= 1000000007;
    }
    cout<<totalCost<<" "<<totalWay<<endl;

}