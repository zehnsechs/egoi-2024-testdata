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

    ll n, w, x, y;
    cin >> w >> n;
    vl p(n);
    for0(i, n) cin >> p[i];

    if (w == 0) {
        cout << 3 << endl;
        return 0;
    }
    cin >> x;
    cout << x << endl;;
    cin >> y;
    if (p[0] == 0) cout << y << endl;
    else cout << (x + y) % 2 << endl;
}