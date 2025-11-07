/**
 * Author: Anonymous
 * Description: hash
 */
template <int MOD, int P> struct RH {
  // using H1 = RH<1000000007, 91138233>;
  // using H2 = RH<1000000009, 97266353>;
  vector<long long> h, p;
  RH(const string &s) {
    int n = s.size();
    h.resize(n + 1, 0);
    p.resize(n + 1, 0);
    p[0] = 1;
    for (int i = 0; i < n; i++) {
      h[i + 1] = (h[i] * P + s[i]) % MOD;
      p[i + 1] = p[i] * P % MOD;
    }
  }
  long long get(int l, int r) { // [l,r]
    long long res = (h[r + 1] - h[l] * p[r - l + 1]) % MOD;
    return res < 0 ? res + MOD : res;
  }
};