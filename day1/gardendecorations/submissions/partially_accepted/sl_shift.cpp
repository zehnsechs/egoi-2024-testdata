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
	int I;
	cin >> I;
	if (I == 0) {
		cout << 3 << endl;
		return 0;
	}

	int N;
	cin >> N;
	vi perm(N);
	rep(i,0,N) cin >> perm[i];
	vi bits(N);

	int xo = 0, bit, out;
	rep(i,0,N) {
		cin >> bit;
		bits[i] = bit;
		xo ^= bit;
		if (perm[0] == N-1) {
			if (I == 1) {
				if (i == N-1) out = xo;
				else out = bit;
			} else if (I == 2) {
				out = xo;
			} else {
				if (i == 0) out = bit;
				else out = bit ^ bits[i-1];
			}
		} else {
			if (I == 1) {
				out = xo;
			} else if (I == 2) {
				if (i == 0) out = bit;
				else out = bit ^ bits[i-1];
			} else {
				if (i == N-1) out = xo;
				else out = bit;
			}
		}
		cout << out << endl;
	}
}
