#include "validator.h"
#include <bits/stdc++.h>
using namespace std;

void run() {
    int maxn = Arg("maxn");
    int maxq = Arg("maxq");
    int onlyovertake = Arg("onlyovertake",0);

    int N = Int(2, maxn);
    Endl();
    int M = Int(1, maxq);
    Endl();

    for(int i = 0; i < M; i++){
        int x = Int(-(N-1), N-1);
        if(x == 0) die_line("x=0");
        if(onlyovertake && x<0) die_line("got overtaken");
        Endl();
    }
}
