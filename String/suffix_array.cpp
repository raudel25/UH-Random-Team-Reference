#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define int long long
#define vi vector<int>
#define pii pair<int, int>
#define vii vector<pii>

using namespace std;

// begin
class SuffixArray
{

public:
    SuffixArray(string s)
    {
        n = s.size() + 1;
        s_value = s + "$";

        ra.assign(n, 0);
        sa.assign(n, 0);
        temp_ra.assign(n, 0);
        temp_sa.assign(n, 0);

        construct_sa();
        build_lcp();
    }

    int size() { return n; }

    int get_int(int i) { return sa[i]; }

    int cant_match(string p)
    {
        pii ans = matching(p);

        if (ans.first == -1 && ans.second == -1)
            return 0;

        return ans.second - ans.first + 1;
    }

    int get_lcp(int i) { return plcp[sa[i]]; }

    int cant_substr() { return v_cant_substr; }

    string get_str(int i) { return s_value.substr(sa[i], n - sa[i] - 1); }

private:
    string s_value;
    int n;
    int v_cant_substr;

    vi ra;
    vi sa;
    vi c;
    vi temp_ra;
    vi temp_sa;
    vi phi;
    vi plcp;

    void counting_sort(int k)
    {
        int sum = 0;
        int maxi = max((int)300, n);

        c.assign(maxi, 0);

        for (int i = 0; i < n; i++)
            c[i + k < n ? ra[i + k] : 0]++;

        for (int i = 0; i < maxi; i++)
        {
            int tx = c[i];
            c[i] = sum;
            sum += tx;
        }

        for (int i = 0; i < n; i++)
            temp_sa[c[sa[i] + k < n ? ra[sa[i] + k] : 0]++] = sa[i];

        for (int i = 0; i < n; i++)
            sa[i] = temp_sa[i];
    }

    void construct_sa()
    {
        int k, r;

        for (int i = 0; i < n; i++)
        {
            ra[i] = s_value[i];
            sa[i] = i;
        }

        for (k = 1; k < n; k <<= 1)
        {
            counting_sort(k);
            counting_sort(0);

            temp_ra[sa[0]] = r = 0;

            for (int i = 1; i < n; i++)
                temp_ra[sa[i]] = (ra[sa[i]] == ra[sa[i - 1]] && ra[sa[i] + k] == ra[sa[i - 1] + k]) ? r : ++r;

            for (int i = 0; i < n; i++)
                ra[i] = temp_ra[i];

            if (ra[sa[n - 1]] == n - 1)
                break;
        }
    }

    pii matching(string p)
    {
        int l = 0;
        int r = n - 1;
        int p_size = p.size();

        string comp;

        while (l < r)
        {
            int m = (l + r) / 2;

            comp = s_value.substr(sa[m], min(n - sa[m], p_size));

            if (comp >= p)
                r = m;
            else
                l = m + 1;
        }

        comp = s_value.substr(sa[l], min(n - sa[l], p_size));

        if (comp != p)
            return {-1, -1};

        int ans_l = l;

        l = 0;
        r = n - 1;

        while (l < r)
        {
            int m = (l + r) / 2;

            comp = s_value.substr(sa[m], min(n - sa[m], p_size));

            if (comp > p)
                r = m;
            else
                l = m + 1;
        }

        comp = s_value.substr(sa[r], min(n - sa[r], p_size));

        if (comp != p)
            r--;

        int ans_r = r;

        return {ans_l, ans_r};
    }

    void build_lcp()
    {
        phi.assign(n, 0);
        plcp.assign(n, 0);

        phi[0] = -1;

        for (int i = 1; i < n; i++)
            phi[sa[i]] = sa[i - 1];

        int l = 0;
        int q = 0;
        for (int i = 0; i < n; i++)
        {
            if (phi[i] == -1)
            {
                plcp[i] = 0;
                continue;
            }

            while (s_value[i + l] == s_value[phi[i] + l])
                l++;

            plcp[i] = l;
            q += l;
            l = max(l - 1, (int)0);
        }

        v_cant_substr = n * (n - 1) / 2 - q;
    }
};
// end;

void solve()
{
    string s;
    cin >> s;

    SuffixArray suffix(s);
    int n = s.size();

    cout << suffix.cant_substr() << "\n";
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    solve();

    return 0;
}