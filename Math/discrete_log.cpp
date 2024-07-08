// raudel25
#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b

#define int long long
#define vi vector<int>
#define pii pair<int, int>
#define vii vector<pii>

#define sz(x) (int)(x).size()
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define rall(x) x.rbegin(), x.rend()
#define sor(x) sort(all(x))
#define rsz resize
#define ins insert
#define pb push_back
#define eb emplace_back
#define emp emplace
#define ft front()
#define bk back()
#define f first
#define s second

#define for1(i, a, b) for (int i = ((int)a); i < ((int)b); i++)
#define for2(i, a) for (int i = 0; i < ((int)a); i++)
#define for3(i, a, b, c) for (int i = a; i < ((int)b); i += c)
#define foreach(i, a) for (auto &i : a)
#define print(a)          \
    foreach (i, a)        \
        cout << i << " "; \
    cout << "\n";

#define yes cout << "YES\n";
#define no cout << "NO\n";
#define yes_no(x) cout << ((x) ? ("YES") : ("NO")) << "\n";
#define impossible cout << "IMPOSSIBLE\n";
#define possible cout << "POSSIBLE\n";

using namespace std;

// begin

int powmod(int a, int b, int m)
{
    int res = 1;
    while (b > 0)
    {
        if (b & 1)
        {
            res = (res * 1ll * a) % m;
        }
        a = (a * 1ll * a) % m;
        b >>= 1;
    }
    return res;
}

int discrete_log(int a, int b, int m)
{
    a %= m, b %= m;
    int n = sqrt(m) + 1;
    map<int, int> vals;
    for (int p = 1; p <= n; ++p)
        vals[powmod(a, p * n, m)] = p;
    for (int q = 0; q <= n; ++q)
    {
        int cur = (powmod(a, q, m) * 1ll * b) % m;
        if (vals.count(cur))
        {
            int ans = vals[cur] * n - q;
            return ans;
        }
    }
    return -1;
}

// end

void solve()
{
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin >> t;

    while (t--)
        solve();

    return 0;
}