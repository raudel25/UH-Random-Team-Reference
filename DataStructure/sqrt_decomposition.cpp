#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// begin

struct sqd {
    int n;
    int b;
    vi a;
    vi bsum;
    sqd(vi &a) {
        n = a.size();
        b = sqrt(n);
        this->a = a;
        bsum.assign(b + 1, 0);
        for (int i = 0; i < n; i++)
            bsum[i / b] += a[i];
    }
    void update(int i, int v) {
        bsum[i / b] += v - a[i];
        a[i] = v;
    }
    int query(int l, int r) {
        int sum = 0;
        for (int i = l; i <= r; i++)
            if (i % b == 0 && i + b - 1 <= r) {
                sum += bsum[i / b];
                i += b - 1;
            } else
                sum += a[i];
        return sum;
    }
};

// end