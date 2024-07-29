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

    ll n, k; 
    cin >> n >> k; 
    vl col(n); 
    vector<vl> adj(n); 
    vl depth(n);
    vl team(n, -1);  

    pl res = {0, 0}; 
    for0(i, n) {
        cin >> col[i];
        if (col[i] == col[0]) res.first++;
    }

    for0(i, n - 1) {
        ll p; 
        cin >> p; 
        adj[p].push_back(i + 1); 
    }

    queue<ll> q; 
    q.push(0);
    depth[0] = 0;  
    ll t = 0; 
    while (!q.empty()) {
        ll curr = q.front(); 
        q.pop();
        for (ll v : adj[curr]) {
            depth[v] = depth[curr] + 1;
            if (team[curr] == -1 && col[v] != col[0]) team[v] = t++;
            else team[v] = team[curr]; 
            q.push(v); 
        }
    }
    vl numPerLayer(n, 0);
    vector<map<ll, ll>> vPerTeamPerLayer(t);
    vector<map<ll, ll>> vColPerTeamPerLayer(t);
    for0(i, n) {
        if (col[i] != col[0]) {
            numPerLayer[depth[i]]++;
            vColPerTeamPerLayer[team[i]][depth[i]]++;
        }
        if (team[i] != -1) vPerTeamPerLayer[team[i]][depth[i]]++;
    }

    vector<pl> resTeam(t, {0, 0});
    for0(i, t) {
        for (auto [d, k] : vPerTeamPerLayer[i]) {
            resTeam[i].first += min(numPerLayer[d], k);
            resTeam[i].second += min(numPerLayer[d], k) - vColPerTeamPerLayer[i][d];
        }
    } 

    for0(i, t) {
        if (resTeam[i].first > res.first) res = resTeam[i];
        else if (resTeam[i].first == res.first && resTeam[i].second > res.second) res = resTeam[i]; 
    }
    cout << res.first << " " << res.second << endl; 
}