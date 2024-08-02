// raudel25
#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b

#define int long long
#define vi vector<int>
#define pii pair<int, int>
#define vii vector<pii>

#define sz(x) (int)(x).size()
#define bg(x) begin(x)
#define all(x) bg(x), end(x)
#define rall(x) x.rbegin(), x.rend()
#define sor(x) sort(all(x))
#define rsz resize
#define ins insert
#define pb push_back
#define eb emplace_back
#define emp emplace
#define ft front()
#define bk back()
#define f first
#define s second

#define for1(i, a, b) for (int i = ((int)a); i < ((int)b); i++)
#define for2(i, a) for (int i = 0; i < ((int)a); i++)
#define for3(i, a, b, c) for (int i = a; i < ((int)b); i += c)
#define foreach(i, a) for (auto &i : a)
#define print(a)          \
    foreach (i, a)        \
        cout << i << " "; \
    cout << "\n";

#define yes cout << "YES\n";
#define no cout << "NO\n";
#define yes_no(x) cout << ((x) ? ("YES") : ("NO")) << "\n";
#define impossible cout << "IMPOSSIBLE\n";
#define possible cout << "POSSIBLE\n";

using namespace std;

// begin

void remove(int idx); // TODO: remove value at idx from data structure
void add(int idx);    // TODO: add value at idx from data structure
int get_answer();     // TODO: extract the current answer of the data structure

int block_size;

struct Query
{
    int l, r, idx;
    bool operator<(Query other) const
    {
        return make_pair(l / block_size, r) <
               make_pair(other.l / block_size, other.r);
    }
};

vector<int> mo_s_algorithm(vector<Query> queries)
{
    vector<int> answers(queries.size());
    sort(queries.begin(), queries.end());

    // TODO: initialize data structure

    int cur_l = 0;
    int cur_r = -1;
    // invariant: data structure will always reflect the range [cur_l, cur_r]
    for (Query q : queries)
    {
        while (cur_l > q.l)
        {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r)
        {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l)
        {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.r)
        {
            remove(cur_r);
            cur_r--;
        }
        answers[q.idx] = get_answer();
    }
    return answers;
}

// end

void solve()
{
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t = 1;
    cin >> t;

    while (t--)
        solve();

    return 0;
}
