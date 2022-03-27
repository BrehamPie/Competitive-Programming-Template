#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9;
void lis(vector<int>& a) {
    int n = a.size();
    vector<int>d(n + 1, inf), id(n + 1, -1), path(n + 1, -1);
    d[0] = -inf;
    // d[i] holds the smallest value that has a subsequence of length i.
    int ans = 1;
    //id holds the index ,path holds the previous elements index.
    for (int i = 0;i < n;i++) {
        int j = upper_bound(d.begin(), d.end(), a[i]) - d.begin();
        // use lower bound if you need non-decreasing subsequence.
        if (d[j - 1] < a[i] && a[i] < d[j]) {
            d[j] = a[i];
            id[j] = i;
            path[i] = id[j - 1];
            ans = max(j, ans);
        }
    }
    stack<int>s;
    int cur = id[ans];
    while (cur + 1) {
        s.push(a[cur]);
        cur = path[cur];
    }
    //ans holds the length of LIS
    // stack holds the whole sequence.
}
int main() {
  
}