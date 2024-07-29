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
ll query(vector<vector<char>> &grid, bool ask) {
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
    for0 (i, n) {
        for0 (j, n) {
            grid[i][j] = '0'; 
            ll res = query(grid, true); 
            if (res < n * n) grid[i][j] = '1'; 
        }
    } 
    query(grid, false);
}