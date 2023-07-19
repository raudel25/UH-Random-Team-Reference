#include <bits/stdc++.h>

#define MAX(a, b) (a > b) ? a : b
#define MIN(a, b) (a < b) ? a : b
#define all(x) (x).begin(),(x).end()
#define pb push_back
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

// begin

void dfs(vector<vi> adj, int s) {
    vi visited(adj.size(), false);
    stack<int> st;
    st.push(s);
    visited[s] = true;
    while (!st.empty()) {
        int u = st.top();
        st.pop();
        if (!visited[u]) {
            visited[u] = true;
            for (int v : adj[u]) {
                if (!visited[v]) {
                    st.push(v);
                }
            }
        }
    }
}

void bfs(vector<vi> adj, int s) {
    vi visited(adj.size(), false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (!visited[u]) {
            visited[u] = true;
            for (int v : adj[u]) {
                if (!visited[v]) {
                    q.push(v);
                }
            }
        }
    }
}

void dijkstra(vector<vii> adj, int s) {
    vi dist(adj.size(), INT_MAX);
    priority_queue<ii> pq;
    pq.push({s, 0});
    dist[s] = 0;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (ii v : adj[u]) {
            if (dist[u] + v.second < dist[v.first]) {
                dist[v.first] = dist[u] + v.second;
                pq.push({dist[v.first], v.first});
            }
        }
    }
}

// end