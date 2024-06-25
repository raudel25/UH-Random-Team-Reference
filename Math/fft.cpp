#include <bits/stdc++.h>
using namespace std;

// begin
struct point
{
    double x, y;
    point(double x = 0, double y = 0) : x(x), y(y) {}
};

point operator+(const point &a, const point &b)
{
    return {a.x + b.x, a.y + b.y};
}
point operator-(const point &a, const point &b)
{
    return {a.x - b.x, a.y - b.y};
}
point operator*(const point &a, const point &b)
{
    return {a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x};
}
point operator/(const point &a, double d) { return {a.x / d, a.y / d}; }

void fft(vector<point> &a, int sign = 1)
{
    int n = a.size(); // n should be a power of two
    double theta = 8 * sign * atan(1.0) / n;
    for (int i = 0, j = 1; j < n - 1; ++j)
    {
        for (int k = n >> 1; k > (i ^= k); k >>= 1)
            ;
        if (j < i)
            swap(a[i], a[j]);
    }
    for (int m, mh = 1; (m = mh << 1) <= n; mh = m)
    {
        int irev = 0;
        for (int i = 0; i < n; i += m)
        {
            point w = point(cos(theta * irev), sin(theta * irev));
            for (int k = n >> 2; k > (irev ^= k); k >>= 1)
                ;
            for (int j = i; j < mh + i; ++j)
            {
                int k = j + mh;
                point x = a[j] - a[k];
                a[j] = a[j] + a[k];
                a[k] = w * x;
            }
        }
    }
    if (sign == -1)
        for (auto &p : a)
            p = p / n;
}

vector<point> convolve(vector<point> &a, vector<point> &b)
{
    int n = a.size();
    int m = b.size();
    int k = n + m;
    while (k != (k & -k))
        k += (k & -k);
    while (a.size() < k)
        a.push_back(point(0, 0));
    while (b.size() < k)
        b.push_back(point(0, 0));

    fft(a, 1);
    fft(b, 1);

    vector<point> c(k);
    for (int i = 0; i < k; i++)
        c[i] = a[i] * b[i];

    fft(c, -1);

    return c;
}

// end

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cout << "Grado del primer polinomio (n):\n";
    cin >> n;
    cout << "Se esperan a continuación los " << n + 1 << " coeficientes:\n";
    vector<point> a(n + 1);
    for (int i = 0; i < n + 1; i++)
    {
        double x;
        cin >> x;
        a[i] = point(x, 0);
    }
    cout << "Grado del segundo polinomio (m):\n";
    cin >> m;
    cout << "Se esperan a continuación los " << m + 1 << " coeficientes:\n";
    vector<point> b(m + 1);
    for (int i = 0; i < m + 1; i++)
    {
        double x;
        cin >> x;
        b[i] = point(x, 0);
    }

    cout << "Multiplicación:\n";
    cout.precision(4);
    cout << fixed;
    vector<point> c = convolve(a, b);
    for (int i = 0; i < n + m + 1; i++)
    {
        if (abs(c[i].x) < 1e-4)
            continue;
        cout << c[i].x;
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
