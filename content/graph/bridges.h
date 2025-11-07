/**
 * Author: Anonymous
 * Description: bridges
 */
int n;                   // number of nodes
vector<vector<int>> adj; // adjacency list of graph

vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {
  visited[v] = true;
  tin[v] = low[v] = timer++;
  for (int to : adj[v]) {
    if (to == p)
      continue;
    if (visited[to]) {
      low[v] = min(low[v], tin[to]);
    } else {
      dfs(to, v);
      low[v] = min(low[v], low[to]);
      if (low[to] > tin[v])
        IS_BRIDGE(v, to);
    }
  }
}

void find_bridges() {
  timer = 0;
  visited.assign(n, false);
  tin.assign(n, -1);
  low.assign(n, -1);
  for (int i = 0; i < n; ++i) {
    if (!visited[i])
      dfs(i);
  }
}

// ARTICULATION POINTS:
int n;
vector<vector<int>> adj;
vector<bool> visited;
vector<int> tin, low;
int timer;
void dfs(int v, int p = -1) {
  visited[v] = true;
  tin[v] = low[v] = timer++;
  int children = 0;
  for (int to : adj[v]) {
    if (to == p)
      continue;
    if (visited[to]) {
      low[v] = min(low[v], tin[to]);
    } else {
      dfs(to, v);
      low[v] = min(low[v], low[to]);
      if (low[to] >= tin[v] && p != -1)
        IS_CUTPOINT(v);
      ++children;
    }
  }
  if (p == -1 && children > 1)
    IS_CUTPOINT(v);
}
void find_cutpoints() {
  timer = 0;
  visited.assign(n, false);
  tin.assign(n, -1);
  low.assign(n, -1);
  for (int i = 0; i < n; ++i) {
    if (!visited[i])
      dfs(i);
  }
}

// arya bridges
void findBridges_dfs(int u, int p, int &time, vector<vector<int>> &adj,
                     vector<int> &disc, vector<int> &low,
                     vector<pair<int, int>> &bridges) {
  disc[u] = low[u] = time++;

  for (int v : adj[u]) {
    if (v == p)
      continue;

    if (disc[v] != -1) {
      low[u] = min(low[u], disc[v]);
    } else {
      findBridges_dfs(v, u, time, adj, disc, low, bridges);
      low[u] = min(low[u], low[v]);
      if (low[v] > disc[u]) {
        bridges.push_back({u, v});
      }
    }
  }
}

vector<pair<int, int>> findBridges(int n, vector<vector<int>> &adj) {
  vector<int> disc(n, -1), low(n, -1);
  vector<pair<int, int>> bridges;
  int time = 0;

  for (int i = 0; i < n; ++i) {
    if (disc[i] == -1) {
      findBridges_dfs(i, -1, time, adj, disc, low, bridges);
    }
  }
  return bridges;
}
