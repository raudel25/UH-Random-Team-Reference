#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define vi vector<int>
#define pii pair<int, int>
#define vii vector<pii>

using namespace std;

// begin
class SparseTable
{

private:
    vector<vi> lookup;

    vi arr;

    int rmq(int a, int b)
    {
        if (arr[a] <= arr[b])
            return a;

        return b;
    }

    int operation(int a, int b)
    {
        return rmq(a, b);
    }

    void build_sparse_table()
    {
        int n = arr.size();

        for (int i = 0; i < n; i++)
            lookup[i][0] = i;

        for (int j = 1; (1 << j) <= n; j++)
        {
            for (int i = 0; i <= n - (1 << j); i++)
                lookup[i][j] = operation(lookup[i][j - 1], lookup[i + (1 << (j - 1))][j - 1]);
        }
    }

public:
    SparseTable(vi &a)
    {
        int q = (int)log2(a.size());

        arr.assign(a.size(), 0);
        lookup.assign(a.size(), vi(q + 1));

        for (int i = 0; i < a.size(); i++)
            arr[i] = a[i];

        build_sparse_table();
    }

    int query(int l, int r)
    {
        int q = (int)log2(r - l + 1);

        return operation(lookup[l][q],
                         lookup[r - (1 << q) + 1][q]);
    }

    int get(int i) { return arr[i]; }
};

void dfs(int n, int p, int d, vi adj[], vi &deep, vi &arr)
{
    deep[n] = d;
    arr.push_back(n);

    for (int i = 0; i < adj[n].size(); i++)
    {
        if (p != adj[n][i])
        {
            dfs(adj[n][i], n, d + 1, adj, deep, arr);
            arr.push_back(n);
        }
    }
}

vi lca(int root, int n, vi adj[], vii &querys)
{
    vi deep(n);
    vi first(n);
    vi last(n);
    vi arr;
    vi resp(querys.size());

    dfs(root, -1, 0, adj, deep, arr);

    for (int i = 0; i < arr.size(); i++)
        last[arr[i]] = i;

    for (int i = arr.size() - 1; i >= 0; i--)
        first[arr[i]] = i;

    vi arr_deep(arr.size());

    for (int i = 0; i < arr_deep.size(); i++)
        arr_deep[i] = deep[arr[i]];

    auto s = SparseTable(arr_deep);

    for (int i = 0; i < querys.size(); i++)
    {
        int l = first[querys[i].first];
        int r = last[querys[i].second];

        if (l > r)
        {
            r = last[querys[i].first];
            l = first[querys[i].second];
        }

        int q = s.query(l, r);
        resp[i] = arr[q];
    }

    return resp;
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