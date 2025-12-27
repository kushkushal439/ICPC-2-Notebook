/**
 * Author: Anonymous
 * Description: XerniaAndTree
 */

struct HLD {
  ... template <class B> void go_up(int node, int anc, B op) {
    while (top[node] != top[anc]) {
      op(tin[top[node]], tin[node]);
      node = p[top[node]];
    }
    op(tin[anc], tin[node]);
  }
};

template <typename T, typename U> struct seg_tree_lazy {};

struct node {
  int ans = 1e9, len = 0, max_d = 0;
  node operator+(const node &n) {
    node ret;
    ret.len = len + n.len;
    ret.ans = min(ans + n.len, n.ans);
    ret.max_d = max(max_d, n.max_d);
    return ret;
  }
};
struct update {
  int depth = 1e9;
  node operator()(const node &n) {
    node ret;
    ret.len = n.len;
    ret.ans = min(n.ans, depth - n.max_d);
    ret.max_d = n.max_d;
    return ret;
  }
  update operator+(const update &u) { return {min(depth, u.depth)}; }
};

void solve() {
  int n, m;
  cin >> n >> m;
  vvi adj(n);
  fr(i, 0, n - 1){...}

  vi dep(n, 0);
  function<void(int, int)> dfs = [&](int node, int par) {
    for (auto child : adj[node]) {
      if (child == par)
        continue;
      dep[child] = dep[node] + 1;
      dfs(child, node);
    }
  };
  dep[0] = 1;
  dfs(0, -1);

  HLD hld(adj);
  seg_tree_lazy<node, update> lst(n);
  vector<node> leaves(n);
  leaves[hld.tin[0]].ans = 0;
  leaves[hld.tin[0]].len = 1;
  leaves[hld.tin[0]].max_d = 1;
  for (int i = 1; i < n; i++) {
    leaves[hld.tin[i]].ans = 1e9;
    leaves[hld.tin[i]].len = 1;
    leaves[hld.tin[i]].max_d = dep[i];
  }
  lst.set_leaves(leaves);
  while (m--) {
    int q, v;
    cin >> q >> v;
    v--;
    if (q == 1) {
      // paint v red
      int depth = dep[v];
      hld.process(0, v, [&](int l, int r) {
        // in range l, r should do the update
        lst.upd(l, r, {depth});
      });
    } else {
      // get distance from v to closest red vertex
      // should go up?
      auto add = [&](node n2, node n1) {
        // n1 n2
        node ret;
        ret.len = n1.len + n2.len;
        ret.max_d = min(n1.max_d, n2.max_d);
        ret.ans = min(n1.ans, n2.ans + n1.len);
        return ret;
      };
      node ans = {-1, -1, -1};
      hld.process(0, v, [&](int l, int r) {
        // it will keep going up basically
        if (ans.ans == -1) {
          ans = lst.query(l, r);
        } else {
          ans = add(lst.query(l, r), ans);
        }
      });
      cout << ans.ans << endl;
    }
  }
}
