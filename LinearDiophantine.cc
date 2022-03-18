/**
 * Find Solution of
 *  ax+by = c where a,b,c is given.
 * (ax+by)%b = (ax)
 * Hence ax ≡ c (mod b)
 * if a and b are coprime we can say,
 *          x ≡ ca^(-1) (mod b)
 * let g = gcd(x,y).Then
 *  x = (c/g)(a/g)(mod b/g)
 *  y = (c-ax)/b
 * Other solutions
 *  x = x + k*(b/g)
 *  y = y - k*(a/g)
 **/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// extended-euclidean
ll gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    ll x1, y1;
    ll d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
// return true if solution exists
bool findSolution(ll a, ll b, ll c, ll& x, ll& y, ll& g) {
    g = gcd(abs(a), abs(b), x, y);
    if (c % g) return false;
    x *= c / g;
    y *= c / g;
    if (a < 0) x *= -1;
    if (b < 0) y *= -1;
    return true;
}
// for ax+by+cz = d -> gcd(a,b)*X+cz = d
// for all solution add b/g with x and -a/g with y

// for all solution in a range - Lightoj1306

void shift_solution(ll& x, ll& y, ll a, ll b, ll cnt) {
    x += cnt * b;
    y -= cnt * a;
}

ll find_all_solutions(ll a, ll b, ll c, ll minx, ll maxx, ll miny,
    ll maxy) {
    ll x, y, g;
    if (!findSolution(a, b, c, x, y, g)) return 0;
    a /= g;
    b /= g;
    ll sign_a = a > 0 ? +1 : -1;
    ll sign_b = b > 0 ? +1 : -1;
    shift_solution(x, y, a, b, (minx - x) / b);
    if (x < minx) shift_solution(x, y, a, b, sign_b);
    if (x > maxx) return 0;
    ll lx1 = x;
    shift_solution(x, y, a, b, (maxx - x) / b);
    if (x > maxx) shift_solution(x, y, a, b, -sign_b);
    ll rx1 = x;
    shift_solution(x, y, a, b, -(miny - y) / a);
    if (y < miny) shift_solution(x, y, a, b, -sign_a);
    if (y > maxy) return 0;
    ll lx2 = x;
    shift_solution(x, y, a, b, -(maxy - y) / a);
    if (y > maxy) shift_solution(x, y, a, b, sign_a);
    ll rx2 = x;
    if (lx2 > rx2) swap(lx2, rx2);
    ll lx = max(lx1, lx2);
    ll rx = min(rx1, rx2);
    if (lx > rx) return 0;
    return (rx - lx) / abs(b) + 1;
}
int main() {

}