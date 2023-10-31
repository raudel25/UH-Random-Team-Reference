#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define vi vector<int>
#define pii pair<int, int>
#define vii vector<pii>

using namespace std;

class SparseTable
{
private:
    vi arr, p2, l2;
    vector<vi> spt;

public:
    SparseTable(int n, int *A)
    {
        arr.assign(A + 1, A + n + 1);
        build_spt();
    }
    SparseTable(vi A)
    {
        arr = A;
        build_spt();
    }
    void build_spt()
    {
        int n = arr.size();
        int L2_n = (int)log2(n) + 1;
        p2.assign(L2_n + 1, 0);
        l2.assign((1 << L2_n) + 1, 0);

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
            for (int j = 0; j + p2[i] - 1 < n; ++j)
            {
                int x = spt[i - 1][j];
                int y = spt[i - 1][j + p2[i - 1]];
                spt[i][j] = arr[x] <= arr[y] ? x : y;
            }
    }
    int rmq(int i, int j)
    {
        if (i > j)
            swap(i, j);
        int k = l2[j - i + 1];
        int x = spt[k][i];
        int y = spt[k][j - p2[k] + 1];
        return arr[x] <= arr[y] ? x : y;
    }
};
int first_ocurr[MAXN], euler_tour[2 * MAXN], depth[MAXN * 2], D[MAXN], idx;
void lca_dfs(int node, int d, int parent = -1)
{
    euler_tour[++idx] = node;
    depth[idx] = d;
    first_ocurr[node] = idx;
    D[node] = d;

    for (auto &nxt : ady[node])
    {
        if (nxt == parent)
            continue;
        lca_dfs(nxt, d + 1, node);
        euler_tour[++idx] = node;
        depth[idx] = d;
    }
}
SparseTable *spt;
void build_lca()
{
    idx = 0;
    lca_dfs(1, 0);
    spt = new SparseTable(idx, depth);
}
int lca_query(int a, int b)
{
    if (depth[a] > depth[b])
        swap(a, b);

    return euler_tour[spt->rmq(first_ocurr[a] - 1, first_ocurr[b] - 1) + 1];
}
int dist(int a, int b)
{
    int lca = lca_query(a, b);

    return D[a] + D[b] - 2 * D[lca];
}
// end

void solve()
{
}

int main()
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