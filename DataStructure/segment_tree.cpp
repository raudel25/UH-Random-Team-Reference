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

class SegmentTreeLazy
{
private:
    vi values;
    vector<bool> lazy;
    vi l_values;
    vi p_values;
    int n;

    int left(int p) { return p << 1; };

    int right(int p) { return (p << 1) + 1; }

    int simple_node(int index) { return values[index]; }

    int prop(int x, int y) { return x + y; }

    int prop_lazy(int x, int y) { return x + y; }

    int prop_lazy_up(int x, int y, int s) { return x + y * s; }

    void update_lazy(int p, int l, int r)
    {
        if (l == r)
        {
            values[l] = prop_lazy(values[l], l_values[p]);
        }

        p_values[p] = prop_lazy_up(p_values[p], l_values[p], r - l + 1);
    }

    void propagate_lazy(int p, int l, int r)
    {
        lazy[p] = false;

        if (l == r)
            return;

        l_values[left(p)] = lazy[left(p)]
                                ? prop_lazy(l_values[left(p)], l_values[p])
                                : l_values[p];
        l_values[right(p)] = lazy[right(p)]
                                 ? prop_lazy(l_values[right(p)], l_values[p])
                                 : l_values[p];

        lazy[left(p)] = true;
        lazy[right(p)] = true;
    }

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
        if (lazy[p])
        {
            update_lazy(p, l, r);
            propagate_lazy(p, l, r);
        }

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
        if (lazy[p])
        {
            update_lazy(p, l, r);
            propagate_lazy(p, l, r);
        }

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

    void set_rank(int p, int l, int r, int lq, int rq, int value)
    {
        if (lazy[p])
        {
            update_lazy(p, l, r);
            propagate_lazy(p, l, r);
        }

        if (l > rq || lq > r)
            return;

        if (lq <= l && r <= rq)
        {
            lazy[p] = true;
            l_values[p] = value;
            update_lazy(p, l, r);
            propagate_lazy(p, l, r);
            return;
        }

        set_rank(left(p), l, (l + r) / 2, lq, rq, value);
        set_rank(right(p), (l + r) / 2 + 1, r, lq, rq, value);

        p_values[p] = prop(p_values[left(p)], p_values[right(p)]);
    }

    int get(int p, int l, int r, int i)
    {
        if (lazy[p])
        {
            update_lazy(p, l, r);
            propagate_lazy(p, l, r);
        }

        if (l == r)
            return values[i];

        if (i <= (l + r) / 2)
            return get(left(p), l, (l + r) / 2, i);

        return get(right(p), (l + r) / 2 + 1, r, i);
    }

public:
    SegmentTreeLazy(vi &a)
    {
        values = a;
        n = a.size();
        p_values.assign(4 * n, 0);
        lazy.assign(4 * n, false);
        l_values.assign(4 * n, 0);
        build(1, 0, n - 1);
    }

    int query(int i, int j) { return query(1, 0, n - 1, i, j); }

    void set(int i, int v) { set(1, 0, n - 1, i, v); }

    void set_rank(int i, int j, int v) { set_rank(1, 0, n - 1, i, j, v); }

    int get(int i) { return get(1, 0, n - 1, i); }
};
// end

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    return 0;
}
