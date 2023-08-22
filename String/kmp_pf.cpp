#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define ll long long
#define vi vector<int>
#define vll vector<long long>

using namespace std;

// begin
vi prefix_function(string p)
{
    vi pf(p.size());

    pf[0] = 0;
    int k = 0;

    for (int i = 1; i < p.size(); i++)
    {
        while (k > 0 && p[k] != p[i])
            k = pf[k - 1];

        if (p[k] == p[i])
            k++;

        pf[i] = k;
    }

    return pf;
}

vi kmp(string t, string p)
{
    vi result;
    vi pf = prefix_function(p);
    int k = 0;

    for (int i = 0; i < t.size(); i++)
    {
        while (k > 0 && p[k] != t[i])
            k = pf[k - 1];

        if (p[k] == t[i])
            k++;

        if (k == p.size())
        {
            result.push_back(i - (p.size() - 1));
            k = pf[k - 1];
        }
    }

    return result;
}
// end

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    return 0;
}