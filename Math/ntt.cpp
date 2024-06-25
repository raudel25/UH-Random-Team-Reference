#include <bits/stdc++.h>
using namespace std;

// begin
using ll = long long;

const ll mod = (119 << 23) + 1, root = 62; // 998244353

ll qp(ll b, ll e)
{
    ll ans = 1;
    for (; e; b = b * b % mod, e /= 2)
        if (e & 1)
            ans = ans * b % mod;
    return ans;
}

void ntt(vector<ll> &a, vector<ll> &rt, vector<ll> &rev, int n)
{
    for (int i = 0; i < n; i++)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);

    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k)
            for (int j = 0; j < k; j++)
            {
                ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
                a[i + j + k] = (z > ai ? ai - z + mod : ai - z);
                ai += (ai + z >= mod ? z - mod : z);
            }
}

vector<ll> convolve(const vector<ll> &a, const vector<ll> &b)
{
    if (a.empty() || b.empty())
        return {};

    int s = a.size() + b.size() - 1, B = 32 - __builtin_clz(s), n = 1 << B;

    vector<ll> L(a), R(b), out(n), rt(n, 1), rev(n);
    L.resize(n), R.resize(n);

    for (int i = 0; i < n; i++)
        rev[i] = (rev[i / 2] | (i & 1) << B) / 2;

    ll curL = mod / 2, inv = qp(n, mod - 2);
    for (int k = 2; k < n; k *= 2)
    {
        ll z[] = {1, qp(root, curL /= 2)};
        for (int i = k; i < 2 * k; i++)
            rt[i] = rt[i / 2] * z[i & 1] % mod;
    }

    ntt(L, rt, rev, n);
    ntt(R, rt, rev, n);

    for (int i = 0; i < n; i++)
        out[-i & (n - 1)] = L[i] * R[i] % mod * inv % mod;

    ntt(out, rt, rev, n);

    return {out.begin(), out.begin() + s};
}

// end

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cout << "Grado del primer polinomio (n):\n";
    cin >> n;
    cout << "Se esperan a continuación los " << n + 1 << " coeficientes enteros:\n";
    vector<ll> a(n + 1);
    for (int i = 0; i < n + 1; i++)
    {
        cin >> a[i];
    }
    cout << "Grado del segundo polinomio (m):\n";
    cin >> m;
    cout << "Se esperan a continuación los " << m + 1 << " coeficientes enteros:\n";
    vector<ll> b(m + 1);
    for (int i = 0; i < m + 1; i++)
    {
        cin >> b[i];
    }

    cout << "Multiplicación tomando los coeficientes módulo " << mod << ":\n";
    cout.precision(4);
    cout << fixed;
    vector<ll> c = convolve(a, b);
    for (int i = 0; i < n + m + 1; i++)
    {
        if (c[i] == 0)
            continue;
        cout << c[i];
        if (i)
        {
            cout << "x";
            if (i > 1)
            {
                cout << "^" << i;
            }
        }
        if (i + 1 < n + m + 1)
        {
            cout << " + ";
        }
    }
    cout << "\n";
}
