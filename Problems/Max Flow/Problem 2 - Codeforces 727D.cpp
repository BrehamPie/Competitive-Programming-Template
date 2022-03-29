#include<bits/stdc++.h>
using namespace std;
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
    int tsh[6];
    string val[7] = { "","S","M","L","XL","XXL","XXXL" };
    map<string, int>mp = { {"S",1},{"M",2},{"L",3},{"XL",4},{"XXL",5},{"XXXL",6} };
    for (int i = 0;i < 6;i++)cin >> tsh[i];
    int n;cin >> n;
    Dinic dic(n + 8);
    for (int i = 7;i <= n + 6;i++) {
        string str;
        cin >> str;
        string ch1, ch2;
        bool f = 0;
        for (int j = 0;j < str.size();j++) {
            if (str[j] == ',') { f = 1;continue; }
            if (!f) ch1 += str[j];
            else ch2 += str[j];
        }
        dic.addEdge(i, mp[ch1], 1);
        if (f) dic.addEdge(i, mp[ch2], 1);
    }
    for (int i = 1;i <= n;i++) dic.addEdge(0, i + 6, 1);
    for (int i = 1;i <= 6;i++) { dic.addEdge(i, n + 7, tsh[i - 1]); }

    int matched = dic.maxFlow(0, n + 7);
    if (matched == n) {
        puts("YES");
        vector<int>ans(n + 1);
        int k = dic.edge.size();
        for (int i = 0;i < k;i += 2) {
            int u = dic.edge[i].u;
            int v = dic.edge[i].v;
            int f = dic.edge[i].flow;
            if (f) {
                u -= 6;
                if (u > 0 && u <= n && v > 0 && v < 7) {
                    ans[u] = v;
                }
            }
        }
        for (int i = 1;i <= n;i++)cout << val[ans[i]] << endl;
    }
    else {
        puts("NO");
    }

}