#include<bits/stdc++.h>
using namespace std;
using ll = long long;
char mat[3001][3001];
bool vis[3001][3001][2];
int dist[3001][3001][2];
#define pii pair<int,int>
const int fx[] = { 0,1 };
const int fy[] = { 1,0 };
int main() {
    int n, m, k, t;
    scanf("%d%d%d%d", &n, &m, &k, &t);
    for (int i = 0;i < n;i++) scanf("%s", mat[i]);
    for (int i = 0;i < n;i++)
        for (int j = 0;j < m;j++)
            for (int d = 0;d < 2;d++)
                dist[i][j][d] = INT_MAX;
    deque<pair<pii, pii> >q;
    q.push_back({ {0,0},{0,0} });
    q.push_back({ {0,0},{1,0} });
    dist[0][0][0] = 1;
    dist[0][0][1] = 1;
    while (!q.empty()) {
        pair<pii, pii> cur = q.front();
        q.pop_front();
        int x = cur.first.first, y = cur.first.second;
        int d = cur.second.first, s = cur.second.second;
        if (vis[x][y][d]) continue;
        vis[x][y][d] = 1;
        for (int i = 0;i < 2;i++) {
            int nx = x + fx[i], ny = y + fy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m || mat[nx][ny] == '#') continue;
            if (i == d && s<k && dist[nx][ny][i]>dist[x][y][d]) {
                dist[nx][ny][i] = dist[x][y][d];
                q.push_front({ {nx,ny},{i,s + 1} });
            }
            else if (dist[nx][ny][i] > dist[x][y][d] + 1) {
                dist[nx][ny][i] = dist[x][y][d] + 1;
                q.push_back({ {nx,ny},{i,1} });
            }
        }
    }
    n--, m--;
    ll ans = INT_MAX;
    for (int i = 0;i < 2;i++) ans = min(ans, 1ll*dist[n][m][i]);
    if (ans == INT_MAX) ans = -1;
    else  ans = t * ans + (n + m);
    printf("%lld\n", ans);
}