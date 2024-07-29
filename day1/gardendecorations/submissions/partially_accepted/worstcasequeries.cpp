// based on sl_3logn.cpp
#include <bits/stdc++.h>
using namespace std;

#define rep(i,f,t) for (int i = f; i < (t); i++)
#define all(x) x.begin(), x.end()
#define trav(a, x) for (auto& a : x)
#define sz(x) (int)(x).size()
typedef vector<int> vi;


vector<vector<vi>> solve_cycle_rec(int n, const vi& cycle, int parity) {
    int cn = sz(cycle);
    if (cn == 1)
        return {};
    assert(cn > 1);
	vector<vi> sc;
	rep(i,0,n) sc.push_back(vi(1, i));
    vector<vector<vi>> sched(3, sc);
    vi ncycle;
	rep(i,0,cn/2) {
        int a = cycle[2*i];
        int b = cycle[2*i+1];
        ncycle.push_back(b);
        if ((a > b) ^ parity)
			swap(a, b);
        sched[0][b] = {a, b};
        sched[1][a] = {a, b};
        sched[2][b] = {a, b};
	}
    if (cn % 2)
        ncycle.push_back(cycle.back());
    auto sched2 = solve_cycle_rec(n, ncycle, parity^1);
	sched.insert(sched.end(), sched2.begin(), sched2.end());
    return sched;
}


vector<vector<vi>> solve_cycle(const vi& cycle) {
    int n = sz(cycle);
	vi co(n);
	rep(i,0,n) assert(cycle[i] >= 0 && cycle[i] < n && !co[cycle[i]]++);
    return solve_cycle_rec(n, cycle, 0);
}


vector<vector<vi>> solve(const vi& perm) {
    int n = sz(perm);
    vi seen(n);
    vector<vector<vi>> total_sched;
    vi inv(n, -1);
	rep(i,0,n) {
		if (seen[i]) continue;
        vi cycle;
        int at = i;
        while (!seen[at]) {
            cycle.push_back(at);
            seen[at] = true;
            at = perm[at];
		}
		vi ren = cycle;
		sort(all(ren));
		rep(j,0,sz(ren))
            inv[ren[j]] = j;
		vi small(sz(ren));
		rep(j,0,sz(ren))
			small[j] = inv[cycle[j]];
        auto subsched = solve_cycle(small);
        while (sz(total_sched) < sz(subsched)) {
			vector<vi> sc;
			rep(i,0,n) sc.push_back({i});
            total_sched.push_back(sc);
		}
		rep(it,0,sz(subsched)) {
			auto& inds = subsched[it];
            auto& tot_inds = total_sched[it];
			rep(j,0,sz(inds)) {
				vi v;
				trav(x, inds[j]) {
					assert(x < sz(ren));
					v.push_back(ren[x]);
				}
                tot_inds[ren[j]] = v;
			}
		}
	}
    return total_sched;
}


void assert_solution_ok2(const vi& perm, const vector<vector<vi>>& schedule, vi vals) {
    int n = sz(perm);
	vi target_vals(n);
	rep(i,0,n) target_vals[i] = vals[perm[i]];
	rep(it,0,sz(schedule)) {
		auto& sched = schedule[it];
		vi nvals(n);
		rep(j,0,sz(sched)) {
			auto& inds = sched[j];
            int x = 0;
			trav(i, inds) {
                if (it % 2 == 0)
                    assert(i <= j);
                else
                    assert(i >= j);
                x ^= vals[i];
			}
            nvals[j] = x;
		}
        vals = nvals;
	}
    assert(vals == target_vals);
}


void assert_solution_ok(const vi& perm, const vector<vector<vi>>& schedule) {
    int n = sz(perm);
	vi vals1(n), vals2(n);
	rep(i,0,n) vals1[i] = i, vals2[i] = rand();
    assert_solution_ok2(perm, schedule, vals1);
    assert_solution_ok2(perm, schedule, vals2);
}


int main() {
    int iteration, n;
	cin >> iteration >> n;
	vi perm(n), co(n);
	rep(i,0,n) {
		cin >> perm[i];
		assert(perm[i] >= 0 && perm[i] < n && !co[perm[i]]++);
	}

    auto schedule = solve(perm);
    while (sz(schedule) < 60) {
		vector<vi> sc;
		rep(i,0,n) sc.push_back({i});
        schedule.push_back(sc);
	}

    if (iteration == 0) {
        assert_solution_ok(perm, schedule);
        cout << sz(schedule) << endl;
		_Exit(0);
	} else {
        iteration--;
        assert(0 <= iteration && iteration < sz(schedule));
        auto& sched = schedule[iteration];
		vi bits(n);
		rep(k,0,n) {
			int j = iteration % 2 == 0 ? k : n-1 - k;
            auto& inds = sched[j];
            cin >> bits[j];
            int x = 0;
			trav(i, inds)
                x ^= bits[i];
			cout << x << endl;
		}
	}
}
