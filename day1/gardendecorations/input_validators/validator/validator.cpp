#include "validator.h"
#include <bits/stdc++.h>
using namespace std;

void run() {
	int n = Int(2, Arg("n"));
	Endl();
	vector<int> order = SpacedInts(n, 0, n-1);
	vector<int> values = SpacedInts(n, 0, 1);

	auto order2 = order;
	sort(order2.begin(), order2.end());
	for (int i = 0; i < n; i++)
		assert(order2[i] == i);

	string mode = Arg("mode");
	if (mode == "rev") {
		for (int i = 0; i < n; i++)
			assert(order[i] == n-1 - i);
	} else if (mode == "rot") {
		for (int i = 0; i < n; i++)
			assert(order[i] == (i + 1) % n);
	} else if (mode == "tor") {
		for (int i = 0; i < n; i++)
			assert(order[i] == (i - 1 + n) % n);
	} else {
		assert(mode == "general");
	}
}
