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

// begin

const int MAXN = 2 * 1e5 + 5;

int n, m;

vi mt;
vi ady[MAXN];
vector<bool> used;
vector<bool> visitedx;
vector<bool> visitedy;

vector<bool> coverx;
vector<bool> covery;

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

void augm_path(int n, bool isX)
{
    if (isX)
        visitedx[n] = true;
    else
        visitedy[n] = true;

    if (!isX)
    {
        if (!visitedx[mt[n]])
            augm_path(mt[n], true);
        return;
    }

    for (auto i : ady[n])
        if (!visitedy[i])
            augm_path(i, false);
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
    for (int v = 1; v <= n; v++)
    {
        used.assign(n + 1, false);
        if (try_kuhn(v))
            max_matching++;
    }

    // vertex cover

    visitedx.assign(n + 1, false);
    visitedy.assign(m + 1, false);

    used.assign(n + 1, false);
    for (int v = 1; v <= m; v++)
        if (mt[v] != -1)
            used[mt[v]] = true;

    for (int v = 1; v <= n; v++)
        if (!used[v] && !visitedx[v])
            augm_path(v, true);

    coverx.assign(n + 1, false);
    covery.assign(m + 1, false);

    for (int v = 1; v <= n; v++)
        if (!visitedx[v])
            coverx[v] = true;

    for (int v = 1; v <= m; v++)
        if (visitedy[v])
            covery[v] = true;

    cout << max_matching << '\n';
    return 0;
}

// end
