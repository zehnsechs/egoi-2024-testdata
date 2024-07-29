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

const int MAXN = 100001;
const int SQRT = 100;

int n,k;

vector<vi> C(MAXN, vi());
vector<vi> C2(MAXN, vi());
int SS[MAXN] = {0};
int depth[MAXN] = {0};
int PAR[MAXN] = {0};

int color[MAXN] = {0};
vector<vi> color_list(MAXN, vi());
vector<map<int,int> > on_level(MAXN, map<int,int>());

int f_now[MAXN] = {0};
bool not_optimal[MAXN] = {0};

void dfs1(int i, int par){
    PAR[i] = par;
    SS[i] = 1;
    if(on_level[color[i]].find(depth[i]) == on_level[color[i]].end()){
        on_level[color[i]][depth[i]] = 1;
    }
    else{
        on_level[color[i]][depth[i]]++;
    }
    if(f_now[color[i]] > 0)not_optimal[i] = 1;
    f_now[color[i]]++;
    trav(j, C[i]){
        if(j != par){
            C2[i].push_back(j);
            depth[j] = depth[i]+1;
            dfs1(j,i);
            SS[i] += SS[j];
        }
    }
    f_now[color[i]]--;
}

bool comp(int i, int j){
    return SS[i] < SS[j];
}

pii ans = {0,0};

deque<int> levels;
map<int,int> F;

void merge_into(deque<int> &lvl1, deque<int> &lvl2, map<int,int> &F1, map<int,int> &F2){
    rep(c1,0,sz(lvl1)){
        if(c1 < sz(lvl2)){
            lvl2[c1] += lvl1[c1];
        }
        else{
            lvl2.push_back(lvl1[c1]);
        }
    }
    trav(p, F1){
        if(F2.find(p.first) == F2.end()){
            F2[p.first] = p.second;
        }
        else{
            F2[p.first] += p.second;
        }
    }
}

void dfs2(int i){
    deque<int> levels2;
    map<int,int> F2;

    rep(c1,0,sz(C2[i])-1){
        int j = C2[i][c1];
        dfs2(j);
        merge_into(levels, levels2, F, F2);
    }
    if(sz(C2[i]) > 0){
        dfs2(C2[i].back());
    }
    else{
        levels.clear();
        F.clear();
    }
    merge_into(levels2, levels, F2, F);


    levels.push_front(1);
    if(F.find(color[i]) == F.end())F[color[i]] = 0;
    F[color[i]]++;

    int score = min(SS[i], sz(color_list[color[i]]));


    if(score < ans.first || not_optimal[i] || sz(color_list[color[i]]) >= SQRT)return;

    pii temp = {0,0};
    trav(p, on_level[color[i]]){
        int lvl = p.first;
        int index = lvl-depth[i];
        int x = p.second;
        if(0 <= index && index < sz(levels))temp.first += min(x, levels[index]);
    }
    temp.second = -(temp.first - F[color[i]]);
    ans = max(ans, temp);

}

void solve_heavy(int col){
    vi Q;
    Q.push_back(0);
    vi parents;
    while(sz(Q) > 0){
        int i = Q.back();
        Q.pop_back();
        if(color[i] == col){
            parents.push_back(i);
        }
        else{
            trav(j, C2[i]){
                Q.push_back(j);
            }
        }
    }
    vi LEVEL(n,0);
    trav(p, on_level[col]){
        LEVEL[p.first] = p.second;
    }

    trav(par, parents){
        int tot = 0;
        vi Q2;
        Q2.push_back(par);
        vi level;
        pii temp;
        while(sz(Q2) > 0){
            int i = Q2.back();
            Q2.pop_back();
            if(color[i] == col)tot++;
            int index = depth[i]-depth[par];
            if(index >= sz(level)){
                level.push_back(0);
            }
            level[index]++;
            trav(j, C2[i]){
                Q2.push_back(j);
            }
        }
        rep(c1,0,sz(level)){
            int d = c1+depth[par];
            temp.first += min(level[c1], LEVEL[d]);
        }
        temp.second = -(temp.first - tot);
        ans = max(ans, temp);
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> k;
    rep(c1,0,n){
        cin >> color[c1];
        color_list[color[c1]].push_back(c1);
    }
    rep(c1,0,n-1){
        int a;
        cin >> a;
	    int b = c1+1;
        C[a].push_back(b);
        C[b].push_back(a);
    }

    dfs1(0,-1);
    rep(c1,0,n){
        sort(all(C2[c1]), comp);
    }

    dfs2(0);

    rep(c1,0,k){
        if(sz(color_list[c1]) >= SQRT){
            solve_heavy(c1);
        }
    }

    cout << ans.first << " " << -ans.second << "\n";

    return 0;
}
