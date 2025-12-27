/**
 * Author: Anonymous
 * Description: Centroid
 */
void solve() {
  int n;
  cin >> n;
  vvi adj(n);
  int centroid = -1;
  vi sub(n, 0);
  function<void(int, int, int)> find_centroid = [&](int node, int par,
                                                    int size) {
    sub[node] = 1;
    for (auto child : adj[node]) {
      if (child == par)
        continue;
      find_centroid(child, node, size);
      sub[node] += sub[child];
    }
    if (centroid == -1) {
      debug(node, sub[node], size);
      if (sub[node] * 2 > size) {
        centroid = node;
      }
    }
  };

  function<void(int, int, int)> getans = [&](int node, int par, int size) {
    centroid = -1;
    find_centroid(node, -1, size);
    vi v;
    for (auto i : adj[centroid])
      v.pb(i);
    if (sz(v) == 0)
      ans(centroid);
    int ismin = ask(centroid, v);
    if (ismin)
      ans(centroid);
    if (sz(v) == 1) {
      vvi adj1(n);
      function<void(int, int)> dfscase = [&](int node, int par) {
        for (auto child : adj[node]) {
          if (child == par)
            continue;
          adj1[node].pb(child);
          adj1[child].pb(node);
          dfscase(child, node);
        }
      };
      dfscase(v[0], centroid);
      swap(adj, adj1);
      getans(v[0], -1, sub[v[0]]);
      return;
    }
    function<void(int, int)> getsizes = [&](int node, int par) {
      sub[node] = 1;
      for (auto child : adj[node]) {
        if (child == par)
          continue;
        getsizes(child, node);
        sub[node] += sub[child];
      }
    };
    getsizes(centroid, par);
    sort(all(v), [&](int a, int b) { return sub[a] > sub[b]; });
    vi temp;
    int idx = -1;
    int totsum = 0;
    for (int i = 0; i < sz(v); i++) {
      totsum += sub[v[i]];
    }
    int sum = 0;
    for (int i = 0; i < sz(v); i++) {
      if (sum >= (totsum / 2)) {
        idx = i;
        break;
      }
      sum += sub[v[i]];
      temp.pb(v[i]);
    }
    ismin = ask(centroid, temp);
    vi bad(n, 0);
    if (ismin) {
      for (auto i : temp)
        bad[i] = 1;
    } else {
      for (auto i : v)
        bad[i] = 1;
      for (auto i : temp)
        bad[i] = 0;
    }
    vvi adj1(n);
    int szz = 0;
    function<void(int, int)> dfs = [&](int node, int par) {
      szz++;
      for (auto child : adj[node]) {
        if (child == par)
          continue;
        if (bad[child] == 1)
          continue;
        adj1[node].pb(child);
        adj1[child].pb(node);
        dfs(child, node);
      }
    };
    dfs(centroid, -1);
    swap(adj, adj1);
    getans(centroid, -1, szz);
  };

  getans(0, -1, n);
}

struct LCA {
  int n, LOG;
  vector<vector<int>> up;
  vector<int> depth;
  vector<vector<int>> adj;

  LCA(int n_) {
    n = n_;
    adj.assign(n + 1, {});
    LOG = 1;
    while ((1 << LOG) <= n)
      LOG++;
    up.assign(n + 1, vector<int>(LOG + 1));
    depth.assign(n + 1, 0);
  }

  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void dfs(int v, int p) {
    up[v][0] = p;
    for (int i = 1; i <= LOG; i++)
      up[v][i] = up[up[v][i - 1]][i - 1];
    for (int to : adj[v])
      if (to != p) {
        depth[to] = depth[v] + 1;
        dfs(to, v);
      }
  }

  void init(int root) { dfs(root, root); }

  int query(int a, int b) {
    if (depth[a] < depth[b])
      swap(a, b);
    int k = depth[a] - depth[b];
    for (int i = LOG; i >= 0; i--)
      if (k & (1 << i))
        a = up[a][i];
    if (a == b)
      return a;
    for (int i = LOG; i >= 0; i--)
      if (up[a][i] != up[b][i]) {
        a = up[a][i];
        b = up[b][i];
      }
    return up[a][0];
  }
  int get_dist(int u, int v) {
    int lca = query(u, v);
    return depth[u] + depth[v] - 2 * depth[lca];
  }
};

struct CentroidDecomposition {
  vector<vector<int>> adj;
  vector<bool> is_removed;
  vector<int> parent_in_centroid_tree;
  vector<int> subtree_size;
  int n;

  CentroidDecomposition(int size) {
    n = size;
    adj.assign(n + 1, vector<int>());
    is_removed.assign(n + 1, false);
    parent_in_centroid_tree.assign(n + 1, 0);
    subtree_size.assign(n + 1, 0);
  }

  void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int get_subtree_sizes(int u, int p = -1) {
    if (is_removed[u])
      return 0;
    subtree_size[u] = 1;
    for (int v : adj[u]) {
      if (v != p && !is_removed[v]) {
        subtree_size[u] += get_subtree_sizes(v, u);
      }
    }
    return subtree_size[u];
  }

  int find_centroid(int u, int p, int tree_total_size) {
    for (int v : adj[u]) {
      if (v != p && !is_removed[v] && subtree_size[v] > tree_total_size / 2) {
        return find_centroid(v, u, tree_total_size);
      }
    }
    return u;
  }

  void init(int u = 0, int p = -1) {
    int tree_total_size = get_subtree_sizes(u);
    int centroid = find_centroid(u, -1, tree_total_size);

    parent_in_centroid_tree[centroid] = p;
    is_removed[centroid] = true;

    // --- Add logic for the current centroid here ---

    for (int v : adj[centroid]) {
      if (!is_removed[v]) {
        init(v, centroid);
      }
    }
  }
};
