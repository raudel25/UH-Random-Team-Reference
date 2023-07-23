#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define vi vector<int>

using namespace std;

// begin
void dfs_g(int n, int c, vi adj[], vector<bool> &visited, vi &cc)
{
    visited[n] = true;
    cc[n] = c;

    for (int i = 0; i < adj[n].size(); i++)
    {
        if (!visited[adj[n][i]])
            dfs_g(adj[n][i], c, adj, visited, cc);
    }
}

void dfs_t(int n, int p, int d, vi adj[], vi &deep)
{
    deep[n] = d;

    for (int i = 0; i < adj[n].size(); i++)
    {
        if (p != adj[n][i])
            dfs_t(adj[n][i], n, d + 1, adj, deep);
    }
}

vi bfs(int node, int n, vi adj[])
{
    vi result(n);
    vector<bool> visited;
    visited.assign(n, false);

    queue<int> q;
    visited[node] = true;

    q.push(node);

    while (q.size() != 0)
    {
        int w = q.front();
        q.pop();

        for (int i = 0; i < adj[w].size(); i++)
        {
            if (!visited[adj[w][i]])
            {
                q.push(adj[w][i]);
                result[adj[w][i]] = result[w] + 1;
                visited[adj[w][i]] = true;
            }
        }
    }

    return result;
}
// end

void solve()
{
    int n, m;
    cin >> n >> m;
    vi adj[n];
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vi r = bfs(0, n, adj);
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