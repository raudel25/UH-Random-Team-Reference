#include <bits/stdc++.h>
using namespace std;

// begin

using ll = long long;

const int mod = 1e9 + 7;

template <const int _mod_>
struct mod_int
{
    static const int mod = _mod_;
    int val;

    mod_int(long long v = 0)
    {
        if (v < 0)
            v = v % mod + mod;
        if (v >= mod)
            v %= mod;
        val = v;
    }

    static int mod_inv(int a, int m = mod)
    {
        int g = m, r = a, x = 0, y = 1;
        while (r != 0)
        {
            int q = g / r;
            g %= r;
            swap(g, r);
            x -= q * y;
            swap(x, y);
        }
        return x < 0 ? x + m : x;
    }

    explicit operator int() const { return val; }

    mod_int &operator+=(const mod_int &other)
    {
        val += other.val;
        if (val >= mod)
            val -= mod;
        return *this;
    }

    mod_int &operator-=(const mod_int &other)
    {
        val -= other.val;
        if (val < 0)
            val += mod;
        return *this;
    }

    static unsigned fast_mod(uint64_t x, unsigned m = mod)
    {
#if !defined(_WIN32) || defined(_WIN64)
        return x % m;
#endif
        // Optimized mod for Codeforces 32-bit machines.
        // x must be less than 2^32 * m for this to work, so that x / m fits in
        // a 32-bit integer.
        unsigned x_high = x >> 32, x_low = (unsigned)x;
        unsigned quot, rem;
        asm("divl %4\n"
            : "=a"(quot), "=d"(rem)
            : "d"(x_high), "a"(x_low), "r"(m));
        return rem;
    }

    mod_int &operator*=(const mod_int &other)
    {
        val = fast_mod((uint64_t)val * other.val);
        return *this;
    }

    mod_int &operator/=(const mod_int &other) { return *this *= other.inv(); }

    friend mod_int operator+(const mod_int &a, const mod_int &b)
    {
        return mod_int(a) += b;
    }
    friend mod_int operator-(const mod_int &a, const mod_int &b)
    {
        return mod_int(a) -= b;
    }
    friend mod_int operator*(const mod_int &a, const mod_int &b)
    {
        return mod_int(a) *= b;
    }
    friend mod_int operator/(const mod_int &a, const mod_int &b)
    {
        return mod_int(a) /= b;
    }

    mod_int &operator++()
    {
        val = val == mod - 1 ? 0 : val + 1;
        return *this;
    }

    mod_int &operator--()
    {
        val = val == 0 ? mod - 1 : val - 1;
        return *this;
    }

    mod_int operator++(int)
    {
        mod_int a = *this;
        ++*this;
        return a;
    }
    mod_int operator--(int)
    {
        mod_int a = *this;
        --*this;
        return a;
    }
    mod_int operator-() const { return val == 0 ? 0 : mod - val; }
    mod_int inv() const { return mod_inv(val); }

    bool operator==(const mod_int &other) const { return val == other.val; }
    bool operator!=(const mod_int &other) const { return val != other.val; }
    bool operator<(const mod_int &other) const { return val < other.val; }
    bool operator>(const mod_int &other) const { return val > other.val; }

    template <typename T>
    bool operator<(const T &other) const
    {
        return val < other;
    }

    template <typename T>
    bool operator>(const T &other) const
    {
        return val > other;
    }

    friend string to_string(const mod_int &m) { return to_string(m.val); }
    friend mod_int abs(const mod_int &m) { return mod_int(m.val); }

    friend ostream &operator<<(ostream &stream, const mod_int &m)
    {
        return stream << m.val;
    }
    friend istream &operator>>(istream &stream, mod_int &m)
    {
        return stream >> m.val;
    }
};

// Notar que se uso este tipo de datos entero, que implementa todas las
// operaciones basicos en el sistem residual modulo 10^9+7 para hacer mas
// faciles las implementaciones si se quiere implementarlo, se puede dejar en
// long long, y modificar las operaciones para mantener los resultados teneindo
// en cuenta el modulo a usar.
using T = mod_int<mod>;

void HADAMARD_XOR(vector<T> &a, bool inverse = false)
{
    int n = a.size();
    for (int k = 1; k < n; k <<= 1)
    {
        for (int i = 0; i < n; i += 2 * k)
        {
            for (int j = 0; j < k; j++)
            {
                T x = a[i + j];
                T y = a[i + j + k];
                a[i + j] = x + y;
                a[i + j + k] = x - y;
            }
        }
    }

    if (inverse)
    {
        T q = 1 / static_cast<T>(n);

        for (int i = 0; i < n; i++)
        {
            a[i] *= q;
        }
    }
}

void HADAMARD_AND(vector<T> &a, bool inverse = false)
{
    int n = a.size();
    for (int k = 1; k < n; k <<= 1)
    {
        for (int i = 0; i < n; i += 2 * k)
        {
            for (int j = 0; j < k; j++)
            {
                T x = a[i + j];
                T y = a[i + j + k];
                if (inverse)
                {
                    a[i + j] = -x + y;
                    a[i + j + k] = x;
                }
                else
                {
                    a[i + j] = y;
                    a[i + j + k] = x + y;
                }
            }
        }
    }
}

void HADAMARD_OR(vector<T> &a, bool inverse = false)
{
    int n = a.size();
    for (int k = 1; k < n; k <<= 1)
    {
        for (int i = 0; i < n; i += 2 * k)
        {
            for (int j = 0; j < k; j++)
            {
                T x = a[i + j];
                T y = a[i + j + k];
                if (inverse)
                {
                    a[i + j] = y;
                    a[i + j + k] = x - y;
                }
                else
                {
                    a[i + j] = x + y;
                    a[i + j + k] = x;
                }
            }
        }
    }
}

// Las demas operaciones a nivel de bit tienen una implementacion semejante
template <typename T>
vector<T> FWHT_XOR(vector<T> a, vector<T> b)
{
    bool eq = (a == b);
    int n = 1;

    while (n < (int)max(a.size(), b.size()))
    {
        n <<= 1;
    }

    a.resize(n);
    b.resize(n);

    HADAMARD_XOR(a);

    if (eq)
        b = a;
    else
        HADAMARD_XOR(b);

    for (int i = 0; i < n; i++)
    {
        a[i] *= b[i];
    }

    HADAMARD_XOR(a, true);

    return a;
}

// end

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cout << "Grado del primer polinomio (n):\n";
    cin >> n;
    cout << "Se esperan a continuación los " << n + 1
         << " coeficientes enteros:\n";
    vector<T> a(n + 1);
    for (int i = 0; i < n + 1; i++)
    {
        cin >> a[i];
    }
    cout << "Grado del segundo polinomio (m):\n";
    cin >> m;
    cout << "Se esperan a continuación los " << m + 1
         << " coeficientes enteros:\n";
    vector<T> b(m + 1);
    for (int i = 0; i < m + 1; i++)
    {
        cin >> b[i];
    }

    cout << "Multiplicación (cambiando la operacion de suma de exponentes por "
            "otra a nivel de bits) tomando los coeficientes módulo "
         << mod << ":\n";
    cout.precision(4);
    cout << fixed;
    vector<T> c = FWHT_XOR(a, b);
    for (int i = 0; i < c.size(); i++)
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
