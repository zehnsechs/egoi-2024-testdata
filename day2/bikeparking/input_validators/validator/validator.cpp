#include "validator.h"
#include <bits/stdc++.h>
using namespace std;

void run() {
    int minn = Arg("minn");
    int maxn = Arg("maxn");
    int maxx = Arg("maxx");
    int maxy = Arg("maxy");
    int maxsumx = Arg("maxsumx");
    int maxsumy = Arg("maxsumy");
    int allequal = Arg("equal");

    int N = Int(minn, maxn);
    Endl();

    int value = -1;
    long long sumx = 0;
    for(int i = 0; i < N; i++){
        if (i) Space();
        int x = Int(0, maxx);
        if (allequal) {
            if (value == -1) value = x;
            if (x != value) die_line("different x");
        }
        sumx += x;
    }
    Endl();

    long long sumy = 0;
    for(int i = 0; i < N; i++){
        if (i) Space();
        int y = Int(0, maxy);
        if (allequal) {
            if (y != value) die_line("different y");
        }
        sumy += y;
    }
    Endl();

    if (sumy > sumx)
        die_line("sumy > sumx");

    if (sumy > maxsumy)
        die_line("sumy > maxsumy");

    if (sumx > maxsumx)
        die_line("sumx > maxsumx");
}
