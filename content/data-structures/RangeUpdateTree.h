/**
 * Author: Unknown
 */
template <typename T, typename F> struct RangeUpdateTree {
  int n;
  vector<T> tree;
  T identity;
  F merge;
  RangeUpdateTree(const vector<T> &arr, T id, F _m)
      : n((int)arr.size()), tree(2 * n), identity(id), merge(_m) {
    for (int i = 0; i < n; i++)
      tree[n + i] = arr[i];
    for (int i = n - 1; i >= 1; i--)
      tree[i] = merge(tree[2 * i], tree[2 * i + 1]);
  }
  void update(int l, int r, T value) {
    assert(l >= 0 && r < n && l <= r);
    for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
      if (l & 1)
        tree[l] = merge(value, tree[l]), l++;
      if (!(r & 1))
        tree[r] = merge(value, tree[r]), r--;
    }
    if (l == r)
      tree[l] = merge(value, tree[l]);
  }
  T query(int v) {
    T res = tree[v += n];
    for (; v > 1; v >>= 1)
      res = merge(res, tree[v >> 1]);
    return res;
  }
};
// ex: RangeUpdateTree<int, decltype(join)> v(vi (n, 1e9), 1e9, join); use auto
// func for join