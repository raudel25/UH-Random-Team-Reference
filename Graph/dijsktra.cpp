#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define vi vector<int>
#define vii vector<pair<int, int>>

using namespace std;

// begin
int infinite = (int)1e9;

// O(V^2)
vector<int> dijkstra1(int V, vector<vector<int>> adj[], int S)
{
    vector<int> d;

    d.assign(V, infinite);
    d[S] = 0;

    vector<bool> mask;

    mask.assign(V, false);

    for (int i = 0; i < V; i++)
    {
        int m = infinite;
        int act = -1;

        for (int j = 0; j < V; j++)
        {
            if (mask[j])
                continue;

            if (m > d[j])
            {
                m = d[j];
                act = j;
            }
        }

        for (int j = 0; j < adj[act].size(); j++)
        {
            if (d[act] + adj[act][j][1] < d[adj[act][j][0]])
            {
                d[adj[act][j][0]] = d[act] + adj[act][j][1];
            }
        }

        mask[act] = true;
    }

    return d;
}

// O((V+E)log(E))
vi dijkstra2(int V, vii adj[], int S)
{
    vector<int> dist(V, infinite);
    dist[S] = 0;

    priority_queue<pair<int, int>> q;
    q.emplace(0, S);

    while (!q.empty())
    {
        auto [d, u] = q.top();
        q.pop();

        if (d > dist[act])
            continue;

        for (auto &[v, w] : adj[u])
        {
            if (dist[u] + w >= dist[v])
                continue;

            dist[v] = dist[u] + w;
            q.emplace(dist[v], v);
        }
    }

    return dist;
}

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