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
    for0(i, n) cin >> x[i];
    for0(i, n) cin >> y[i];

    ll res = 0;  
    vector<pl> todo; 
    for (ll i = n - 2; i >= 0; i--) {
        todo.pb({i + 1, y[i + 1]}); 
        while(!todo.empty() && x[i] > 0) {
            ll add = min(todo.back().second, x[i]); 
            todo.back().second -= add; 
            x[i] -= add; 
            res += add; 
            if (todo.back().second == 0) todo.pop_back(); 
        }
    }
    for (pl rest : todo) res -= max(0ll, rest.second - x[rest.first]); 
    cout << res -  max(0ll, y[0] - x[0]) << endl; 
}