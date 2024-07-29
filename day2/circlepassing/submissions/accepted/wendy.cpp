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
    
    ll n, m, q, a, x, y; 
    cin >> n >> m >> q; 
    set<ll> s; 
    for0(i, m) {
        cin >> a; 
        s.insert(a); 
        s.insert(a + n); 
    } 
    n *= 2; 

    for0(i, q) {
        cin >> x >> y; 
        
        // pass directly
        ll res = minDirectPass(n, x, y); 
 
        // right bridge
        auto b = s.upper_bound(x);
        if (b == s.end()) b = s.begin(); 
        res = min(res, minDirectPass(n, x, *b) + minDirectPass(n, (*b + n / 2) % n, y) + 1);   
        // cout << *b << " " << res << endl; 

        // left bridge
        if (b != s.begin()) b = prev(b);
        else b = prev(s.end());  
        res = min(res, minDirectPass(n, x, *b) + minDirectPass(n, (*b + n / 2) % n, y) + 1);   

        cout << res << endl; 
    }
}