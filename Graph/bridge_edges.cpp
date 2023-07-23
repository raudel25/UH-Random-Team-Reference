#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define vi vector<int>

using namespace std;

// begin
vector<bool> visited;
vector<int> t;
vector<int> low;
set<pair<int, int>> bridges;

void dfs_bridges(vector<int> adj[], int n, int p, int q)
{
    t[n] = q;
    low[n] = q++;
    visited[n] = true;

    int j = 0;

    for (int i = 0; i < adj[n].size(); i++)
    {
        if (!visited[adj[n][i]])
        {
            dfs_bridges(adj, adj[n][i], n, q);
            low[n] = min(low[adj[n][i]], low[n]);
            j++;
        }
        else if (adj[n][i] != p)
        {
            low[n] = min(t[adj[n][i]], low[n]);
        }
    }

    if (t[n] == low[n] && p != -1)
    {
        bridges.insert({min(n, p), max(n, p)});
    }
}

set<pair<int, int>> bridge_edges(int V, vector<int> adj[])
{
    visited.assign(V, false);
    t.assign(V, -1);
    low.assign(V, -1);
    bridges = set<pair<int, int>>();

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            dfs_bridges(adj, i, -1, 1);
        }
    }

    return bridges;
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