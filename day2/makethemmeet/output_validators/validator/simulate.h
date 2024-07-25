#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

vector<pii> slow_dp(vector<vi> &graph, vector<vi> &color){
    // Output: list of pairs of vertices that can avoid each other
    // Should be empty in a correct solution
    // O(m^2 * sol), so could be O(n^6) in the worst case although with a good constant
    int n = sz(graph);
    int k = sz(color);

    vector<vector<array<char, 2>>> DP(n, vector<array<char, 2>>(n, array<char, 2>{0, 0})); // 1 if they can avoid, 0 if they can't
    vector<vi> graph2 = graph;

    for(int t = k; t >= 0; t--){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                DP[i][j][t%2] = (i != j);
            }
        }
        if(t < k){
            trav(x, graph2) x.clear();
            for(int i = 0; i < n; i++){
                for(int j : graph[i]){
                    if(color[t][i] == color[t][j]){
                        graph2[i].push_back(j);
                    }
                }
                if(sz(graph2[i]) == 0)graph2[i].push_back(i);
            }
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(i == j)continue;
                    if(i > j){
                        DP[i][j][t%2] = DP[j][i][t%2];
                        continue;
                    }
                    DP[i][j][t%2] = 0;
                    for(int i2 : graph2[i]){
                        if(DP[i][j][t%2] == 1)break;
                        for(int j2 : graph2[j]){
                            if(DP[i2][j2][(t+1)%2] == 1 && (i2 != j || j2 != i)){
                                DP[i][j][t%2] = 1;
                            }
                        }
                    }
                }
            }
        }
    }

    vector<pii> ans;
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(DP[i][j][0] == 1)ans.push_back({i, j});
        }
    }

    sort(all(ans));
    return ans;
}

vector<pii> fast_dp(vector<vi> &graph, vector<vi> &color){

    // Similar to slow_dp but makes the transitions sparse by adding an extra flag,
    // making the time complexity O(nm * sol)

    int n = sz(graph);
    int k = sz(color);

    vector<vector<array<char, 2>>> DP(n, vector<array<char, 2>>(n, array<char, 2>{0, 0}));
    vector<vi> graph2 = graph;

    for(int t = k; t >= 0; t--){
        if(t == k){
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    DP[i][j][0] = (i != j);
                }
            }
        }
        else{
            trav(x, graph2) x.clear();
            for(int i = 0; i < n; i++){
                for(int j : graph[i]){
                    if(color[t][i] == color[t][j]){
                        graph2[i].push_back(j);
                    }
                }
                if(sz(graph2[i]) == 0)graph2[i].push_back(i);
            }
            for(int flag = 1; flag >= 0; flag--){

                for(int i = 0; i < n; i++){
                    for(int j = 0; j < n; j++){
                        if(flag == 0 && i > j){
                            DP[i][j][flag] = DP[j][i][flag];
                            continue;
                        }
                        if(i == j){
                            DP[i][j][flag] = 0;
                            continue;
                        }
                        DP[i][j][flag] = 0;

                        if(flag == 1){
                            trav(i2, graph2[i]){
                                if(i2 != j && DP[i2][j][0] == 1){
                                    DP[i][j][1] = 1;
                                    break;
                                }
                            }
                        }
                        else{
                            trav(i2, graph2[i]){
                                if(i2 != j && DP[j][i2][1] == 1){
                                    DP[i][j][0] = 1;
                                    break;
                                }
                            }
                            if(DP[i][j][0] == 0){
                                trav(j2, graph2[j]){
                                    if(j2 != i && DP[i][j2][1] == 1){
                                        DP[i][j][0] = 1;
                                        break;
                                    }
                                }
                            }
                        }
                        
                    }
                }
            }
        }
    }

    vector<pii> ans;
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            if(DP[i][j][0] == 1)ans.push_back({i, j});
        }
    }
    sort(all(ans));
    return ans;
}

const int NLIMBS = 2;

struct Bitset {
    array<uint64_t, NLIMBS> vec;
    Bitset() { reset(); }
    void set() {
        memset(&vec[0], 0xff, sizeof(vec));
    }
    void reset() {
        memset(&vec[0], 0, sizeof(vec));
    }
    inline void set(size_t i, uint64_t bit) {
        uint64_t& limb = vec[i >> 6];
        i &= 63;
        limb &= ~((uint64_t)1 << i);
        limb |= bit << i;
    }
    int get(size_t i) const {
        uint64_t limb = vec[i >> 6];
        i &= 63;
        return (limb >> i) & 1;
    }
    void operator|=(const Bitset& other) {
        for (size_t i = 0; i < NLIMBS; i++)
            vec[i] |= other.vec[i];
    }
    bool operator==(const Bitset& other) const {
        return vec == other.vec;
    }
};

