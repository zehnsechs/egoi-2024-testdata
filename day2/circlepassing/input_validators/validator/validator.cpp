#include "validator.h"

void run() {
  int n = Int(2, Arg("maxn"));
	Space();
	int m = Int(1, Arg("maxm"));
	Space();
  int q = Int(1, Arg("maxq"));
	Endl();

	if (m > n) die_line("m larger than n");

  string mode = Arg("mode", "");
  if (mode == "g1" && m != 1) die_line("m is supposed to be 1");

	vector<int> f;
  f = SpacedInts(m, 0, n - 1);
  for (int i = 0; i+1 < f.size(); i++) {
    if (f[i] >=  f[i + 1]) die_line("a is not sorted or contains duplicates");
  }

  for (int i = 0; i < q; i++) {
    int x = Int(0, 2 * n - 1);
    Space();
    int y = Int(0, 2 * n - 1);
    if (mode == "x0" && x != 0) die_line("x is supposed to be 0");
    if (mode == "g1" && x != f[0]) die_line("x is supposed to be at bridge");
    if (x == y) die_line("x and y must be different");
    Endl();
  }
  Eof();
}
