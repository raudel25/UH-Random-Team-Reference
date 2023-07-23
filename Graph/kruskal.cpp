#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define vi vector<int>

using namespace std;

// begin
class ufds
{
private:
    vector<int> p, rank, sizeSet;
    int disjoinSet;

public:
    ufds(int n)
    {
        p.assign(n, 0);
        rank.assign(n, 0);
        sizeSet.assign(n, 1);
        disjoinSet = n;
        for (int i = 0; i < n; i++)
        {
            p[i] = i;
        }
    }

    int find(int n)
    {
        if (n == p[n])
            return n;
        p[n] = find(p[n]);
        return p[n];
    }

    bool isSameSet(int i, int j) { return find(i) == find(j); }

    void unionSet(int i, int j)
    {
        if (!isSameSet(i, j))
        {
            disjoinSet--;
            int x = find(i);
            int y = find(j);
            if (rank[x] > rank[y])
            {
                p[y] = x;
                sizeSet[x] += sizeSet[y];
            }
            else
            {
                p[x] = y;
                sizeSet[y] += sizeSet[x];
                if (rank[x] == rank[y])
                    rank[y]++;
            }
        }
    }

    int numDisjoinset() { return disjoinSet; }

    int sizeofSet(int i) { return sizeSet[find(i)]; }
};

// Function to find sum of weights of edges of the Minimum Spanning Tree.
int spanningTreeKruskal(int V, vector<vector<int>> adj[])
{
    ufds dsu(V);

    vector<pair<int, pair<int, int>>> a;

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < adj[i].size(); j++)
        {
            a.push_back({adj[i][j][1], {i, adj[i][j][0]}});
        }
    }

    sort(a.begin(), a.end());

    int cost = 0;

    for (int i = 0; i < a.size(); i++)
    {
        if (!dsu.isSameSet(a[i].second.first, a[i].second.second))
        {
            cost += a[i].first;

            dsu.unionSet(a[i].second.first, a[i].second.second);
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