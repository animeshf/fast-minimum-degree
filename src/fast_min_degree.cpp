#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;

const int N = 10005;
const int M = 100005;

int n, m, q;
int curMin;
int deg[N], parent[N];
ii edges[M];

bool adj[N][N], white[N], visI[N], visJ[N];
vector<int> initial_graph[N];
vector<int> group[N];

void init() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      adj[i][j] = false;
    }
    deg[i] = 0;
    white[i] = true;
    initial_graph[i].clear();
    group[i].clear();
    parent[i] = i;
  }
}

inline void add_edge(int u, int v) {
  if (adj[u][v]) {
    return;
  }
  if (white[u] && white[v]) {
    adj[u][v] = adj[v][u] = true;
    deg[u] += 1;
    deg[v] += 1;
  }
}

inline int root(int x) {
  if (parent[x] == x) {
    return x;
  } else {
    return parent[x] = root(parent[x]);  // Path compression.
  }
}

inline int get_min_degree_node() {
  int res = -1;
  int minm = n + 1;
  for (int i = 1; i <= n; i++) {
    if (white[i] && deg[i] < minm) {
      minm = deg[i];
      res = i;
    }
  }
  curMin = minm;
  return res;
}

inline void join(int x, int y) {
  x = root(x);
  y = root(y);
  if (x == y) {
    return;
  }
  vector<int> I;
  vector<int> J;
  for (int i = 1; i <= n; i++) {
    visI[i] = visJ[i] = false;
  }
  for (int i : group[x]) {
    visI[i] = true;
  }
  for (int j : group[y]) {
    visJ[j] = true;
  }
  for (int i : group[x]) {
    if (!visJ[i]) {
      I.push_back(i);
    }
  }
  for (int j : group[y]) {
    if (!visI[j]) {
      J.push_back(j);
    }
  }
  // This is the only contentious part: Everything else is O(sum(deg(u)^2)).
  for (int i : I) {
    for (int j : J) {
      add_edge(i, j);
    }
  }
  parent[y] = x;
  for (int j : J) {
    group[x].push_back(j);
  }
}

vector<int> solve() {
  for (int i = 1; i <= m; i++) {
    add_edge(edges[i].first, edges[i].second);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (adj[i][j]) {
        initial_graph[i].push_back(j);
        group[i].push_back(j);
      }
    }
  }
  vector<int> min_degree_ordering;
  int a = get_min_degree_node();
  min_degree_ordering.push_back(a);
  for (int i = 1; i <= n; i++) {
    white[a] = false;
    // This loop is clearly O(sum(degree^2)) = O(nm) overall.
    for (int b : initial_graph[a]) {
      if (white[b]) {
        for (int c : initial_graph[a]) {
          if (b == c) {
            break;
          }
          add_edge(b, c);
        }
      } else {
        join(a, b);
      }
    }
    for (int b = 1; b <= n; b++) {
      if (adj[a][b]) {
        adj[a][b] = adj[b][a] = false;
        deg[a] -= 1;
        deg[b] -= 1;
      }
    }
    a = get_min_degree_node();
    if (i < n) {
      min_degree_ordering.push_back(a);
    }
  }
  return min_degree_ordering;
}

int main() {
  ios::sync_with_stdio(false);
  // Read adjacency list.
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    int u, v;
    cin >> u >> v;
    edges[i] = ii(u, v);
  }
  init();
  // Compute min-degree ordering.
  vector<int> min_degree_ordering = solve();
  for (int i = 0; i < min_degree_ordering.size(); i++) {
    cout << i << ": " << min_degree_ordering[i] << endl;
  }
}
