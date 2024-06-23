#include <bits/stdc++.h>
#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define forl(i, x, n) for (int i = x; i <= n; i++)
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<ll> vi;
typedef vector<pii> vii;
typedef complex<double> cd;

const int MAXN = 4e5 + 1;
const double PI = acos(-1.0);

cd root[MAXN * 2];
int perm[MAXN * 2];

void preCalc(int sz)
{
    ll hb = -1;
    root[0] = 1;
    double angle = 2 * PI / sz;
    int logBound = 31 - __builtin_clz(sz);
    for (int i = 1; i < sz; i++)
    {
        if ((i & (i - 1)) == 0)
            hb++;
        root[i] = cd(cos(angle * i), sin(angle * i));
        perm[i] = perm[i ^ (1 << hb)] + (1 << (logBound - hb - 1));
    }
}

void fft(vector<cd> &A)
{
    int n = A.size();
    for (ll i = 0; i < n; i++)
    {
        if (i < perm[i])
        {
            swap(A[i], A[perm[i]]);
        }
    }
    for (ll len = 1; len < n; len <<= 1)
    {
        for (ll pos = 0; pos < n; pos += 2 * len)
        {
            for (ll i = 0; i < len; i++)
            {
                cd x = A[pos + i], y = A[pos + i + len] * root[n / len / 2 * i];
                A[pos + i] = x + y;
                A[pos + i + len] = x - y;
            }
        }
    }
}

void multpily(vi &a, vi &b, vi &c)
{
    int maxLog = 0;
    while ((1 << maxLog) < a.size() || (1 << maxLog) < b.size())
        maxLog++;
    maxLog++;
    int n = (1 << maxLog);

    preCalc(n);

    vector<cd> A(a.begin(), a.end());
    vector<cd> B(b.begin(), b.end());

    A.resize(n);
    B.resize(n);

    fft(A);
    fft(B);

    for (int i = 0; i < n; i++)
    {
        A[i] *= B[i];
    }

    fft(A);

    reverse(A.begin() + 1, A.end());

    for (auto &p : A)
    {
        p /= n;
        c.push_back(round(p.real()));
    }

    c.resize(a.size() + b.size() - 1);
}
int t, n;

int f[MAXN];

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
}