/**
 * Author: Anonymous
 * Description: ModularArithmetic
 */
int add(int x, int y, int m = M) {
  int ret = (x + y) % m;
  if (ret < 0)
    ret += m;
  return ret;
}
int mult(int x, int y, int m = M) {
  int ret = (x * y) % m;
  if (ret < 0)
    ret += m;
  return ret;
}
int pw(int a, int b, int m = M) {
  int ret = 1;
  int p = a;
  while (b) {
    if (b & 1)
      ret = mult(ret, p, m);
    b >>= 1;
    p = mult(p, p, m);
  }
  return ret;
}

#define LL int
const long long mod = M;

int euclid(int a, int b, int &x, int &y) {
  if (!b)
    return x = 1, y = 0, a;
  int d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}

int modulo_inverse(int a, int m) {
  int x, y;
  int g = euclid(a, m, x, y);
  if (g != 1) {
    return -1;
  } else {
    x = (x % m + m) % m;
    return x;
  }
}

LL mod_mul(LL a, LL b) {
  a = a % mod;
  b = b % mod;
  return (((a * b) % mod) + mod) % mod;
}

LL mod_add(LL a, LL b) {
  a = a % mod;
  b = b % mod;
  return (((a + b) % mod) + mod) % mod;
}

const int MX = 5e5 + 1;
vector<int> inv(MX + 1), fci(MX + 1), fc(MX + 1);
const int Mod = 1e9 + 7;

void Inverses() {
  inv[1] = 1;
  for (int i = 2; i <= MX; i++) {
    inv[i] = Mod - Mod / i * inv[Mod % i] % Mod;
  }
}

void Factorials() {
  fc[0] = fc[1] = 1;
  for (int i = 2; i <= MX; i++) {
    fc[i] = fc[i - 1] * i % Mod;
  }
}

void InverseFactorials() {
  Inverses();
  Factorials();
  fci[1] = fci[0] = 1;
  for (int i = 2; i <= MX; i++) {
    fci[i] = fci[i - 1] * inv[i] % Mod;
  }
}

int nck(int num, int k) {
  if (num < 0) {
    return 0;
  }
  if (k < 0) {
    return 0;
  }
  if (num < k) {
    return 0;
  } else {
    return fc[num] * fci[k] % Mod * fci[num - k] % Mod;
  }
}

int BinExpItermod(int a, int b) {
  int ans = 1;
  while (b > 0) {
    if (b & 1) {
      ans = (ans * a) % mod;
    }
    a = (a * a) % mod;
    b = b >> 1;
  }
  return ans;
}