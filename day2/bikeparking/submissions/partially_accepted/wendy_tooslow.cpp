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

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

    ll n; 
    cin >> n; 
    vl x(n), y(n);
    for0(i, n) cin >> y[i];
    for0(i, n) cin >> x[i];

    // vl remaining(n, 0);
    ll res = 0;  
    ll last = n - 1; 
    for (ll i = n - 2; i >= 0; i--) {
        while (x[last] == 0) last--; 
        for (ll j = i + 1; j <= last && y[i] > 0; j++) {
            ll add = min(x[j], y[i]); 
            x[j] -= add; 
            y[i] -= add; 
            res += add; 
        }
    }
    for0(i, n) {
        ll down = max(0ll, x[i] - y[i]); 
        res -= down; 
    }
    cout << res << endl; 
}