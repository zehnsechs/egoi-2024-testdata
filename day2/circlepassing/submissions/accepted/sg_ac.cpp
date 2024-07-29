#include <bits/stdc++.h>
using namespace std;

int64_t n, m, q;

int64_t dist(int64_t x, int64_t y) {
	x %= (n * 2), y %= (n * 2);
	return min(abs(x - y), 2 * n - abs(x - y));
} 

int main() {
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> m >> q;
	vector<int64_t> k(m); 
	set<int64_t> s;
	for(int i = 0; i < m; ++i) {
		cin >> k[i];
		s.insert(k[i]);
		s.insert(k[i] + n);
	}
	while(q--) {
		int64_t x, y; cin >> x >> y;
		auto it = s.upper_bound(x);
		for(int f = 1; f >= 0 && it != s.begin(); --f) {
			--it;
		}

		int64_t ans = dist(x, y);
		for(int f = 4; f >= 0 && it != s.end(); --f) {
			int64_t ans2 = dist(x, *it) + dist(*it + n, y) + 1;
            int64_t ans3 = dist(x, *s.begin()) + dist(*s.begin() + n, y) + 1;
            int64_t ans4 = dist(x, *--s.end()) + dist(*--s.end() + n, y) + 1;
			ans = min({ans, ans2, ans3, ans4});
			++it;
		}
		cout << ans << "\n";
	}
}
