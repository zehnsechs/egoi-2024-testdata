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
    cout << 2 * n - 1 << endl; 
    for0(i, n - 1) {
        for0(j, n) {
            if (i + 1 == j) cout << "0 ";
            else cout << j << " ";
        }
        cout << endl; 
         for0(j, n) {
            if (i + 1 == j) cout << "0 ";
            else cout << j << " ";
        }
        cout << endl; 
    }
    for0(i, n) cout << "0 "; 
    cout << endl; 
}