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
    vl l(n + 1), r(n + 1), dp(n + 1, 1);
    vector<vl> ins(n + 1); 
    for0(i, n) {
        cin >> l[i + 1] >> r[i + 1];
        if (i + r[i + 1] + 2 < n + 1) ins[i + r[i + 1] + 2].pb(i + 1); 
    } 
    set<ll> pick; 
    dp[0] = 0; 
    for (ll i = 1; i <= n; i++) {
        for (ll x : ins[i]) {
            auto it = pick.insert(x).first; 
            if (it != pick.begin() && dp[*it] <= dp[*prev(it)]) {
                pick.erase(it);
                continue;
            }  
            while (next(it) != pick.end() && dp[*next(it)] <= dp[*it]) pick.erase(next(it)); 
        }
        if (l[i] >= i || pick.empty()) continue; 
        auto it = pick.upper_bound(i - l[i] - 1); 
        if (it == pick.begin()) continue; 
        else dp[i] = max(dp[i], dp[*prev(it)] + 1);
    }
    cout << *max_element(dp.begin(), dp.end()) << endl; 
}