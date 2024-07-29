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

ll n; 
ll query(vector<vector<char>> &grid, bool ask = true) {
    string q; 
    ll k = 0; 
    for0 (i, n) {
        for0(j, n) q += grid[i][j]; 
        q += "\n"; 
    }
    if (!ask) {
        cout << "! " << endl;  
        cout << q << endl; 
        return 0; 
    }
    cout << "? " << endl;
    cout << q << endl; 
    ll res; 
    cin >> res; 
    return res; 
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    cin >> n; 
    vector<vector<char>> grid(n, vector<char>(n, '1'));
    
    for0(i, n) {
        ll l = 0; 
        ll r = n; 
        while (true) {
            if (r == 0) break; 
            for0(j, r) grid[i][j] = '0'; 
            if (query(grid) == n * n) break; 
            while(r - l > 1) {
                ll mid = (l + r) / 2; 
                for0(j, mid) grid[i][j] = '1'; 
                for (ll j = mid; j < r; j++) grid[i][j] = '0'; 
                if (query(grid) < n * n) l = mid; 
                else r = mid; 
            }
            grid[i][l] = '1';
            r = l;  
            l = 0; 
        }
    }
    query(grid, false); 
}