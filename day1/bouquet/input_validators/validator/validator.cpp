#include "validator.h"
#include<bits/stdc++.h>

using namespace std;

void run() {
    int n = Int(1, Arg("maxn"));
    int mxx = min((int)n, (int) Arg("maxval")); //N is upper bound.
    int all_equal = Arg("all_equal");
    int r0 = Arg("r0");
    Endl();
    set<int> st;
    for(int i = 0; i < n; ++i) {
        int l = Int(0, mxx);
        Space();
        int r = Int(0, mxx);
        assert(r0 != 1 || r == 0);
        Endl();
        st.insert(l);
        st.insert(r);
    }
    assert(st.size() == 1 || all_equal != 1);
}
