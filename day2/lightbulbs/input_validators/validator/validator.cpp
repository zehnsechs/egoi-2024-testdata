#include "validator.h"
#include <bits/stdc++.h>
using namespace std;

void run() {
  int n = Int(3, Arg("maxn"));
  Endl();
  for(int i = 0; i < n; ++i) {
    string line = Line();
    if(size(line) != n)
      die_line("Line " + to_string(i) + " does not have length n");
    if(line.find_first_not_of("vh") != string::npos)
      die_line("Line " + to_string(i) + " has bad character");
  }
  Eof();
}
