#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
struct Hash {
    // bases should be greater than total characters
    const int base1 = 31;
    const int base2 = 53;
    const int mod1 = 1000000007;
    const int mod2 = 1018199999;
    vector<ll>poly1, poly2;
    vector<pll>pref;
    int n;
    void init(int N) {
        n = N;
        poly1.resize(n + 1);
        poly2.resize(n + 1);
        pref.resize(n + 1);
        poly1[0] = 1, poly2[0] = 1;
        for (int i = 1;i <= n;i++) {
            poly1[i] = (poly1[i - 1] * base1) % mod1;
            poly2[i] = (poly2[i - 1] * base2) % mod2;
        }
    }
    void build(string& str) {
        int N = str.size();
        for (int i = 0;i < n;i++) {
            int d = str[i] - 'a' + 1;
            pref[i + 1].first = (d + pref[i].first * base1) % mod1;
            pref[i + 1].second = (d + pref[i].second * base2) % mod2;
        }
    }

    pll subHash(int l, int r) {
        int len = r - l + 1;
        pll ret;
        ret.first = (pref[l + len].first - ((pref[l].first * poly1[len]) % mod1) + mod1) % mod1;
        ret.second = (pref[l + len].second - ((pref[l].second * poly2[len]) % mod2) + mod2) % mod2;
        return ret;
    }
    // If you change here ,you can't use subhashes anymore.be careful about sending now and pre
    void change(int pos, int now, int pre) {
        pref[n].first = (pref[n].first - ((pre + 1) * poly1[pos + 1]) % mod1 + mod1) % mod1;
        pref[n].first = (pref[n].first + ((now + 1) * poly1[pos + 1]) % mod1) % mod1;
        pref[n].second = (pref[n].second - ((pre + 1) * poly2[pos + 1]) % mod2 + mod2) % mod2;
        pref[n].second = (pref[n].second + ((now + 1) * poly2[pos + 1]) % mod2) % mod2;
    }
    int LCP(int id1, int id2, int len) {
        int lo = 1, hi = len;
        while (lo <= hi) {
            int mid = (hi + lo) / 2;
            if (subHash(id1, id1 + mid) == subHash(id2, id2 + mid))
                lo = mid + 1;
            else hi = mid - 1;
        }
        return hi;
    }
};
/*
    0 based index.
    call init first.
    inspired from: https://codeforces.com/blog/entry/60445
*/
int main() {

}
