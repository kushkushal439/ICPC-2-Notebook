/**
 * Author: Anonymous
 * Description: FloydWarshall
 */
const long long INF = (long long)1e18;
bool floyd_warshall(int n, vector<vector<long long>> &dist) {
  // initialise dist with edge weights, INF if no edge exists
  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        if (dist[i][k] < INF && dist[k][j] < INF)
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

  for (int i = 0; i < n; i++)
    if (dist[i][i] < 0)
      return true;
  return false;
}
