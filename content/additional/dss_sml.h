#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
class DSU {
public:
  vector<int> parent;
  vector<int> size;
  void make_set(int v) {
    parent[v] = v;
    size[v] = 1;
  }
  DSU(int n) {
    parent.resize(n);
    size.resize(n);
    for (int i = 0; i < n; i++) {
      make_set(i);
    }
  }
  int find_set(int v) {
    if (v == parent[v])
      return v;
    return parent[v] = find_set(parent[v]);
  }

  void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
      if (size[a] < size[b])
        swap(a, b);
      parent[b] = a;
      size[a] += size[b];
    }
  }
};

void solve() {
  int n;
  cin >> n;
  vector<array<int, 2>> edg;
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    edg.push_back({a, b});
  }

  vvi adj(n + 1);
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].pb(b);
    adj[b].pb(a);
  }

  DSU dsu(n + 1);
  LL ans = 1;

  vector<vector<int>> st(n + 1);
  fr(i, 1, n + 1) st[i].push_back(i);
  // debug(st);
  for (auto [a, b] : edg) {
    int sz1 = dsu.size[dsu.find_set(a)];
    int sz2 = dsu.size[dsu.find_set(b)];
    ans = mod_mul(ans, mod_mul(inv[sz1], inv[sz2]));

    int pa = dsu.find_set(a);
    int pb = dsu.find_set(b);

    if (st[pa].size() < st[pb].size()) {
      swap(pa, pb);
    }
    // for every edge from comp pb, check if connecting to comp pa
    int cnt = 0;
    for (auto node : st[pb]) {
      for (auto j : adj[node]) {
        int par = dsu.find_set(j);
        if (par == pa)
          cnt++;
        if (cnt >= 2)
          break;
      }
    }
    if (cnt != 1) {
      cout << 0 << endl;
      return;
    }

    for (auto node : st[pb]) {
      st[pa].push_back(node);
    }

    st[pb].clear();

    dsu.union_sets(pa, pb);
  }
  cout << ans << endl;
}

signed main() {
  fast();
  int t = 1;
  Inverses();
  while (t--)
    solve();
  return 0;
}
