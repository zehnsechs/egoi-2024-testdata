#include "validate.h"

#include <bits/stdc++.h>
using namespace std;

const int MAX_QUERIES = 2'000;

string readline() {
	string s;
	while (cin) {
		getline(cin, s);
		s.erase(remove(s.begin(), s.end(), ' '), s.end());
		if (!s.empty()) return s;
	}
	return "";
}

int main(int argc, char **argv) {
  init_io(argc, argv);

  int N;
  judge_in >> N;
  vector<string> grid(N);
  for(int i = 0; i < N; ++i)
    judge_in >> grid[i];

  cout << N << endl;

  int queries = 0;

  auto read_matrix = [&](const string &msg) {
    vector<int> verticals(N, 0), horizontals(N, 0);
    int turned_on = 0;
    for(int i = 0; i < N; ++i) {
      string s = readline();
      if(!cin)
        wrong_answer("%s unexpected eof2", msg.c_str());
      if(size(s) != (size_t)N)
        wrong_answer("%s wrong length (got: %d; expected %d)", msg.c_str(), (int)size(s), N);

      for(int j = 0; j < N; ++j) {
        if(s[j] == '1') {
          ++turned_on;
          if (grid[i][j] == 'v') verticals[j] = 1;
          else if (grid[i][j] == 'h') horizontals[i] = 1;
          else judge_error("input grid is bad");
        }
        else if (s[j] != '0') {
          wrong_answer("%s unexpected character (got: \"%c\")", msg.c_str(), s[j]);
        }
      }
    }
    int v = count(begin(verticals), end(verticals), 1);
    int h = count(begin(horizontals), end(horizontals), 1);
    return make_tuple(turned_on, N * (v + h) - v * h);
  };

  for (;;) {
	  string type;
	  cin >> type;
    if(!cin)
      wrong_answer("unexpected eof1");
    if(type == "!") {
      auto [k, cover] = read_matrix("[answer]");
      if (cover < N * N)
        wrong_answer("wa: does not cover enough");
      if (cover > N * N)
        judge_error("covers too much? impossible");
      if (k > N)
        wrong_answer("wa: uses too many lamps: %d > N (=%d)", k, N);
      if (k < N)
        judge_error("too few lamps? impossible");
      break;
    }
    else if(type == "?") {
      ++queries;
      if (queries > MAX_QUERIES)
        wrong_answer("too many queries");
      auto [k, cover] = read_matrix("[query " + to_string(queries) + "]");
      cout << cover << endl;
    }
    else{
      wrong_answer("[query %d] bad query type (char: \'%c\'; ascii: %d)",
                   queries, type[0], (int)type[0]);
    }
  }

  string garbage;
  cin >> garbage;
  if(cin) wrong_answer("trailing output, expected eof");

  judge_message("used %d queries", queries);
  accept_with_score(queries);
}
