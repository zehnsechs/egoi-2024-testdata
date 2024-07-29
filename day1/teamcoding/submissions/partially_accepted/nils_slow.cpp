#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;

// Sorts the vertices decreasingly by min(subtree_size, color_size), then
// runs runs a linear solution for each vertex but breaks if current score
// is higher than min(subtree_size, color_size).

// A very deep tree with many colors and only few vertices for every color
// should be enough. Maybe even a path with colors 1 1 2 2 3 3 ...

const int MAXN = 100001;

int n,k;

vector<vi> C(MAXN, vi());
int SS[MAXN] = {0};
int level[MAXN] = {0};
int score[MAXN] = {0};
int PAR[MAXN] = {0};
vi ind;

int color[MAXN] = {0};
vector<vi> color_list(MAXN, vi());
vector<map<int,int> > CM(MAXN, map<int,int>());

void bfs1(int start){
    vi Q;
    Q.push_back(start);
    PAR[start] = -1;
    int qi = 0;
    while(qi < n){
        int i = Q[qi];
        trav(y, C[i]){
            if(y != PAR[i]){
                level[y] = level[i] + 1;
                PAR[y] = i;
                Q.push_back(y);
            }
        }
        qi++;
    }
    reverse(all(Q));
    trav(i, Q){
        SS[i] = 1;
        trav(y, C[i]){
            if(y != PAR[i]){
                SS[i] += SS[y];
            }
        }
    }
}

pii solve(int i){
    pii res = {1, 0};
    vi same, diff;
    vi Q;
    trav(y, C[i]){
        if(level[y] > level[i]){
            Q.push_back(y);
        }
    }

    while(!Q.empty()){
        int a = Q.back();
        Q.pop_back();
        int d = level[a];
        if(d-level[i] > sz(same)){
            same.push_back(0);
            diff.push_back(0);
        }
        same[d-level[i]-1] += (color[a] == color[i]);
        diff[d-level[i]-1] += (color[a] != color[i]);
        trav(y, C[a]){
            if(level[y] > level[a]){
                Q.push_back(y);
            }
        }
    }

    rep(d2, 0, sz(same)){
        int d = d2 + level[i] + 1;
        int cap = -same[d2];
        if(cap != 0 || CM[color[i]].find(d) != CM[color[i]].end()){
            cap += CM[color[i]][d];
        }
        res.first += same[d2] + min(diff[d2], cap);
        res.second += min(diff[d2], cap);
    }

    res.second *= -1;
    return res;
}

bool comp(int i, int j){
    return score[i] > score[j];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> k;
    rep(c1,0,n){
        cin >> color[c1];
        color_list[color[c1]].push_back(c1);
        ind.push_back(c1);
    }
    rep(c1,0,n-1){
        int a;
        cin >> a;
	int b = c1+1;
        C[a].push_back(b);
        C[b].push_back(a);
    }

    bfs1(0);

    rep(c1,0,k){
        trav(y, color_list[c1]){
            if(CM[c1].find(level[y]) == CM[c1].end()){
                CM[c1][level[y]] = 0;
            }
            CM[c1][level[y]]++;
        }
    }

    rep(c1,0,n){
        score[c1] = min(SS[c1], sz(color_list[color[c1]]));
    }

    sort(all(ind), comp);
    
    pii ans = {-1, -1};
    rep(c1,0,n){
        int i = ind[c1];
        if(score[i] < ans.first)break;
        pii temp = solve(i);
        ans = max(ans, temp);
    }
    
    cout << ans.first << " " << -ans.second << "\n";

    return 0;
}
