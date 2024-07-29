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

#define all(x) begin(x), end(x)


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    ll n, m, a, b; 
    cin >> n >> m; 
    for0(i, m) cin >> a >> b; 
    cout << n << endl; 
    for0(i, n) {
        for0(j, n) {
            if (i % 2 == 0) cout << (j % 4 < 2) << " "; 
            else cout << ((j + 1) % 4 < 2) << " ";
        }
        cout << endl; 
    }
    cout << endl; 
}