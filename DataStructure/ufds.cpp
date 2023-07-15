#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b

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
// end

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    return 0;
}