#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define int long long
#define vi vector<int>
#define pii pair<int, int>
#define vii vector<pii>

using namespace std;

// begin
const int maxn = 10;

vi adj[maxn];
bool mk[maxn];
int q[maxn], p[maxn], sz[maxn], mc[maxn];

int centroid(int c)
{
    int b = 0, e = 0;
    q[e++] = c, p[c] = -1, sz[c] = 1, mc[c] = 0;

    while (b < e)
    {
        int u = q[b++];
        for (auto v : adj[u])
            if (v != p[u] && !mk[v])
                p[v] = u, sz[v] = 1, mc[v] = 0, q[e++] = v;
    }

    for (int i = e - 1; ~i; --i)
    {
        int u = q[i];
        int bc = max(e - sz[u], mc[u]);
        if (2 * bc <= e)
            return u;
        sz[p[u]] += sz[u], mc[p[u]] = max(mc[p[u]], sz[u]);
    }

    assert(false);
    return -1;
}
// end

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