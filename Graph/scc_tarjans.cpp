#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define vi vector<int>

using namespace std;

// begin
stack<int> q;
vector<bool> mask;
vector<int> cc_list;

void g_transp(int V, vector<int> adj[], vector<int> new_adj[])
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < adj[i].size(); j++)
        {
            new_adj[adj[i][j]].push_back(i);
        }
    }
}

void dfs_visit(int n, vector<int> adj[], int cc)
{
    mask[n] = true;

    for (int i = 0; i < adj[n].size(); i++)
    {
        if (!mask[adj[n][i]])
            dfs_visit(adj[n][i], adj, cc);
    }

    if (cc == -1)
        q.push(n);
    else
    {
        cc_list[n] = cc;
    }
}

void tarjans(int V, vector<int> adj[])
{
    vector<int> new_adj[V];
    g_transp(V, adj, new_adj);

    mask.assign(V, false);
    cc_list.assign(V, -1);

    for (int i = 0; i < V; i++)
    {
        if (mask[i])
            continue;

        dfs_visit(i, adj, -1);
    }

    for (int i = 0; i < V; i++)
        mask[i] = false;

    int ind = 0;

    while (q.size() != 0)
    {
        int act = q.top();

        q.pop();

        if (!mask[act])
        {
            dfs_visit(act, new_adj, ind);
            ind++;
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