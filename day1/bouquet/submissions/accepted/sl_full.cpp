#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto& a : x)
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N;
	cin >> N;

	// lis[k] = min allowed i - L for ans = k
	// sorted in ascending order
	vi lis = {INT_MIN};
	vector<vector<pii>> events(N);

	rep(i,0,N) {
		int L, R;
		cin >> L >> R;
		int lo = 0, hi = sz(lis); // lo ok, hi not ok
		while (lo + 1 < hi) {
			int mid = (lo + hi) / 2;
			if (lis[mid] <= i - L) lo = mid;
			else hi = mid;
		}
		events[min(i + R, N-1)].push_back({lo + 1, i + 1});
		trav(pa, events[i]) {
			int ind = pa.first, val = pa.second;
			if (sz(lis) == ind)
				lis.push_back(val);
			else if (val < lis[ind])
				lis[ind] = val;
		}
	}
	cout << sz(lis) - 1 << endl;
}