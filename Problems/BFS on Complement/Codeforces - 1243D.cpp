/* We run bfs on the complement graph of the input graph.
 We will use set instead of vector.
 Once we visit a node we erase it from set.
 */
#include<bits/stdc++.h>
using namespace std;
const int mx = 1e5 + 5;
vector<set<int>>adj(mx);
// Returns number of connected components in complement graph.
int BFSonComplement(int n) {
    queue<int>q;
    set<int>toRemove;
    for (int i = 1;i <= n;i++)toRemove.insert(i);
    int comps = 0;
    for (int i = 1;i <= n;i++) {
        if (toRemove.count(i)) {
            q.push(i);
            comps++;
            toRemove.erase(i);
            while (q.size()) {
                int u = q.front();
                q.pop();
                vector<int>newComer;
                for (int v : toRemove)
                    if (!adj[u].count(v))
                        newComer.push_back(v);
                for (int v : newComer) toRemove.erase(v), q.push(v);

            }
        }
    }
    return comps;
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    while (m--) {
        int u, v;
        scanf("%d%d", &u, &v);
        adj[u].insert(v);
        adj[v].insert(u);
    }
    cout << BFSonComplement(n) - 1 << endl;
}