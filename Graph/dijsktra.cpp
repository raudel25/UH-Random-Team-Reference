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
    vector<int> d;

    d.assign(V, infinite);
    d[S] = 0;

    priority_queue<pair<int, int>> q;
    q.push({d[S], S});

    while (!q.empty())
    {
        int act = q.top().second;
        int m = abs(q.top().first);
        q.pop();

        if (m > d[act])
            continue;

        for (int j = 0; j < adj[act].size(); j++)
        {
            if (d[act] + adj[act][j].second < d[adj[act][j].first])
            {
                d[adj[act][j].first] = d[act] + adj[act][j].second;
                q.push({-d[adj[act][j].first], adj[act][j].first});
            }
        }
    }

    return d;
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