void transpose_slow(vector<Bitset>& out, const vector<Bitset>& in, int n) {
    rep(i,0,n) rep(j,0,n)
        out[i].set(j, in[j].get(i));
}

#ifdef __x86_64__
// https://mischasan.wordpress.com/2011/10/03/the-full-sse2-bit-matrix-transpose-routine/
// GPL licensed (we're not distributing this as a binary, so it's fine)
#include <emmintrin.h>

inline void sse_trans(uint8_t const *inp, uint8_t *out, int nrows, int ncols) {
    for (int rr = 0; rr <= nrows - 16; rr += 16) {
        for (int cc = 0; cc < ncols; cc += 8) {
            union { __m128i x; uint8_t b[16]; } tmp;
            for (int i = 0; i < 16; ++i)
                tmp.b[i] = inp[ncols/8 * (rr + i) + cc/8];
            for (int i = 8; --i >= 0; tmp.x = _mm_slli_epi64(tmp.x, 1))
                *(uint16_t*)&out[nrows/8 * (cc+i) + rr/8] = (uint16_t)_mm_movemask_epi8(tmp.x);
        }
    }
}

void transpose(vector<Bitset>& out, const vector<Bitset>& in, int n) {
    sse_trans((const uint8_t*)in.data(), (uint8_t*)out.data(), NLIMBS * 64, NLIMBS * 64);
}

#else
// Not actually that slow, just 25% overall perf loss or so in the worst case
void transpose(vector<Bitset>& out, const vector<Bitset>& in, int n) {
    transpose_slow(out, in, n);
}
#endif

void test_transpose() {
    int n = NLIMBS * 64;
    vector<Bitset> a(n);
    vector<Bitset> b(n);
    vector<Bitset> c(n);
    rep(i,0,n) rep(j,0,n) a[i].set(j, (rand() >> 5) % 2);
    transpose(b, a, n);
    transpose_slow(c, b, n);
    assert(a == c);
}

vector<pii> faster_dp(vector<vi> &graph, vector<vi> &color) {
    // Bitset version of fast_dp

    int n = sz(graph);
    int k = sz(color);
    assert(n <= NLIMBS * 64);

    vector<Bitset> DP0(NLIMBS * 64);
    vector<Bitset> DP1(NLIMBS * 64);
    vector<Bitset> DP0tr(NLIMBS * 64);
    vector<Bitset> DP1tr(NLIMBS * 64);
    vector<vi> graph2 = graph;

    // This has no business being static, but placing it on the stack makes
    // GCC aware of its alignment, and then it tries to be smart with SIMD
    // which interferes with store forwarding or something, causing a 2x perf
    // penalty on AMD.
    static Bitset v;

    for (int t = k; t >= 0; t--) {
        if (t == k) {
            rep(i,0,n) {
                DP0[i].set();
            }
            rep(i,0,n) {
                DP0[i].set(i, 0);
            }
        } else {
            trav(x, graph2) x.clear();
            rep(i,0,n) {
                for (int j : graph[i]) {
                    if (color[t][i] == color[t][j]) {
                        graph2[i].push_back(j);
                    }
                }
                if (graph2[i].empty()) graph2[i].push_back(i);
            }

            {
                // flag = 1
                rep(i,0,n) {
                    DP1[i].reset();
                }
                rep(i,0,n) trav(i2, graph2[i]) {
                    v = DP0[i2];
                    v.set(i2, 0);
                    v.set(i, 0);
                    DP1[i] |= v;
                }

                // flag = 0
                rep(i,0,n) {
                    DP0tr[i].reset();
                }

                transpose(DP1tr, DP1, n);

                rep(j,0,n) trav(j2, graph2[j]) {
                    v = DP1tr[j2];
                    v.set(j2, 0);
                    DP0tr[j] |= v;
                }

                transpose(DP0, DP0tr, n);

                rep(i,0,n) trav(i2, graph2[i]) {
                    v = DP1tr[i2];
                    v.set(i2, 0);
                    v.set(i, 0);
                    DP0[i] |= v;
                }
            }
        }
    }

    vector<pii> ans;
    rep(i,0,n) rep(j,i+1,n) {
        if (DP0[i].get(j)) ans.push_back({i, j});
    }
    sort(all(ans));
    return ans;
}
