#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define vi vector<int>

using namespace std;

// begin
vector<bool> visited;
vi t;
vi low;
vector<bool> art;

void dfs_art(vi adj[], int n, int p, int q)
{
    t[n] = q;
    low[n] = q++;
    visited[n] = true;

    int j = 0;

    for (int i = 0; i < adj[n].size(); i++)
    {
        if (!visited[adj[n][i]])
        {
            dfs_art(adj, adj[n][i], n, q);
            low[n] = min(low[adj[n][i]], low[n]);
            j++;

            if (low[adj[n][i]] >= t[n] && p != -1)
            {
                art[n] = true;
            }
        }
        else if (adj[n][i] != p)
        {
            low[n] = min(t[adj[n][i]], low[n]);
        }
    }

    if (p == -1)
    {
        art[n] = j >= 2;
    }
}

void articulationPoints(int V, vi adj[])
{
    visited.assign(V, false);
    t.assign(V, -1);
    low.assign(V, -1);
    art.assign(V, false);

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
        {
            dfs_art(adj, i, -1, 1);
        }
    }
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