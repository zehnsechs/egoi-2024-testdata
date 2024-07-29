#include <bits/stdc++.h>
using namespace std;

int64_t n, m, q, k0;

int64_t dist(int64_t x, int64_t y) {
	return min(abs(x - y), 2 * n - abs(x - y));
} 

int main() {
	cin >> n >> m >> q >> k0;
	while(q--) {
		int64_t x, y; cin >> x >> y;
		cout << min(dist(x, y), dist(x + n, y) + 1) << "\n";
	}
}
