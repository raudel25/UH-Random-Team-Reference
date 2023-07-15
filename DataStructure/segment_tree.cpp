#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define int long long
#define vi vector<int>
#define pii pair<int, int>
#define vii vector<pii>

using namespace std;

// begin
class SegmentTree
{
private:
    vi values;

    vi p_values;
    int n;

    int left(int p) { return p << 1; };

    int right(int p) { return (p << 1) + 1; }

    int simple_node(int index) { return values[index]; }

    int prop(int x, int y) { return x + y; }

    void build(int p, int l, int r)
    {
        if (l == r)
        {
            p_values[p] = simple_node(l);
            return;
        }

        build(left(p), l, (l + r) / 2);
        build(right(p), (l + r) / 2 + 1, r);

        p_values[p] = prop(p_values[left(p)], p_values[right(p)]);
    }

    void set(int p, int l, int r, int i, int v)
    {
        if (l == r)
        {
            values[l] = v;
            p_values[p] = simple_node(l);
            return;
        }

        if (i <= (l + r) / 2)
            set(left(p), l, (l + r) / 2, i, v);
        else
            set(right(p), (l + r) / 2 + 1, r, i, v);

        p_values[p] = prop(p_values[left(p)], p_values[right(p)]);
    }

    int query(int p, int l, int r, int lq, int rq)
    {
        if (lq <= l && r <= rq)
            return p_values[p];

        int l1 = l, r1 = (l + r) / 2;
        int l2 = (l + r) / 2 + 1, r2 = r;

        if (l1 > rq || lq > r1)
            return query(right(p), l2, r2, lq, rq);
        if (l2 > rq || lq > r2)
            return query(left(p), l1, r1, lq, rq);

        int lt = query(left(p), l1, r1, lq, rq);
        int rt = query(right(p), l2, r2, lq, rq);

        return prop(lt, rt);
    }

public:
    SegmentTree(vi &a)
    {
        values = a;
        n = a.size();
        p_values.assign(4 * n, 0);
        build(1, 0, n - 1);
    }

    int query(int i, int j) { return query(1, 0, n - 1, i, j); }

    void set(int i, int v) { set(1, 0, n - 1, i, v); }

    int get(int i) { return values[i]; }
};
// end

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    return 0;
}
