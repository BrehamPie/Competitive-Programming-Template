#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9;
/**
 *  A number can be a fit if a[i]-i>=0 else we can't have i-1 numbers before it.
 *  So if a[i]-i<=0 we must change it.
 *  Else if a[i]-i>0 we find the Longest non-decreasing subsequence of these elements.
 *  Hence answer = size - length of Longest non-decreasing subsequence. 
 **/
int lis(vector<int>& a) {
    int n = a.size();
    vector<int>d(n + 1, inf), id(n + 1, -1), path(n + 1, -1);
    d[0] = -inf;
    int ans = 1;
    for (int i = 0;i < n;i++) {
        int j = lower_bound(d.begin(), d.end(), a[i]) - d.begin();
        if (d[j - 1] < a[i] && a[i] < d[j]) {
            d[j] = a[i];
            id[j] = i;
            path[i] = id[j - 1];
            ans = max(j, ans);
        }
    }
    return ans;
}
int main() {
    int n;
    cin >> n;
    vector<int>a(n);
    for (int& x : a)cin >> x;
    vector<int>b;
    for (int i = 0;i < n;i++) {
        if (a[i] - i > 0)b.push_back(a[i]-i);
    }
    cout << n - lis(b) << endl;
}