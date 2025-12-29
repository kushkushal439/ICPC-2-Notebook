/**
 * Author: Anonymous
 * Description: bridges
 */
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
