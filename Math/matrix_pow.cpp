#include <bits/stdc++.h>
#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define forl(i, x, n) for (int i = x; i <= n; i++)
#define lsone(x) (x & -x)
using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vii;

const int MAXN = 2;

struct Matrix
{
    ll mat[MAXN][MAXN];
};

Matrix operator*(const Matrix &a, const Matrix &b)
{
    Matrix c;
    for (int i = 0; i < MAXN; ++i)
        for (int j = 0; j < MAXN; ++j)
            c.mat[i][j] = 0;

    for (int i = 0; i < MAXN; i++)
    {
        for (int k = 0; k < MAXN; k++)
        {
            if (a.mat[i][k] == 0)
                continue;
            for (int j = 0; j < MAXN; j++)
            {
                c.mat[i][j] += a.mat[i][k] * b.mat[k][j];
            }
        }
    }
    return c;
}
Matrix operator^(Matrix &base, ll e)
{
    Matrix c;
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            c.mat[i][j] = (i == j);
    while (e)
    {
        if (e & 1ll)
            c = c * base;
        base = base * base;
        e >>= 1;
    }
    return c;
}
int main()
{

    Matrix ans; // Fibonaccci matrix

    ans.mat[0][0] = 1;
    ans.mat[0][1] = 1;
    ans.mat[1][0] = 1;
    ans.mat[1][1] = 0;

    ans = ans ^ 11;
    assert(ans.mat[0][1] == 89);
    return 0;
}
