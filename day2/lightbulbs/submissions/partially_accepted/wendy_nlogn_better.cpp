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


    bool firstIsRow = true; 
    grid[0][0] = '1'; 
    grid[0][1] = '1'; 
    ll t = query(grid); 
    if (t == 2 * n) firstIsRow = false; 
    else if (t != n) {
        grid[0][1] = '0'; 
        grid[0][2] = '1';
        ll res = query(grid); 
        grid[0][0] = '0'; 
        grid[0][1] = '1';
        if (query(grid) < res) firstIsRow = false;  
    }   

    set<ll> asFirst, other; 
    asFirst.insert(0); 
    for(ll i = 1; i < n; i++) {
        resetGrid(grid); 
        grid[0][0] = '1'; 
        grid[i][i] = '1'; 
        if (query(grid) == 2 * n) asFirst.insert(i); 
        else other.insert(i); 
    }
    resetGrid(grid); 

    bool row = true; 
    set<ll> rest; 
    if (sz(asFirst) > sz(other)) {
        rest = other; 
        row = firstIsRow;
        for (ll x : asFirst) grid[x][x] = '1'; 
    } else {
        rest = asFirst; 
        row = !firstIsRow; 
        for (ll x : other) grid[x][x] = '1'; 
    }

    for0 (i, n) {
        if (grid[i][i] == '1') continue; 
        resetGrid(zero); 
        for0(j, n) {
            if (row) zero[i][j] = '1';
            else zero[j][i] = '1';
        } 
        if (query(zero) == n * n) {
            query(zero, false); 
            return 0; 
        } 

        ll l = 0; 
        ll r = n; 
        while (r - l > 2) {
            resetGrid(zero);
            ll mid = (l + r) / 2; 
            for0(j, n) {
                if (j >= l && j < mid) {
                    if (row) zero[i][j] = '1';
                    else zero[j][i] = '1';
                }
            } 
            if (mid - l == 1) {
                if (row) zero[i][mid] = '1';
                else zero[mid][i] = '1';
            }
            ll res = query(zero); 
            if (res < n * (mid - l + (mid - l == 1))) r = mid; 
            else l = mid; 
        }
        if (row) {
            grid[i][l] = '1'; 
            grid[i][l + 1] = '1'; 
        } else {
            grid[l][i] = '1'; 
            grid[l + 1][i] = '1'; 
        }
        
    } 

    for0(i, n) {
        if (rest.find(i) == rest.end()) continue; 
        for0(j, n - 1) {
            if (row) {
                if (grid[i][j] == '1') {
                    grid[i][j] = '0'; 
                    if (query(grid) != n * n) {
                        grid[i][j] = '1'; 
                        grid[i][j + 1] = '0'; 
                    } 
                    break; 
                }
            } else {
                if (grid[j][i] == '1') {
                    grid[j][i] = '0'; 
                    if (query(grid) != n * n) {
                        grid[j][i] = '1'; 
                        grid[j + 1][i] = '0'; 
                    } 
                    break; 
                }
            }
            
        }
    }
    query(grid, false);
}