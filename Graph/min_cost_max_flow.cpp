#include <bits/stdc++.h>
using namespace std;

// begin

template <typename flow_type, typename cost_type> struct min_cost_max_flow {
	struct edge {
		size_t src, dst, rev;
		flow_type flow, cap;
		cost_type cost;
	};

	int n;
	vector<vector<edge>> adj;

	min_cost_max_flow(int n) : n(n), adj(n), potential(n), dist(n), back(n) {}

	void add_edge(size_t src, size_t dst, flow_type cap, cost_type cost) {
		adj[src].push_back({src, dst, adj[dst].size(), 0, cap, cost});
		if (src == dst)
			adj[src].back().rev++;
		adj[dst].push_back({dst, src, adj[src].size() - 1, 0, 0, -cost});
	}

	vector<cost_type> potential;

	inline cost_type rcost(const edge &e) {
		return e.cost + potential[e.src] - potential[e.dst];
	}

	void bellman_ford(int source) {
		for (int k = 0; k < n; ++k)
			for (int u = 0; u < n; ++u)
				for (edge &e : adj[u])
					if (e.cap > 0 && rcost(e) < 0)
						potential[e.dst] += rcost(e);
	}

	const cost_type oo = numeric_limits<cost_type>::max();

	vector<cost_type> dist;
	vector<edge *> back;

	cost_type dijkstra(int source, int sink) {
		fill(dist.begin(), dist.end(), oo);

		typedef pair<cost_type, int> node;
		priority_queue<node, vector<node>, greater<node>> pq;

		for (pq.push({dist[source] = 0, source}); !pq.empty();) {
			node p = pq.top();
			pq.pop();

			if (dist[p.second] < p.first)
				continue;
			if (p.second == sink)
				break;

			for (edge &e : adj[p.second])
				if (e.flow < e.cap && dist[e.dst] > dist[e.src] + rcost(e)) {
					back[e.dst] = &e;
					pq.push({dist[e.dst] = dist[e.src] + rcost(e), e.dst});
				}
		}

		return dist[sink];
	}

	pair<flow_type, cost_type> max_flow(int source, int sink) {
		flow_type flow = 0;
		cost_type cost = 0;

		for (int u = 0; u < n; ++u)
			for (edge &e : adj[u])
				e.flow = 0;

		potential.assign(n, 0);
		dist.assign(n, 0);
		back.assign(n, nullptr);

		bellman_ford(source); // remove negative costs

		while (dijkstra(source, sink) < oo) {
			for (int u = 0; u < n; ++u)
				if (dist[u] < dist[sink])
					potential[u] += dist[u] - dist[sink];

			flow_type f = numeric_limits<flow_type>::max();

			for (edge *e = back[sink]; e; e = back[e->src])
				f = min(f, e->cap - e->flow);
			for (edge *e = back[sink]; e; e = back[e->src])
				e->flow += f, adj[e->dst][e->rev].flow -= f;

			flow += f;
			cost += f * (potential[sink] - potential[source]);
		}
		return {flow, cost};
	}
};

// end

// Resolvamos el problema de matching maximo de costo minimo en un grafo
// bipartito con mcmf
int32_t main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	// Los tamaños de los dos conjuntos de la particion
	int n, m;
	cin >> n >> m;
	min_cost_max_flow<int, double> g(2 + n + m);
	int s = n + m;     // el source
	int t = n + m + 1; // el sink

	// el nodo de la red de flujo correspondiente al i-esimo nodo de la primera
	// mitad
	auto primera_mitad = [&](int i) {
		return i - 1;
	};

	// el nodo de la red de flujo correspondiente al i-esimo nodo de la segunda
	// mitad
	auto segunda_mitad = [&](int i) {
		return i + n - 1;
	};

	// Las aristas
	int e;
	cin >> e;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			// el costo de matchear el nodo de la primera mitad i, con el nodo j
			// de la segunda mitad
			double w_ij;
			cin >> w_ij;
			g.add_edge(primera_mitad(i), segunda_mitad(j), 1, w_ij);
		}
	}
	for (int i = 1; i <= n; i++)
		g.add_edge(s, primera_mitad(i), 1, 0);
	for (int i = 1; i <= m; i++)
		g.add_edge(segunda_mitad(i), t, 1, 0);

	int cardinalidad_matching;
	double costo_minimo;
	tie(cardinalidad_matching, costo_minimo) = g.max_flow(s, t);

	cout << "La cardinalidad del mayor matching es: " << cardinalidad_matching
	     << "\n";
	cout << "Su costo minimo es: " << costo_minimo << "\n";
	cout << "El matching es:\n";
	for (int i = 1; i <= n; i++) {
		// chequeamos las aristas que salen de los nodos de la primera mitad
		for (auto e : g.adj[primera_mitad(i)]) {
			if (e.dst >= n && e.dst < n + m && e.flow == 1) {
				cout << "(" << i << ", " << e.dst - n + 1 << ")\n";
			}
		}
	}
}
