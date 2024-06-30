/*
    Kuhn's Algorithm
    Maximum Bipartite Matching
    O(n * m)
    n: number of vertices in the left part
    m: number of vertices in the right part
    mt: mt[i] = j means that vertex i is matched with vertex j
    ady: ady[i] contains all the vertices that vertex i is connected to
    max_matching: maximum number of matchings

    Problem:  https://matcomgrader.com/problem/9759/a-pumpkin-game/

*/

#include <bits/stdc++.h>
#define MAX(a, b) ((a) > (b)) ? (a) : (b)
#define MIN(a, b) ((a) < (b)) ? (a) : (b)
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define forl(i, x, n) for (int i = (x); i <= (int)(n); i++)
#define rforl(i, x, n) for (int i = (x); i >= (int)(n); i--)
#define lsone(x) ((x) & -(x))
#define pb push_back
#define int long long
using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vii;

const int MAXN = 1e3 + 5;


int n, m;

vi mt;
vi ady[MAXN];
vector<bool> used;

bool try_kuhn(int v)
{
    if (used[v])
        return false;
    used[v] = true;
    for (int to : ady[v])
    {
        if (mt[to] == -1 || try_kuhn(mt[to]))
        {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

int32_t main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    forl(i, 1, m)
    {
        int a, b;
        cin >> a >> b;
        ady[a].pb(b);
    }
    int max_matching = 0;

    mt.assign(m + 1, -1);
    int ans = 0;
    forl(v, 1, n)
    {
        used.assign(n + 1, false);
        if (try_kuhn(v))
            max_matching++;
    }

    cout << max_matching << '\n';
    return 0;
}
