#include "validate.h"
#include "simulate.h"

#include <bits/stdc++.h>
using namespace std;

const int MAX_MOVES = 20000;

const double FULL_SCORE = 600;
const double BASE_SCORE = 0.17;

int main(int argc, char **argv) {
  init_io(argc, argv);
  bool sample = 0;
  for (int i = 4; i < argc; i++) {
    if (string(argv[i]) == "sample") sample = 1;
  }

  int n,m;
  judge_in >> n >> m;
  vector<vi> graph(n, vi());

  for(int c1 = 0; c1 < m; c1++){
    int a,b;
    judge_in >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  int moves;
  if(!(author_out >> moves)){
    wrong_answer("Could not read number of moves");
  }

  if(moves < 0 || moves > MAX_MOVES){
    wrong_answer("Number of moves out of bounds");
  }

  vector<vi> color;
  for(int t = 0; t < moves; t++){
    vi row;
    for(int c1 = 0; c1 < n; c1++){
      int c;
      if(!(author_out >> c)){
        wrong_answer("Could not read color");
      }
      if(c < 0 || c > n){
        wrong_answer("Color out of bounds %d", c);
      }
      row.push_back(c);
    }
    color.push_back(row);
  }

  vector<pii> avoid = faster_dp(graph, color);
  if(sz(avoid) != 0){
    int x = avoid[0].first;
    int y = avoid[0].second;
    wrong_answer("If people start at %d and %d, then they can avoid each other", x, y);
  }

  string garbage;
  author_out >> garbage;
  if (author_out)
    wrong_answer("trailing output, expected eof");


  //double B = (MAX_MOVES * BASE_SCORE - FULL_SCORE) / (1.0 - BASE_SCORE);
  //double A = FULL_SCORE + B;

  double A = 2000.0;
  double B = 1900.0;
  double C = 5.0;

  double score = min(1.0, A / (double(moves) + B) + 1.0 / C);
  score = max(score, 0.0);
  score *= 1000;

  if (sample) score = 0;
  //score = 100000-moves;
  //score = moves;

  accept_with_score(score);
}
