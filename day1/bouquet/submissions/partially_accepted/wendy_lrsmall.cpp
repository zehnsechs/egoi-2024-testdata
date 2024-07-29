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
    for0(i, n) cin >> l[i + 1] >> r[i + 1];
    dp[0] = 0; 
    for (ll i = 1; i <= n; i++) {
       for (ll j = max(0ll, i - 4); j < i; j++) {
            if (j + r[j] < i && i - l[i] > j) dp[i] = max(dp[i], dp[j] + 1); 
       }
    }
    cout << *max_element(dp.begin(), dp.end()) << endl; 
}