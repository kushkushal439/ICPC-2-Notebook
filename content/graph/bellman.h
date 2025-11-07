/**
 * Author: Anonymous
 * Description: bellman
 */
bool bellman_ford(int n, int src, vector<vector<pair<int, int>>> &adj,
                  vector<long long> &dist) {
  const long long INF = 1e18;
  dist.assign(n, INF);
  dist[src] = 0;
  for (int i = 0; i < n - 1; i++) {
    for (int u = 0; u < n; u++) {
      if (dist[u] == INF)
        continue;
      for (auto &p : adj[u]) {
        int v = p.first, w = p.second;
        if (dist[u] + w < dist[v])
          dist[v] = dist[u] + w;
      }
    }
  }
  for (int u = 0; u < n; u++) {
    if (dist[u] == INF)
      continue;
    for (auto &p : adj[u]) {
      int v = p.first, w = p.second;
      if (dist[u] + w < dist[v])
        return false;
    }
  }
  return true;
}
