#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define vi vector<int>

using namespace std;

// begin
vector<int> topoSort(int V, vector<int> adj[])
{
    vector<int> in(V);
    vector<int> resp;

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < adj[i].size(); j++)
        {
            in[adj[i][j]]++;
        }
    }

    queue<int> q;

    for (int i = 0; i < V; i++)
    {
        if (in[i] == 0)
            q.push(i);
    }

    while (q.size() != 0)
    {
        int n = q.front();
        q.pop();

        for (int i = 0; i < adj[n].size(); i++)
        {
            in[adj[n][i]]--;

            if (in[adj[n][i]] == 0)
                q.push(adj[n][i]);
        }

        resp.push_back(n);
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