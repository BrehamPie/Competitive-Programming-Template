#include<bits/stdc++.h>
using namespace std;
char mat[1001][1001];
bool vis[1001][1001][4];
int dist[1001][1001][4];
#define pii pair<int,int>
const int fx[] = { 0,0,1,-1 };
const int fy[] = { 1,-1,0,0 };
int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    for (int i = 0;i < n;i++) {
        scanf("%s", mat[i]);
    }
    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    x1--, y1--, x2--, y2--;
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < m;j++) {
            for (int d = 0;d < 4;d++) {
                vis[i][j][d] = 0;
                dist[i][j][d] = (int)1e9;
            }
        }
    }
    deque<pair<pii, pii> >q;
    q.push_back({ {x1,y1},{0,0} });
    q.push_back({ {x1,y1},{1,0} });
    q.push_back({ {x1,y1},{2,0} });
    q.push_back({ {x1,y1},{3,0} });
    dist[x1][y1][0] = 1;
    dist[x1][y1][1] = 1;
    dist[x1][y1][2] = 1;
    dist[x1][y1][3] = 1;
    while (!q.empty()) {
        pair<pii, pii> cur = q.front();
        q.pop_front();
        int x = cur.first.first, y = cur.first.second;
        int d = cur.second.first, s = cur.second.second;
        if (vis[x][y][d]) continue;
        vis[x][y][d] = 1;
        for (int i = 0;i < 4;i++) {
            int nx = x + fx[i], ny = y + fy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            if (mat[nx][ny] == '#') continue;
            if (i == d && s<k && dist[nx][ny][i]>dist[x][y][d]) {
                dist[nx][ny][i] = dist[x][y][d];
                q.push_back({ {nx,ny},{i,s + 1} });
            }
            else if (dist[nx][ny][i] > dist[x][y][d] + 1) {
                dist[nx][ny][i] = dist[x][y][d] + 1;
                q.push_back({ {nx,ny},{i,1} });
            }
        }

    }
    if (x1 == x2 && y1 == y2)puts("0");
    else {
        int ans = (int)1e9;
        for (int i = 0;i < 4;i++) {
            ans = min(ans, dist[x2][y2][i]);
        }
        if (ans == (int)1e9) puts("-1");
        else printf("%d\n", ans);
    }



}