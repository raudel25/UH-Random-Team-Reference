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
typedef long long ll;
const int MAXN = 1e5 + 1;

const int p = 131;     // p and M are
const int M = 1e9 + 7; // relatively prime

int Pow[MAXN]; // to store p^i % M
int h[MAXN];   // to store prefix hashes
int n;
char T[MAXN];
int P[MAXN];

void computeRollingHash()
{                               // Overall: O(n)
    Pow[0] = 1;                 // compute p^i % M
    for (int i = 1; i < n; ++i) // O(n)
        Pow[i] = ((ll)Pow[i - 1] * p) % M;
    h[0] = 0;
    for (int i = 0; i < n; ++i)
    { // O(n)
        if (i != 0)
            h[i] = h[i - 1]; // rolling hash
        h[i] = (h[i] + ((ll)T[i] * Pow[i]) % M) % M;
    }
}

int extEuclid(int a, int b, int &x, int &y)
{ // pass x and y by ref
    int xx = y = 0;
    int yy = x = 1;
    while (b)
    { // repeats until b == 0
        int q = a / b;
        tie(a, b) = tuple(b, a % b);
        tie(x, xx) = tuple(xx, x - q * xx);
        tie(y, yy) = tuple(yy, y - q * yy);
    }
    return a; // returns gcd(a, b)
}

int modInverse(int b, int m)
{ // returns b^(-1) (mod m)
    int x, y;
    int d = extEuclid(b, m, x, y); // to get b*x + m*y == d
    if (d != 1)
        return -1; // to indicate failure
    // b*x + m*y == 1, now apply (mod m) to get b*x == 1 (mod m)
    return (x + m) % m; // this is the answer
}

int hash_fast(int l, int r)
{ // O(1) hash of any substr
    if (l == 0)
        return h[r]; // h is the prefix hashes
    int ans = 0;
    ans = ((h[r] - h[l - 1]) % M + M) % M;       // compute differences
    ans = ((ll)ans * modInverse(Pow[l], M)) % M; // remove P[L]^-1 (mod M)
    return ans;
}
// end

int32_t main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    return 0;
}