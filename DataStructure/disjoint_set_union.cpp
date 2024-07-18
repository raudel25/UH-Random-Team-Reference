#include <bits/stdc++.h>

using namespace std;
typedef vector<int> vi;

// begin

struct dsu
{
    vi p, rank, sz;
    int num_sets;
    dsu(int n)
    {
        p.assign(n + 1, 0);
        iota(p.begin(), p.end(), 0);
        rank.assign(n + 1, 0);
        sz.assign(n + 1, 1);
        num_sets = n;
    }
    int get(int x)
    {
        if (p[x] < 0)
            return x;
        return p[x] = get(p[x]);
    }
    bool is_same_set(int a, int b) { return get(a) == get(b); }
    int size_of(int a) { return sz[get(a)]; }
    void unite(int a, int b)
    {
        a = get(a);
        b = get(b);
        if (rank[a] > rank[b])
            swap(a, b);
        p[a] = b;
        if (rank[a] == rank[b])
            rank[b]++;
        sz[b] += sz[a];
        num_sets--;
    }
};

// end