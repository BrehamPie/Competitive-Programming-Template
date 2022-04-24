#include<bits/stdc++.h>
using namespace std;
const int mx = 1e5 + 5;
vector<int>adj[mx], disc, low;
int timer;
set<pair<int,int>>bridge;
void dfs(int u, int p = -1) {
    low[u] = disc[u] = ++timer;
    int child = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        if (disc[v]) {
            if(disc[v]<disc[u])bridge.insert({ u,v });
            low[u] = min(low[u], disc[v]);
        }
        else {
            bridge.insert({ u,v });
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            child++;
            if (disc[u] < low[v]) bridge.insert({v,u});
        }
    }
}
void findcuts(int n) {
    disc = low = vector<int>(n + 1, 0);
    timer = 0;
    for (int i = 1; i <= n; i++) {
        if (!disc[i]) dfs(i);
    }
}
int main() {
    int n,m;
    int test=1;
    while(scanf("%d %d",&n,&m) && n){
        for(int i=0;i<=n;i++)adj[i].clear();
        bridge.clear();
        for(int i=0;i<m;i++){
            int u,v;
            scanf("%d %d",&u,&v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        findcuts(n);
        printf("%d\n",test++);
        puts("");
        for(auto x:bridge){
            printf("%d %d\n",x.first,x.second);
        }
        puts("#");
    }
}