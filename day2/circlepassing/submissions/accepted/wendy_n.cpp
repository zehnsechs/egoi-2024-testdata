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

int n; 
constexpr int lim = 1'000'000'000;
bitset<lim> bridges; 
constexpr int c = 512; 

array<int, lim / c + 2> l, r; 

int minDirectPass(int x, int y) {
    return min(abs(x - y), n - abs(x - y));
}

void update(int entry, int b, array<int, lim / c + 2> &arr) {
    if (arr[entry] == -1) arr[entry] = b;
    if (minDirectPass(entry * c, b) < minDirectPass(entry * c, arr[entry])) arr[entry] = b;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    
    int m, q, x, y, b; 
    cin >> n >> m >> q; 
    n *= 2; 
    
    fill(all(l), -1);
    fill(all(r), -1);

    int lastb = 0, firstb = 0; 

    for0(i, m) {
        cin >> b; 
        bridges[b] = 1; 
        bridges[b + n / 2] = 1; 

        update(b / c, b, r);
        update((b + n / 2) / c, b + n / 2, r);  
        
        update(b / c + (b % c != 0), b, l);
        update((b + n / 2) / c + ((b + n / 2) % c != 0), b + n / 2, l);  

        if (i == m - 1) lastb = b + n / 2; 
        if (i == 0) firstb = b;  
    }

    for0(i, n / c + 2) {
        if (l[i] != -1) lastb = l[i];
        l[i] = lastb; 
    }
    for0(i, n / c + 2) {
        if (r[n / c - i + 1] != -1) firstb = r[n / c - i + 1]; 
        r[n / c - i + 1] = firstb; 
    }

    for0(i, q) {
        cin >> x >> y; 
        int res = minDirectPass(x, y); 
        if (m == 0) {
            cout << res << endl; 
            continue; 
        }

        for (int i = x; i % c != 0; i--) {
            if (bridges[i]) {
                res = min(res, minDirectPass(x, i) + 1 + minDirectPass((i + n / 2) % n, y)); 
                break; 
            }
        }
        res = min(res, minDirectPass(x, l[x / c]) + 1 + minDirectPass((l[x / c] + n / 2) % n, y));

        for (int i = x; i % c != 0 && i < n; i++) {
            if (bridges[i]) {
                res = min(res, minDirectPass(x, i) + 1 + minDirectPass((i + n / 2) % n, y)); 
                break;
            }
        }
        res = min(res, minDirectPass(x, r[x / c + (x % c != 0)]) + 1 + minDirectPass((r[x / c + (x % c != 0)] + n / 2) % n, y));

        cout << res << "\n"; 
    }
}