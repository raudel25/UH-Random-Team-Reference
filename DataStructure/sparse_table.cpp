#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define vi vector<int>

using namespace std;
const int MAXN = 2e5;
const int MAXE = 31 - __builtin_clz(MAXN) + 1;

int p2[MAXN], l2[MAXN], n = 5;
int spt[MAXE][MAXN];
int A[] = {0, 1, -1, 3, 10, 5};

void build_spt()
{

    int L2_n = (int)log2(n) + 1;
    for (int i = 0; i <= L2_n; ++i)
    {
        p2[i] = (1 << i);
        l2[(1 << i)] = i;
    }
    for (int i = 2; i < p2[L2_n]; ++i)
        if (l2[i] == 0)
            l2[i] = l2[i - 1];

    for (int j = 1; j <= n; ++j)
        spt[0][j] = j;

    for (int i = 1; p2[i] <= n; ++i)
        for (int j = 1; j + p2[i] - 1 <= n; ++j)
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
    build_spt();
    for (int i = 1; i <= 5; i++)
        for (int j = i; j <= 5; j++)
        {
            int x = rmq(i, j);
            int y = rmq(i, j);
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