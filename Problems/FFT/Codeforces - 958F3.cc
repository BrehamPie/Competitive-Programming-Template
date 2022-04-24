#include<bits/stdc++.h>
using namespace std;
const double PI = acos(-1.0);
using ll = long long;
const int mx = 2e5 + 5;
template<typename float_t>
struct mycomplex {
    float_t x, y;

    mycomplex<float_t>(float_t _x = 0, float_t _y = 0) : x(_x), y(_y) {}

    float_t real() const { return x; }
    float_t imag() const { return y; }

    void real(float_t _x) { x = _x; }
    void imag(float_t _y) { y = _y; }

    mycomplex<float_t>& operator+=(const mycomplex<float_t>& other) { x += other.x; y += other.y; return *this; }
    mycomplex<float_t>& operator-=(const mycomplex<float_t>& other) { x -= other.x; y -= other.y; return *this; }

    mycomplex<float_t> operator+(const mycomplex<float_t>& other) const { return mycomplex<float_t>(*this) += other; }
    mycomplex<float_t> operator-(const mycomplex<float_t>& other) const { return mycomplex<float_t>(*this) -= other; }

    mycomplex<float_t> operator*(const mycomplex<float_t>& other) const {
        return { x * other.x - y * other.y, x * other.y + other.x * y };
    }

    mycomplex<float_t> operator*(float_t mult) const {
        return { x * mult, y * mult };
    }

    friend mycomplex<float_t> conj(const mycomplex<float_t>& c) {
        return { c.x, -c.y };
    }

    friend ostream& operator<<(ostream& stream, const mycomplex<float_t>& c) {
        return stream << '(' << c.x << ", " << c.y << ')';
    }
};
using cd = mycomplex<double>;

void fft(vector<cd>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w = w * wlen;
            }
        }
    }
    if (invert) {
        for (cd& x : a) {
            double z = n;
            z = 1 / z;
            x = x * z;
        }
    }
}

void multiply(const vector<ll>& a, const vector<ll>& b, vector<ll>& res) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    size_t n = 1;
    while (n < max(a.size(), b.size()))  n <<= 1;
    n <<= 1;
    fa.resize(n), fb.resize(n);

    fft(fa, false), fft(fb, false);
    for (size_t i = 0; i < n; ++i)
        fa[i] = fa[i] * fb[i];
    fft(fa, true);

    res.resize(n);
    for (size_t i = 0; i < n; ++i) {
        res[i] = (ll)(fa[i].real() + 0.5);
        res[i] %= 1009;
    }
}
vector<int>cnt(200000 + 1);
vector<ll>poly[2 * mx];
int main() {
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0;i < n;i++) {
        int x;
        scanf("%d", &x);
        cnt[x]++;
    }
    set<pair<int, int>>s;
    for (int i = 0;i <= m;i++) {
        if (cnt[i]) {
            poly[i] = vector<ll>(cnt[i] + 1, 1);
            s.insert(make_pair(cnt[i], i));
        }

    }
    while (s.size() > 1) {
        m++;
        int a = (*s.begin()).second;
        s.erase(s.begin());
        int b = (*s.begin()).second;
        s.erase(s.begin());;
        multiply(poly[a], poly[b], poly[m]);
        s.insert(make_pair(poly[m].size(), m));
    }
    int ans = poly[(*s.begin()).second][k];
    printf("%d\n", ans);
}