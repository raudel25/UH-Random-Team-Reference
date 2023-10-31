#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define int long long
#define vi vector<int>
#define pii pair<int, int>
#define vii vector<pii>

using namespace std;

// begin
const int MAXN = 2e5 + 5;

vi ady[MAXN];

bitset<MAXN> is_centroid;

int sz[MAXN], ct_par[MAXN];
void centroid_dfs(int node, int parent)
{
    sz[node] = 1;
    for (int &nxt : ady[node])
    {
        if (is_centroid[nxt] || nxt == parent)
            continue;
        centroid_dfs(nxt, node);
        sz[node] += sz[nxt];
    }
}
int get_centroid(int node, int parent, int tree_sz)
{
    for (int nxt : ady[node])
    {
        if (is_centroid[nxt] || nxt == parent)
            continue;
        if (sz[nxt] * 2 > tree_sz)
            return get_centroid(nxt, node, tree_sz);
    }
    return node;
}
void centroid_decomp(int node, int parent = -1)
{
    centroid_dfs(node, -1);
    int tree_sz = sz[node];
    int centroid = get_centroid(node, -1, tree_sz);
    is_centroid[centroid] = 1;
    ct_par[centroid] = parent;

    for (int &child : ady[centroid])
    {
        if (is_centroid[child])
            continue;
        centroid_decomp(child, centroid);
    }
}

void solve()
{
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