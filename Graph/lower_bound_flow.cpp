#include <bits/stdc++.h>
using namespace std;

// begin

template <typename T>
struct dinic
{
    struct edge
    {
        int src, dst;
        T low, cap, flow;
        int rev;
    };

    int n;
    vector<vector<edge>> adj;

    dinic(int n) : n(n), adj(n + 2) {}

    void add_edge(int src, int dst, T low, T cap)
    {
        adj[src].push_back({src, dst, low, cap, 0, (int)adj[dst].size()});
        if (src == dst)
            adj[src].back().rev++;
        adj[dst].push_back({dst, src, 0, 0, 0, (int)adj[src].size() - 1});
    }

    vector<int> level, iter;

    T augment(int u, int t, T cur)
    {
        if (u == t)
            return cur;
        for (int &i = iter[u]; i < (int)adj[u].size(); ++i)
        {
            edge &e = adj[u][i];
            if (e.cap - e.flow > 0 && level[u] > level[e.dst])
            {
                T f = augment(e.dst, t, min(cur, e.cap - e.flow));
                if (f > 0)
                {
                    e.flow += f;
                    adj[e.dst][e.rev].flow -= f;
                    return f;
                }
            }
        }
        return 0;
    }

    int bfs(int s, int t)
    {
        level.assign(n + 2, n + 2);
        level[t] = 0;
        queue<int> Q;
        for (Q.push(t); !Q.empty(); Q.pop())
        {
            int u = Q.front();
            if (u == s)
                break;
            for (edge &e : adj[u])
            {
                edge &erev = adj[e.dst][e.rev];
                if (erev.cap - erev.flow > 0 && level[e.dst] > level[u] + 1)
                {
                    Q.push(e.dst);
                    level[e.dst] = level[u] + 1;
                }
            }
        }
        return level[s];
    }

    const T oo = numeric_limits<T>::max();

    T max_flow(int source, int sink)
    {
        vector<T> delta(n + 2);

        for (int u = 0; u < n; ++u) // initialize
            for (auto &e : adj[u])
            {
                delta[e.src] -= e.low;
                delta[e.dst] += e.low;
                e.cap -= e.low;
                e.flow = 0;
            }

        T sum = 0;
        int s = n, t = n + 1;

        for (int u = 0; u < n; ++u)
        {
            if (delta[u] > 0)
            {
                add_edge(s, u, 0, delta[u]);
                sum += delta[u];
            }
            else if (delta[u] < 0)
                add_edge(u, t, 0, -delta[u]);
        }

        add_edge(sink, source, 0, oo);
        T flow = 0;

        while (bfs(s, t) < n + 2)
        {
            iter.assign(n + 2, 0);
            for (T f; (f = augment(s, t, oo)) > 0;)
                flow += f;
        }

        if (flow != sum)
            return -1; // no solution

        for (int u = 0; u < n; ++u)
            for (auto &e : adj[u])
            {
                e.cap += e.low;
                e.flow += e.low;
                edge &erev = adj[e.dst][e.rev];
                erev.cap -= e.low;
                erev.flow -= e.low;
            }

        adj[sink].pop_back();
        adj[source].pop_back();

        while (bfs(source, sink) < n + 2)
        {
            iter.assign(n + 2, 0);
            for (T f; (f = augment(source, sink, oo)) > 0;)
                flow += f;
        } // level[u] == n + 2 ==> s-side

        return flow;
    }
};

// end

// Resolvamos el problema de las encuestas con flujo con lower bound
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    // La cantidad de clientes y de productos
    int n, m;
    cin >> n >> m;
    dinic<int> g(2 + n + m);
    int s = n + m;     // el source
    int t = n + m + 1; // el sink

    // los limites de la cantidad de productos encuestados por cliente:
    vector<int> l(n), r(n), L(m), R(m);
    for (int i = 0; i < n; i++)
    {
        cin >> l[i] >> r[i];
    }

    // los limites de la cantidad de clientes encuestados por el mismo producto:
    for (int i = 0; i < m; i++)
    {
        cin >> L[i] >> R[i];
    }

    // el nodo de la red de flujo correspondiente al i-esimo nodo de la primera
    // mitad
    auto primera_mitad = [&](int i)
    {
        return i - 1;
    };

    // el nodo de la red de flujo correspondiente al i-esimo nodo de la segunda
    // mitad
    auto segunda_mitad = [&](int i)
    {
        return i + n - 1;
    };

    for (int u = 1; u <= n; u++)
        for (int v = 1; v <= m; v++)
            g.add_edge(primera_mitad(u), segunda_mitad(v), 0, 1);

    for (int i = 1; i <= n; i++)
        g.add_edge(s, primera_mitad(i), l[i - 1], r[i - 1]);
    for (int i = 1; i <= m; i++)
        g.add_edge(segunda_mitad(i), t, L[i - 1], R[i - 1]);

    // En la funcion max_flow se ve la construccion de la red de flujo sin las
    // cotas inferiores
    int f = g.max_flow(s, t);

    if (f == -1)
    {
        cout << "Imposible satisfacer las condiciones planteadas\n";
        return 0;
    }

    cout << "La mayor cantidad de productos a encuestar es: " << f << "\n";
    cout << "La encuesta de cada cliente seria:\n";
    for (int i = 1; i <= n; i++)
    {
        // chequeamos las aristas que salen de los nodos de la primera mitad
        cout << i << ":";
        for (auto e : g.adj[primera_mitad(i)])
        {
            if (e.dst >= n && e.dst < n + m && e.flow == 1)
            {
                cout << " " << e.dst - n + 1;
            }
        }
        cout << "\n";
    }
}
