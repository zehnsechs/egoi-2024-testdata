#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> x(n), y(n);
    //switch so that higher number = better
    for(int i = n - 1; i >= 0; --i) cin >> x[i];
    for(int i = n - 1; i >= 0; --i) cin >> y[i];
    int64_t ans = 0;
    set<pair<int, int>> s;
    for(int i = n - 1; i >= 0; --i) {
        if(x[i] > 0) s.insert(make_pair(i, x[i]));
    }
    for(int i = n - 1; i >= 0; --i) {
        while(y[i]) {
            auto it = s.upper_bound(make_pair(i, (int)1e9 + 5));
            if(it != s.end()) {
                int match_pos = it->first, cnt = it->second;
                s.erase(it);
                int mn = min(y[i], cnt);
                y[i] -= mn;
                if(match_pos > i) ans += mn;
                else ans -= mn;
                cnt -= mn;
                if(cnt > 0) s.insert(make_pair(match_pos, cnt));
            } else {
                break;
            }
        }
    }
    for(int i = 0; i < n; ++i) {
        while(y[i]) {
            auto it = s.upper_bound(make_pair(i, (int)1e9 + 5));
            if(it != s.end()) {
                int match_pos = it->first, cnt = it->second;
                s.erase(it);
                int mn = min(y[i], cnt);
                y[i] -= mn;
                if(match_pos > i) ans += mn;
                else ans -= mn;
                cnt -= mn;
                if(cnt > 0) s.insert(make_pair(match_pos, cnt));
            } else {
                auto it = s.upper_bound(make_pair(i, (int)1e9 + 5));
                --it;
                int match_pos = it->first, cnt = it->second;
                s.erase(it);
                int mn = min(y[i], cnt);
                y[i] -= mn;
                if(match_pos > i) ans += mn;
                else if(match_pos < i) ans -= mn;
                cnt -= mn;
                if(cnt > 0) s.insert(make_pair(match_pos, cnt));
            }
        }
    }
    cout << ans << "\n";
}
