#include <bits/stdc++.h>
 
using namespace std;
typedef vector<int> vi;

// begin
 
struct dsu {
    vi p;
    void init(int n) {
        p = vi(n, -1);
    }
    int get(int x) {
        if (p[x] < 0)
            return x;
        return p[x] = get(p[x]);
    }
    void unite(int a, int b) {
        a = get(a);
        b = get(b);
        if (a != b) {
            if (p[a] > p[b])
                swap(a, b);
            p[a] += p[b];
            p[b] = a;
        }
    }
};

// end