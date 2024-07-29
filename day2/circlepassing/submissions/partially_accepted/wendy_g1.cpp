#include <bits/stdc++.h>
#define f(i, s, k, l) for (int i = s; i < k; i += l)
#define for0(i, k) f(i, 0, k, 1)

#define pl pair<long long, long long>
#define pb push_back

#define vl vector<long long>
#define vi vector<int>
#define sz(x) (ll)(x).size()

using namespace std;
using ll = long long;
using ld = long double;

ll minDirectPass(ll n, ll x, ll y) {
    return min(abs(x - y) % n, n - abs(x - y) % n);
}

int main() {
    ll n, m, q, x, y;
    cin >> n >> m >> q;
    cin >> x;
    n *= 2;
    for0(i, q) {
        cin >> x >> y;
        cout << min(minDirectPass(n, x, y), 1 + minDirectPass(n, x + n / 2, y)) << endl;
    }
}