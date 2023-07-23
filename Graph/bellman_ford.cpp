#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define vi vector<int>

using namespace std;

// begin
int infinite = (int)1e9;

vector<int> bellman_ford(int V, vector<vector<int>> &edges, int S)
{
    vector<int> d;
    d.assign(V, infinite);
    d[S] = 0;

    for (int i = 0; i < V - 1; i++)
    {
        for (int j = 0; j < edges.size(); j++)
        {
            if (d[edges[j][0]] + edges[j][2] < d[edges[j][1]])
            {
                d[edges[j][1]] = d[edges[j][0]] + edges[j][2];
            }
        }
    }

    for (int j = 0; j < edges.size(); j++)
    {
        if (d[edges[j][0]] + edges[j][2] < d[edges[j][1]])
        {
            vector<int> resp(1);
            resp[0] = -1;

            return resp;
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