/*
    Solution Idea: 0-1 BFS.
    Time Complexity: O(N)
    
*/
class Solution {
public:
    const int fx[4] = {0,0,1,-1};
    const int fy[4] = {1,-1,0,0};
    int minCost(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        bool vis[n][m];
        int dist[n][m];
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                vis[i][j]=0;
                dist[i][j]=INT_MAX;
            }
        }
        deque<pair<int,int>>q;
        q.push_back({0,0});
        dist[0][0]=0;
        while(q.size()){
            auto u = q.front();
            q.pop_front();
            int x = u.first;
            int y = u.second;
            if(vis[x][y])continue;
            vis[x][y] = 1;
            for(int i=0;i<4;i++){
                int dx = x+fx[i];
                int dy = y+fy[i];
                if(dx<0 || dx>=n || dy<0 || dy>=m) continue;
                int dur = dist[x][y];
                if(i!=grid[x][y]-1)dur++;
                if(dur==dist[x][y] && dist[dx][dy]>dur){
                    dist[dx][dy] = dur;
                    q.push_front({dx,dy});
                }
                else if(dist[dx][dy]>dur){
                    dist[dx][dy] = dur;
                    q.push_back({dx,dy});
                }
            }
            
        }
        return dist[n-1][m-1];
    }
};