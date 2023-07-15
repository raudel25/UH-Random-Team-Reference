#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define int long long
#define vi vector<int>

using namespace std;

// begin
class SparseTable
{

private:
    vector<vi> lookup;

    vi arr;

    int operation(int a, int b)
    {
        if (arr[a] <= arr[b])
            return a;

        return b;
    }

    int simple_node(int i) { return i; }

    void build_sparse_table()
    {
        int n = arr.size();

        for (int i = 0; i < n; i++)
            lookup[i][0] = simple_node(i);

        for (int j = 1; (1 << j) <= n; j++)
        {
            for (int i = 0; i <= n - (1 << j); i++)
                lookup[i][j] = operation(lookup[i][j - 1],
                                         lookup[i + (1 << (j - 1))][j - 1]);
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

        return operation(lookup[l][q], lookup[r - (1 << q) + 1][q]);
    }

    int get(int i) { return arr[i]; }
};
// end

void solve()
{

    vi a;
    a.push_back(1);
    a.push_back(-1);
    a.push_back(3);
    a.push_back(10);

    auto s = SparseTable(a);

    cout << s.query(1, 3) << "\n";
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