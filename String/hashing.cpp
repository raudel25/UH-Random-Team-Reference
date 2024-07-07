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
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

const int MAXN = 5e5 + 5;
const int MOD = 1e9 + 7;
int mod_pow(int b, int e)
{
    int res = 1;
    while (e)
    {
        if (e & 1)
            res = res * b % MOD;
        b = b * b % MOD;
        e >>= 1;
    }
    return res % MOD;
}

typedef unordered_map<ll, ll, custom_hash> safe_map;

int dx[] = {1, 0, -1, 0, 1, -1, -1, 1};
int dy[] = {0, 1, 0, -1, 1, 1, -1, -1};

int dp[MAXN];
vi ady_list[MAXN];

int n, m, t, k;
int f[MAXN];
int comb(int n, int k)
{
    int fk = mod_pow(f[k], MOD - 2);
    int fnk = mod_pow(f[n - k], MOD - 2);
    int x = ((f[n] * fk) % MOD * fnk % MOD);

    return x;
}

// end

int32_t main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    f[0] = f[1] = 1;
    forl(i, 2, MAXN - 1) f[i] = f[i - 1] * i % MOD;
    cin >> n;
    dp[1] = 1;
    forl(i, 2, n)
    {
        forl(j, 1, i - 1)
        {
            int s = comb(i, j);
            int z = ((s * dp[j] % MOD) * dp[i - j]);
            // if (j == i - j)
            // z = z * mod_pow(2, MOD - 2);
            dp[i] += z % MOD;
            dp[i] %= MOD;
        }
    }
    cout << dp[n];
    return 0;
}