#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define vi vector<int>

using namespace std;
const int MAXN = 2e5;
const int MAXE = 31 - __builtin_clz(MAXN) + 1;

int n = 5;
int A[] = {0, 1, -1, 3, 10, 5};

class SparseTable
{
private:
    vi a, p2, l2;
    vector<vi> spt;

public:
    SparseTable(int n, int *A)
    {
        a.assign(A + 1, A + n + 1);
        build_spt();
    }
    SparseTable(vi A)
    {
        a = A;
        build_spt();
    }
    void build_spt()
    {
        int n = a.size();
        int L2_n = (int)log2(n) + 1;
        p2.assign(L2_n, 0);
        l2.assign(1 << L2_n, 0);

        for (int i = 0; i <= L2_n; ++i)
        {
            p2[i] = (1 << i);
            l2[(1 << i)] = i;
        }
        for (int i = 2; i < p2[L2_n]; ++i)
            if (l2[i] == 0)
                l2[i] = l2[i - 1];

        spt = vector<vi>(l2[n] + 1, vi(n));

        for (int j = 0; j < n; ++j)
            spt[0][j] = j;

        for (int i = 1; p2[i] <= n; ++i)
            for (int j = 1; j + p2[i] - 1 < n; ++j)
            {
                int x = spt[i - 1][j];
                int y = spt[i - 1][j + p2[i - 1]];
                spt[i][j] = A[x] <= A[y] ? x : y;
            }
    }
    int rmq(int i, int j)
    {
        int k = l2[j - i + 1];
        int x = spt[k][i];
        int y = spt[k][j - p2[k] + 1];
        return A[x] <= A[y] ? x : y;
    }
};

int bf(int i, int j)
{

    int idx = -1;
    int mn = INT_MAX;
    for (; i <= j; i++)
    {
        if (mn > A[i])
        {
            mn = A[i];
            idx = i;
        }
    }
    return i;
}

void solve()
{
    SparseTable spt(n, A);
    for (int i = 1; i <= 5; i++)
        for (int j = i; j <= 5; j++)
        {
            int x = spt.rmq(i, j);
            int y = spt.rmq(i, j);
            assert(x == y);
            cout << "Query " << i << " " << j << ": " << A[x] << '\n';
        }
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        solve();
    }

    return 0;
}