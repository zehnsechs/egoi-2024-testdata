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

void resetGrid(vector<vector<char>> &grid) {
    for0(i, n) for0(j, n) grid[i][j] = '0'; 
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
    cin >> n; 
    vector<vector<char>> grid(n, vector<char>(n, '0'));
    vector<vector<char>> zero(n, vector<char>(n, '0'));

    for0 (i, n) {
        resetGrid(zero); 
        for0(j, n) zero[i][j] = '1'; 
        if (query(zero) == n * n) {
            for0 (k, i) for0 (j, n) grid[k][j] = '0';
            query(zero, false); 
            return 0; 
        } 

        ll l = 0; 
        ll r = n; 
        while (r - l > 2) {
            resetGrid(zero);
            ll mid = (l + r) / 2; 
            for0(j, n) {
                if (j >= l && j < mid) zero[i][j] = '1';
            } 
            if (mid - l == 1) zero[i][mid] = '1'; 
            ll res = query(zero); 
            if (res < n * (mid - l + (mid - l == 1))) r = mid; 
            else l = mid; 
        }
        grid[i][l] = '1'; 
        grid[i][l + 1] = '1'; 
    } 

    for0(i, n) {
        for0(j, n - 1) {
            if (grid[i][j] == '1') {
                grid[i][j] = '0'; 
                if (query(grid) != n * n) {
                    grid[i][j] = '1'; 
                    grid[i][j + 1] = '0'; 
                } 
                break; 
            }
        }
    }
    query(grid, false);
}