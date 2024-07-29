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
    return min(abs(x - y), n - abs(x - y));
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    ll n, m, q, k, x, y, b; 
    cin >> n >> m >> q; 
    n *= 2; 
    cin >> b; 
    for0(i, q) {
        cin >> x >> y; 
        ll res = minDirectPass(n, x, y); 
        res = min(res, minDirectPass(n, x, b) + 1 + minDirectPass(n, b + n / 2, y));
        res = min(res, minDirectPass(n, x, b + n / 2) + 1 + minDirectPass(n, b, y));
        cout << res << endl; 
    }
}