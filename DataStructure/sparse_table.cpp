#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define int long long
#define vi vector<int>

using namespace std;
class SparseTable {                              // OOP style
private:
  vi A, P2, L2;
  vector<vi> SpT;                                // the Sparse Table
public:
  SparseTable() {}                               // default constructor

  SparseTable(vi &initialA) {                    // pre-processing routine
    A = initialA;
    int n = (int)A.size();
    int L2_n = (int)log2(n)+1;
    P2.assign(L2_n, 0);
    L2.assign(1<<L2_n, 0);
    for (int i = 0; i <= L2_n; ++i) {
      P2[i] = (1<<i);                            // to speed up 2^i
      L2[(1<<i)] = i;                            // to speed up log_2(i)
    }
    for (int i = 2; i < P2[L2_n]; ++i)
      if (L2[i] == 0)
        L2[i] = L2[i-1];                         // to fill in the blanks

    // the initialization phase
    SpT = vector<vi>(L2[n]+1, vi(n));
    for (int j = 0; j < n; ++j)
      SpT[0][j] = j;                             // RMQ of sub array [j..j]

    // the two nested loops below have overall time complexity = O(n log n)
    for (int i = 1; P2[i] <= n; ++i)             // for all i s.t. 2^i <= n
      for (int j = 0; j+P2[i]-1 < n; ++j) {      // for all valid j
        int x = SpT[i-1][j];                     // [j..j+2^(i-1)-1]
        int y = SpT[i-1][j+P2[i-1]];             // [j+2^(i-1)..j+2^i-1]
        SpT[i][j] = A[x] <= A[y] ? x : y;
      }
  }

  int RMQ(int i, int j) {
    int k = L2[j-i+1];                           // 2^k <= (j-i+1)
    int x = SpT[k][i];                           // covers [i..i+2^k-1]
    int y = SpT[k][j-P2[k]+1];                   // covers [j-2^k+1..j]
    return A[x] <= A[y] ? x : y;
  }
};

void solve()
{

    vi a;
    a.push_back(1);
    a.push_back(-1);
    a.push_back(3);
    a.push_back(10);

    auto s = SparseTable(a);

    cout << s.query(1, 3) << "\n";
}

int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        solve();
    }

    return 0;
}
