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

int minDirectPass(int n, int x, int y) {
    return min(abs(x - y), n - abs(x - y));
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    int n, m, q, b, k, x, y; 
    cin >> n >> m >> q; 
    n *= 2; 
    vector<int> left(n, -1); 
    vector<int> right(n, -1); 
    ll lastb = 0, firstb = 0; 
    for0(i, m) {
        cin >> b; 
        left[b] = b; 
        left[b + n/2] = b + n/2; 
        right[b] = b; 
        right[b + n/2] = b + n/2;
        if (i == m - 1) lastb = b + n / 2; 
        if (i == 0) firstb = b;  
    }
    for0(i, n) {
        if (left[i] == i) lastb = i;
        left[i] = lastb; 
    }
    for0(i, n) {
        if (right[n - i - 1] == n - i - 1) firstb = n - i - 1;
        right[n - i - 1] = firstb; 
    }

    for0(i, q) {
        cin >> x >> y; 
        int res = minDirectPass(n, x, y); 
        if (m == 0) {
            cout << res << endl; 
            continue; 
        }
        res = min(res, minDirectPass(n, x, left[x]) + 1 + minDirectPass(n, (left[x] + n/2) % n, y));
        res = min(res, minDirectPass(n, x, right[x]) + 1 + minDirectPass(n, (right[x] + n/2) % n, y));
        cout << res << endl; 
    }
}