#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define vi vector<int>

using namespace std;

// begin
int spanningTreePrim(int V, vector<vector<int>> adj[])
{

    priority_queue<pair<int, int>> q;

    vector<bool> mask;
    mask.assign(V, false);
    mask[0] = true;

    int cost = 0;

    for (int i = 0; i < adj[0].size(); i++)
    {
        q.push({-adj[0][i][1], adj[0][i][0]});
    }

    while (q.size() != 0)
    {
        auto aux = q.top();
        q.pop();

        int k = aux.second;
        if (mask[k])
            continue;

        mask[k] = true;
        cost += abs(aux.first);

        for (int i = 0; i < adj[k].size(); i++)
        {
            if (!mask[adj[k][i][0]])
            {
                q.push({-adj[k][i][1], adj[k][i][0]});
            }
        }
    }

    return cost;
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