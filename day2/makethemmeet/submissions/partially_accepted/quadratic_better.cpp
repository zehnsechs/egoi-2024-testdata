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
typedef vector<ll> vl;
typedef long double ld;

const int MAXN = 201;
int n,m;
vector<vi> C(MAXN, vi());
vector<vi> ANS;

void move_group(vi v){
    // color v the same, color everything else in different colors
    vi in_group(n,0);
    vi col(n,0);
    trav(y, v){
        in_group[y] = 1;
    }
    int c = 2;
    rep(c1,0,n){
        if(in_group[c1]){
            col[c1] = 1;
        }
        else{
            col[c1] = c;
            c++;
        }
    }
    ANS.push_back(col);
}

vi order;
bool mark[MAXN] = {0};

void dfs1(int i){
    if(mark[i])return;
    mark[i] = 1;
    trav(y, C[i]){
        if(!mark[y])dfs1(y);
    }
    order.push_back(i);
}

int label[MAXN] = {0};
int cc = 0;

void dfs2(int i){
    if(label[i] == cc)return;
    label[i] = cc;
    trav(y, C[i]){
        if(label[y] != cc && label[y] != -1){
            move_group({i, y});
            dfs2(y);
            move_group({i, y});
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n >> m;

    rep(c1,0,m){
        int a,b;
        cin >> a >> b;
        C[a].push_back(b);
        C[b].push_back(a);
    }
    dfs1(0);

    rep(c1,0,n){
        cc++;
        dfs2(order[c1]);
        label[order[c1]] = -1;
    }

    cout << sz(ANS) << "\n";
    trav(v, ANS){
        trav(c, v){
            cout << c << " ";
        }cout << "\n";
    }
	
    return 0;
}