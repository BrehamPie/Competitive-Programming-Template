

#include <bits/stdc++.h>
using namespace std;
void read(int& x) { scanf("%d", &x); }
void read(string& x) { char y[1000006];scanf("%s", &y);x = y; }
template <typename T, typename... A> void read(T& x, A &...args) { read(x);read(args...); }

int arr[200005];
const int base1 = 31;
const int base2 = 53;
const int mod1 = 1000000007;
const int mod2 = 1018199999;
vector<long long>poly1, poly2;
vector< pair<long long, long long> >pref;
void init(int N) {
    int n = N;
    poly1.resize(n + 1);
    poly2.resize(n + 1);
    pref.resize(n + 1);
    poly1[0] = 1, poly2[0] = 1;
    pref[0] = { 1,1 };
    for (int i = 1;i <= n;i++) {
        poly1[i] = (poly1[i - 1] * base1) % mod1;
        poly2[i] = (poly2[i - 1] * base2) % mod2;
        pref[i].first = (pref[i - 1].first + poly1[i]) % mod1;
        pref[i].second = (pref[i - 1].second + poly2[i]) % mod2;
    }
}


struct SegmentTree {
#define lc (C << 1)
#define rc (C << 1 | 1)
#define M ((L + R) >> 1)
    struct node {
        pair<long long, long long> sum;
        node() : sum({ 0,0 }) {}
    };
    vector<node>st;
    vector<bool>isLazy;
    vector<int>lazy;
    SegmentTree(int N) :st(4 * N), isLazy(4 * N), lazy(4 * N) {}
    void push(int C, int L, int R) {
        if (!isLazy[C]) return;
        if (L != R) {
            isLazy[lc] = 1;
            isLazy[rc] = 1;
            lazy[lc] = lazy[C];
            lazy[rc] = lazy[C];
        }
        st[C].sum.first = (lazy[C] * (pref[R - L].first)) % mod1;
        st[C].sum.second = (lazy[C] * (pref[R - L].second)) % mod2;
        lazy[C] = 0;
        isLazy[C] = false;
    }
    void build(int C, int L, int R) {
        if (L == R) {
            st[C].sum = { arr[L],arr[L] };
            return;
        }
        build(lc, L, M);
        build(rc, (M)+1, R);
        st[C].sum.first = (st[lc].sum.first + poly1[M - L + 1] * st[rc].sum.first) % mod1;
        st[C].sum.second = (st[lc].sum.second + poly2[M - L + 1] * st[rc].sum.second) % mod2;
    }
    node Query(int C, int L, int R, int i, int j) {
        push(C, L, R);
        if (L == i && R == j) return st[C];
        if (i > M) return Query(rc, M + 1, R, i, j);
        else if (j <= M) return Query(lc, L, M, i, j);
        else {
            node d1 = Query(lc, L, M, i, M);
            node d2 = Query(rc, M + 1, R, M + 1, j);
            node ret;
            ret.sum.first = (d1.sum.first + poly1[M + 1 - i] * d2.sum.first % mod1) % mod1;
            ret.sum.second = (d1.sum.second + poly2[M + 1 - i] * d2.sum.second % mod2) % mod2;
            return ret;
        }

    }
    void Update(int C, int L, int R, int i, int j, int val) {
        push(C, L, R);
        if (j < L || i > R) return;
        if (i <= L && R <= j) {
            isLazy[C] = 1;
            lazy[C] = val;
            push(C, L, R);
            return;
        }
        Update(lc, L, M, i, j, val);
        Update(rc, M + 1, R, i, j, val);
        st[C].sum.first = (st[lc].sum.first + poly1[M - L + 1] * st[rc].sum.first) % mod1;
        st[C].sum.second = (st[lc].sum.second + poly2[M - L + 1] * st[rc].sum.second) % mod2;
    }
};

int main() {
    int n, m, k;
    read(n, m, k);
    init(n);
    string str;
    read(str);
    for (int i = 0;i < n;i++) {
        arr[i + 1] = str[i] - '0' + 1;
    }
    SegmentTree st(n);
    st.build(1, 1, n);
    m += k;
    while (m--) {
        int t, l, r, d;
        read(t, l, r, d);
        if (t == 1) {
            st.Update(1, 1, n, l, r, d + 1);
        }
        else {
            if (d == (r - l + 1)) {
                puts("YES");
                continue;
            }
            pair<long long, long long> val = st.Query(1, 1, n, l, r - d).sum;
            pair<long long, long long> val2 = st.Query(1, 1, n, l + d, r).sum;
            if (st.Query(1, 1, n, l, r - d).sum == st.Query(1, 1, n, l + d, r).sum) {
                puts("YES");
            }
            else {
                puts("NO");
            }
        }
    }

}